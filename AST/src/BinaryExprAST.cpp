//
// Created by Izumi Sakai on 4/17/22.
//

#include "BinaryExprAST.h"
#include "llvm/IR/Value.h"
#include "../../Codegen/src/CodeGen.h"
#include "../../Error/src/Error.h"

BinaryExprAST::BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs, std::unique_ptr<ExprAST> rhs)
        : op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

llvm::Value *BinaryExprAST::CodeGen() {
    llvm::Value *L = lhs_->CodeGen();
    llvm::Value *R = rhs_->CodeGen();
    if (!L || !R)
        return nullptr;

    switch (op_) {
        case '+':
            return CodeGen::s_builder->CreateFAdd(L, R, "addtmp");
        case '-':
            return CodeGen::s_builder->CreateFSub(L, R, "subtmp");
        case '*':
            return CodeGen::s_builder->CreateFMul(L, R, "multmp");
        case '<':
            L = CodeGen::s_builder->CreateFCmpULT(L, R, "cmptmp");
            // Convert bool 0/1 to double 0.0 or 1.0
            return CodeGen::s_builder->CreateUIToFP(L, llvm::Type::getDoubleTy(*CodeGen::s_context), "booltmp");
        default:
            return Error::LogErrorV("invalid binary operator");
    }
}
