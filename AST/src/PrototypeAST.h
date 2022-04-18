//
// Created by Izumi Sakai on 4/17/22.
//

#ifndef TOY_LANGUAGE_PROTOTYPEAST_H
#define TOY_LANGUAGE_PROTOTYPEAST_H

#include <string>
#include <vector>
#include "llvm/IR/Function.h"

class PrototypeAST {
    const std::string name_;
    const std::vector<std::string> args_;

public:
    PrototypeAST(std::string name, std::vector<std::string> args);

    llvm::Function *CodeGen();

    const std::string &name() const;
};

#endif