//
// Created by Izumi Sakai on 4/17/22.
//

#ifndef TOY_LANGUAGE_FUNCTIONAST_H
#define TOY_LANGUAGE_FUNCTIONAST_H

#include <memory>
#include "PrototypeAST.h"
#include "ExprAST.h"

class FunctionAST {
    std::unique_ptr<PrototypeAST> prototype_ast_;
    std::unique_ptr<ExprAST> body_;
public:
    explicit FunctionAST(std::unique_ptr<PrototypeAST> prototype_ast, std::unique_ptr<ExprAST> body);

    llvm::Function *CodeGen();
};

#endif //TOY_LANGUAGE_FUNCTIONAST_H
