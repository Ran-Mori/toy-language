//
// Created by Izumi Sakai on 4/17/22.
//

#ifndef TOY_LANGUAGE_CODEGEN_H
#define TOY_LANGUAGE_CODEGEN_H

#include <memory>
#include <map>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Value.h"

class CodeGen {
public:
    static std::unique_ptr<llvm::LLVMContext> s_context;
    static std::unique_ptr<llvm::Module> s_module;
    static std::unique_ptr<llvm::IRBuilder<>> s_builder;
    static std::map<std::string, llvm::Value *> s_named_values;
};


#endif //TOY_LANGUAGE_CODEGEN_H
