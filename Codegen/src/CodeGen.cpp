//
// Created by Izumi Sakai on 4/17/22.
//

#include "CodeGen.h"

std::unique_ptr<llvm::LLVMContext> CodeGen::s_context
        = std::make_unique<llvm::LLVMContext>();
std::unique_ptr<llvm::Module> CodeGen::s_module
        = std::make_unique<llvm::Module>("my cool jit", *s_context);
std::unique_ptr<llvm::IRBuilder<>> CodeGen::s_builder
        = std::make_unique<llvm::IRBuilder<>>(*s_context);
std::map<std::string, llvm::Value *> CodeGen::s_named_values;
