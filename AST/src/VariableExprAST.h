//
// Created by Izumi Sakai on 4/17/22.
//

#ifndef TOY_LANGUAGE_VARIABLEEXPRAST_H
#define TOY_LANGUAGE_VARIABLEEXPRAST_H

#include "ExprAST.h"
#include <string>

class VariableExprAST : public ExprAST {
    const std::string name_;
public:
    explicit VariableExprAST(std::string name);

    llvm::Value *CodeGen() override;
};

#endif