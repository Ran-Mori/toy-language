//
// Created by Izumi Sakai on 4/17/22.
//

#ifndef TOY_LANGUAGE_ERROR_H
#define TOY_LANGUAGE_ERROR_H

#include <iostream>
#include <string>
#include "../../AST/src/ExprAST.h"
#include "../../AST/src/PrototypeAST.h"

class Error {
public:
    static std::unique_ptr<ExprAST> LogError(const std::string &error_message);

    static std::unique_ptr<PrototypeAST> LogErrorP(const std::string &error_message);

    static llvm::Value *LogErrorV(const std::string &error_message);
};

#endif //TOY_LANGUAGE_ERROR_H
