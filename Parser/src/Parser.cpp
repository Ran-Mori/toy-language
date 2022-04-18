//
// Created by Izumi Sakai on 4/17/22.
//

#include "Parser.h"
#include "../../AST/src/NumberExprAST.h"
#include "../../AST/src/VariableExprAST.h"
#include "../../AST/src/CallExprAST.h"
#include "../../AST/src/BinaryExprAST.h"
#include "../../Error/src/Error.h"
#include "../../Lexer/src/Token.h"
#include "../../Codegen/src/CodeGen.h"

int Parser::s_current_token_ = -1;

std::map<char, int> Parser::s_binary_op_precedence{
        {'<', 10},
        {'+', 20},
        {'-', 20},
        {'*', 40}
};

Parser::Parser(std::unique_ptr<Lexer> &lexer)
        : lexer_(std::move(lexer)) {}

int Parser::GetTokPrecedence() {
    if (!isascii(s_current_token_)) { return -1; }
    int precedence = s_binary_op_precedence[s_current_token_];
    if (precedence <= 0) { return -1; }
    return precedence;
}

int Parser::GetNextToken() {
    return s_current_token_ = lexer_->GetToken();
}

std::unique_ptr<ExprAST> Parser::ParseNumberExpr() {
    auto result = std::make_unique<NumberExprAST>(lexer_->number_val());
    GetNextToken();
    return result;
}

std::unique_ptr<ExprAST> Parser::ParseParenExpr() {
    GetNextToken(); // eat (.
    auto V = ParseExpression();
    if (!V)
        return nullptr;

    if (s_current_token_ != ')')
        return Error::LogError("expected ')'");
    GetNextToken(); // eat ).
    return V;
}

std::unique_ptr<ExprAST> Parser::ParseExpression() {
    auto lhs = ParsePrimary();
    if (!lhs)
        return nullptr;

    return ParseBinOpRHS(0, std::move(lhs));
}

std::unique_ptr<ExprAST> Parser::ParseIdentifierExpr() {
    std::string id_name = lexer_->identifier_str();

    GetNextToken(); // eat identifier.

    if (s_current_token_ != '(') // Simple variable ref.
        return std::make_unique<VariableExprAST>(id_name);

    // Call.
    GetNextToken(); // eat (
    std::vector<std::unique_ptr<ExprAST>> Args;
    if (s_current_token_ != ')') {
        while (true) {
            if (auto Arg = ParseExpression())
                Args.push_back(std::move(Arg));
            else
                return nullptr;

            if (s_current_token_ == ')')
                break;

            if (s_current_token_ != ',')
                return Error::LogError("Expected ')' or ',' in argument list");
            GetNextToken();
        }
    }

    // Eat the ')'.
    GetNextToken();

    return std::make_unique<CallExprAST>(id_name, std::move(Args));
}

std::unique_ptr<ExprAST> Parser::ParsePrimary() {
    switch (s_current_token_) {
        default:
            return Error::LogError("unknown token when expecting an expression");
        case Token::tok_identifier:
            return ParseIdentifierExpr();
        case Token::tok_number:
            return ParseNumberExpr();
        case '(':
            return ParseParenExpr();
    }
}

std::unique_ptr<ExprAST> Parser::ParseBinOpRHS(int expr_prec, std::unique_ptr<ExprAST> lhs) {
    // If this is a binop, find its precedence.
    while (true) {
        int tok_prec = GetTokPrecedence();

        // If this is a binop that binds at least as tightly as the current binop,
        // consume it, otherwise we are done.
        if (tok_prec < expr_prec)
            return lhs;

        // Okay, we know this is a binop.
        int bin_op = s_current_token_;
        GetNextToken(); // eat binop

        // Parse the primary expression after the binary operator.
        auto rhs = ParsePrimary();
        if (!rhs)
            return nullptr;

        // If BinOp binds less tightly with RHS than the operator after RHS, let
        // the pending operator take RHS as its LHS.
        int next_prec = GetTokPrecedence();
        if (tok_prec < next_prec) {
            rhs = ParseBinOpRHS(tok_prec + 1, std::move(rhs));
            if (!rhs)
                return nullptr;
        }

        // Merge LHS/RHS.
        lhs = std::make_unique<BinaryExprAST>(bin_op, std::move(lhs), std::move(rhs));
    }
}

std::unique_ptr<PrototypeAST> Parser::ParsePrototype() {
    if (s_current_token_ != Token::tok_identifier)
        return Error::LogErrorP("Expected function name in prototype");

    std::string fn_name = lexer_->identifier_str();
    GetNextToken();

    if (s_current_token_ != '(')
        return Error::LogErrorP("Expected '(' in prototype");

    std::vector<std::string> arg_names;
    while (GetNextToken() == Token::tok_identifier)
        arg_names.push_back(lexer_->identifier_str());
    if (s_current_token_ != ')')
        return Error::LogErrorP("Expected ')' in prototype");

    // success.
    GetNextToken(); // eat ')'.

    return std::make_unique<PrototypeAST>(fn_name, std::move(arg_names));
}

std::unique_ptr<FunctionAST> Parser::ParseDefinition() {
    GetNextToken(); // eat def.
    auto proto = ParsePrototype();
    if (!proto) { return nullptr; }

    if (auto e = ParseExpression())
        return std::make_unique<FunctionAST>(std::move(proto), std::move(e));
    return nullptr;
}

std::unique_ptr<FunctionAST> Parser::ParseTopLevelExpr() {
    if (auto e = ParseExpression()) {
        // Make an anonymous proto.
        auto proto = std::make_unique<PrototypeAST>("__anon_expr", std::vector<std::string>());
        return std::make_unique<FunctionAST>(std::move(proto), std::move(e));
    }
    return nullptr;
}

std::unique_ptr<PrototypeAST> Parser::ParseExtern() {
    GetNextToken(); // eat extern.
    return ParsePrototype();
}

void Parser::HandleDefinition() {
    if (auto fn_ast = ParseDefinition()) {
        if (auto *fn_IR = fn_ast->CodeGen()) {
            std::cerr << "Read function definition:";
            fn_IR->print(llvm::errs());
            std::cerr << std::endl;
        }
    } else {
        // Skip token for error recovery.
        GetNextToken();
    }
}

void Parser::HandleExtern() {
    if (auto proto_ast = ParseExtern()) {
        if (auto *fn_IR = proto_ast->CodeGen()) {
            fprintf(stderr, "Read extern: ");
            fn_IR->print(llvm::errs());
            std::cerr << std::endl;
        }
    } else {
        // Skip token for error recovery.
        GetNextToken();
    }
}

void Parser::HandleTopLevelExpression() {
    // Evaluate a top-level expression into an anonymous function.
    if (auto fn_ast = ParseTopLevelExpr()) {
        if (auto *fn_IR = fn_ast->CodeGen()) {
            fprintf(stderr, "Read top-level expression:");
            fn_IR->print(llvm::errs());
            fprintf(stderr, "\n");

            // Remove the anonymous expression.
            fn_IR->eraseFromParent();
        }
    } else {
        // Skip token for error recovery.
        GetNextToken();
    }
}

void Parser::MainLoop() {
    while (true) {
        switch (s_current_token_) {
            case Token::tok_eof:
                return;
            case ';': // ignore top-level semicolons.
                GetNextToken();
                break;
            case Token::tok_def:
                HandleDefinition();
                break;
            case Token::tok_extern:
                HandleExtern();
                break;
            default:
                HandleTopLevelExpression();
                break;
        }
    }
}

void Parser::Run() {
    GetNextToken();
    MainLoop();
    CodeGen::s_module->print(llvm::errs(), nullptr);
}

