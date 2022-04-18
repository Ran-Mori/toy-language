//
// Created by Izumi Sakai on 4/17/22.
//

#ifndef TOY_LANGUAGE_EXPRAST_H
#define TOY_LANGUAGE_EXPRAST_H

#include "llvm/IR/Value.h"

class ExprAST {
public:
    virtual ~ExprAST() {}

    virtual llvm::Value *CodeGen() = 0;
};

#endif //TOY_LANGUAGE_EXPRAST_H
