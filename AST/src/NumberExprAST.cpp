//
// Created by Izumi Sakai on 4/17/22.
//

#include "NumberExprAST.h"
#include "llvm/IR/Constants.h"
#include "../../Codegen/src/CodeGen.h"

NumberExprAST::NumberExprAST(const double val) : val_(val) {}

llvm::Value *NumberExprAST::CodeGen() {
    return llvm::ConstantFP::get(*CodeGen::s_context, llvm::APFloat(val_));
}
