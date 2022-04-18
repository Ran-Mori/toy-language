//
// Created by Izumi Sakai on 4/17/22.
//

#include "FunctionAST.h"
#include "../../Codegen/src/CodeGen.h"
#include "llvm/IR/Verifier.h"

FunctionAST::FunctionAST(std::unique_ptr<PrototypeAST> prototype_ast, std::unique_ptr<ExprAST> body)
        : prototype_ast_(std::move(prototype_ast)), body_(std::move(body)) {}

llvm::Function *FunctionAST::CodeGen() {
    // First, check for an existing function from a previous 'extern' declaration.
    llvm::Function *the_function = CodeGen::s_module->getFunction(prototype_ast_->name());

    if (!the_function)
        the_function = prototype_ast_->CodeGen();

    if (!the_function)
        return nullptr;

    // Create a new basic block to start insertion into.
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(*CodeGen::s_context, "entry", the_function);
    CodeGen::s_builder->SetInsertPoint(BB);

    // Record the function arguments in the NamedValues map.
    CodeGen::s_named_values.clear();
    for (auto &arg: the_function->args())
        CodeGen::s_named_values[std::string(arg.getName())] = &arg;

    if (llvm::Value *ret_val = body_->CodeGen()) {
        // Finish off the function.
        CodeGen::s_builder->CreateRet(ret_val);

        // Validate the generated code, checking for consistency.
        llvm::verifyFunction(*the_function);

        return the_function;
    }

    // Error reading body, remove function.
    the_function->eraseFromParent();
    return nullptr;
}