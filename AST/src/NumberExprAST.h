//
// Created by Izumi Sakai on 4/17/22.
//

#ifndef TOY_LANGUAGE_NUMBEREXPRAST_H
#define TOY_LANGUAGE_NUMBEREXPRAST_H

#include "ExprAST.h"

class NumberExprAST : public ExprAST {
    const double val_;
public:
    explicit NumberExprAST(double val);

    llvm::Value *CodeGen() override;
};

#endif