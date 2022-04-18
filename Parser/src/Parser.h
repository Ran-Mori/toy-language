//
// Created by Izumi Sakai on 4/17/22.
//

#ifndef TOY_LANGUAGE_PARSER_H
#define TOY_LANGUAGE_PARSER_H

#include <map>
#include "../../Lexer/src/Lexer.h"
#include "../../AST/src/ExprAST.h"
#include "../../AST/src/PrototypeAST.h"
#include "../../AST/src/FunctionAST.h"


class Parser {
public:
    explicit Parser(std::unique_ptr<Lexer> &lexer);

    void Run();

private:
    static int s_current_token_;
    static std::map<char, int> s_binary_op_precedence;
    std::unique_ptr<Lexer> lexer_;

    int GetNextToken();

    int GetTokPrecedence();

    std::unique_ptr<ExprAST> ParseNumberExpr();

    // parser a () expression
    std::unique_ptr<ExprAST> ParseParenExpr();

    std::unique_ptr<ExprAST> ParseExpression();

    std::unique_ptr<ExprAST> ParseIdentifierExpr();

    std::unique_ptr<ExprAST> ParsePrimary();

    std::unique_ptr<ExprAST> ParseBinOpRHS(int expr_prec, std::unique_ptr<ExprAST> lhs);

    std::unique_ptr<PrototypeAST> ParsePrototype();

    std::unique_ptr<FunctionAST> ParseDefinition();

    std::unique_ptr<FunctionAST> ParseTopLevelExpr();

    std::unique_ptr<PrototypeAST> ParseExtern();

    void HandleDefinition();

    void HandleExtern();

    void HandleTopLevelExpression();

    void MainLoop();
};


#endif //TOY_LANGUAGE_PARSER_H
