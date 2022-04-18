
#include <iostream>
#include "Lexer/src/Lexer.h"
#include "Parser/src/Parser.h"
#include "Codegen/src/CodeGen.h"


int main() {
    std::string file_name = "../toy.txt";
    auto lexer = std::make_unique<Lexer>(file_name);
    auto parser = std::make_unique<Parser>(lexer);
    parser->Run();
    return 0;
}


