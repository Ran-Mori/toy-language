//
// Created by Izumi Sakai on 4/17/22.
//

#ifndef TOY_LANGUAGE_BINARYEXPRAST_H
#define TOY_LANGUAGE_BINARYEXPRAST_H

#include "ExprAST.h"
#include <memory>

class BinaryExprAST : public ExprAST {
    char op_;
    std::unique_ptr<ExprAST> lhs_, rhs_;
public:
    explicit BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs, std::unique_ptr<ExprAST> rhs);

    llvm::Value *CodeGen() override;
};

#endif //TOY_LANGUAGE_BINARYEXPRAST_H
