//
// Created by Izumi Sakai on 4/17/22.
//

#include "VariableExprAST.h"
#include "../../Codegen/src/CodeGen.h"
#include "llvm/IR/Value.h"
#include "../../Error/src/Error.h"

VariableExprAST::VariableExprAST(std::string name) : name_(std::move(name)) {}

llvm::Value *VariableExprAST::CodeGen() {
    // Look this variable up in the function.
    llvm::Value *v = CodeGen::s_named_values[name_];
    if (!v)
        return Error::LogErrorV("Unknown variable name");
    return v;
}
