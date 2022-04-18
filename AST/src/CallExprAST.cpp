//
// Created by Izumi Sakai on 4/17/22.
//

#include "CallExprAST.h"
#include "../../Codegen/src/CodeGen.h"
#include "../../Error/src/Error.h"

CallExprAST::CallExprAST(std::string callee, std::vector<std::unique_ptr<ExprAST>> args)
        : callee_(std::move(callee)), args_(std::move(args)) {}

llvm::Value *CallExprAST::CodeGen() {
    // Look up the name in the global module table.
    llvm::Function *callee_func = CodeGen::s_module->getFunction(callee_);
    if (!callee_func)
        return Error::LogErrorV("Unknown function referenced");

    // If argument mismatch error.
    if (callee_func->arg_size() != args_.size())
        return Error::LogErrorV("Incorrect # arguments passed");

    std::vector<llvm::Value *> args_v;
    for (unsigned i = 0, e = args_.size(); i != e; ++i) {
        args_v.push_back(args_[i]->CodeGen());
        if (!args_v.back())
            return nullptr;
    }

    return CodeGen::s_builder->CreateCall(callee_func, args_v, "calltmp");
}
