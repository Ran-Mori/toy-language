//
// Created by Izumi Sakai on 4/18/22.
//

#include "Error.h"

std::unique_ptr<ExprAST> Error::LogError(const std::string &error_message) {
    std::cerr << "LogError:" << error_message << std::endl;
    return nullptr;
}

std::unique_ptr<PrototypeAST> Error::LogErrorP(const std::string &error_message) {
    std::cerr << "LogErrorP:" << error_message << std::endl;
    return nullptr;
}

llvm::Value *Error::LogErrorV(const std::string &error_message) {
    std::cerr << "LogErrorV:" << error_message << std::endl;
    return nullptr;
}
