//
// Created by Izumi Sakai on 4/17/22.
//

#ifndef TOY_LANGUAGE_CALLEXPRAST_H
#define TOY_LANGUAGE_CALLEXPRAST_H

#include <string>
#include <vector>
#include <memory>
#include "ExprAST.h"

class CallExprAST : public ExprAST {
    const std::string callee_;
    std::vector<std::unique_ptr<ExprAST>> args_;
public:
    explicit CallExprAST(std::string callee, std::vector<std::unique_ptr<ExprAST>> args);

    llvm::Value *CodeGen() override;
};

#endif //TOY_LANGUAGE_CALLEXPRAST_H
