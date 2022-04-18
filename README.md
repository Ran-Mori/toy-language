# toy-language
A toy language compiler based on llvm. It's just an OOP implementation of the llvm official example(Kaleidoscope).



## Why this project exists?

1. [LLVM official example](https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/) codes are all written in a single file named toy.cpp. And it is not a mannered way to understand structure of the whole project.
2. I'm learning cmake recently. So creating an organized project from a single file helps me understand how cmake arranges a C++ project.
3. It helps me review the course 《Principles of  Compilation》.

## Note

1. Source codes are just almost same as LLVM official example. I would recommend you jump to [offical page](https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/) and browse the explanation.
2. This project implements only to [chapter3(Code generation to LLVM IR)](https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl03.html).
3. Only MacOS is tested, I don't guarantee it can work well on other platforms.

## Requirements

1. llvm = **15**
2. cmake >= 3.8
3. g++ or clang++ compiler that supports **C++ standard 14**

## Get Stated

1. Install llvm 15

   ```shell
   cd ~
   git clone https://github.com/llvm/llvm-project.git --depth=1
   cd llvm-project
   cmake -B build -S llvm -D CMAKE_BUILD_TYPE=Debug -D CMAKE_INSTALL_PREFIX=./build/install -D LLVM_ENABLE_RTTI=ON
   cmake --build build
   cd build
   make install
   ```

   * Please make sure you do clone llvm version **15**. The llvm code base and including header names may vary from versions. Higher or lower llvm versions may lead to not founding of some funtions. If the main git branch version is **above 15**, I would recommend to download llvm 15 from [this official page](https://releases.llvm.org/download.html)，choose **LLVM source code(.sig)** option and start downloading.
   * Please make sure you have set `CMAKE_BUILD_TYPE=Debug` and `LLVM_ENABLE_RTTI=ON` when build with cmake. Using `Realease` type or not enabling `LLVM_RTTI` may also lead to not founding of some functions.

3. Set environment virable

   ```shell
   export LLVM_HOME=~/llvm-project/build/install
   ```

4. Clone the project

   ```shell
   cd ~
   git clone https://github.com/IzumiSakai-zy/toy-language.git
   ```

5. Build and run 

   ```shell
   cd ~/toy-language
   cmake -B build
   cmake --build build
   ./build/toy-language
   ```

6. You will see the result below if nothing unexpected happens(I truly wish).

   ```shell
   Read function definition:define double @foo(double %x, double %y) {
   entry:
     %calltmp = call double @foo(double %y, double 4.000000e+00)
     %addtmp = fadd double %x, %calltmp
     ret double %addtmp
   }
   ```

   

## Thanks

[llvm-project](https://github.com/llvm/llvm-project)

[llvmRustCompiler](https://github.com/G-H-Li/llvmRustCompiler)

