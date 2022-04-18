cmake_minimum_required(VERSION 3.8)
project(toy_language LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# must set system environment LLVM_HOME to where you make install LLVM
if (NOT DEFINED ENV{LLVM_HOME})
    message(FATAL_ERROR "$LLVM_HOME is not defined")
endif ()
if (NOT DEFINED ENV{LLVM_DIR})
    set(LLVM_DIR $ENV{LLVM_HOME}/lib/cmake/llvm)
endif ()

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

message(STATUS "LLVM_INCLUDE_DIRS: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM_DEFINITIONS: ${LLVM_DEFINITIONS}")

list(APPEND llvm_components
        Support
        Core
        MC
        OrcJIT)

message(STATUS "CMAKE_HOST_SYSTEM_PROCESSOR:${CMAKE_HOST_SYSTEM_PROCESSOR}")
# for common x64_64 processor architecture
if (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    list(APPEND llvm_components
            X86Disassembler
            X86AsmParser
            X86CodeGen
            X86Info)
    # for specific Apple M1 processor which based on arm64 architecture
elseif (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "arm64")
    list(APPEND llvm_components
            AArch64Disassembler
            AArch64AsmParser
            AArch64CodeGen
            AArch64Info)
endif ()
message(STATUS "llvm_components:${llvm_components}")

llvm_map_components_to_libnames(llvm_libs ${llvm_components})

add_subdirectory(AST)
add_subdirectory(Codegen)
add_subdirectory(Error)
add_subdirectory(Parser)
add_subdirectory(Lexer)

add_executable(toy_language main.cpp)

target_link_libraries(toy_language
        ${llvm_libs}
        ast
        codegen
        error
        lexer
        parser)

