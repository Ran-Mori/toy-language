//
// Created by Izumi Sakai on 4/17/22.
//

#include "PrototypeAST.h"
#include "../../Codegen/src/CodeGen.h"

const std::string &PrototypeAST::name() const { return name_; }

PrototypeAST::PrototypeAST(std::string name, std::vector<std::string> args)
        : name_(std::move(name)), args_(std::move(args)) {}

llvm::Function *PrototypeAST::CodeGen() {
    // Make the function type:  double(double,double) etc.
    std::vector<llvm::Type *> Doubles(args_.size(), llvm::Type::getDoubleTy(*CodeGen::s_context));
    llvm::FunctionType *ft =
            llvm::FunctionType::get(llvm::Type::getDoubleTy(*CodeGen::s_context), Doubles, false);

    llvm::Function *F =
            llvm::Function::Create(ft, llvm::Function::ExternalLinkage, name_, CodeGen::s_module.get());

    // Set names for all arguments.
    unsigned idx = 0;
    for (auto &Arg: F->args())
        Arg.setName(args_[idx++]);

    return F;
}