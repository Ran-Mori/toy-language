//
// Created by Izumi Sakai on 4/16/22.
//

#ifndef TOY_LANGUAGE_LEXER_H
#define TOY_LANGUAGE_LEXER_H

#include <string>
#include <fstream>

class Lexer {
public:
    explicit Lexer(std::string file_name);

    ~Lexer();

    int GetToken();

    static std::string &identifier_str();

    static double number_val();

private:
    static std::string s_identifier_str;
    static double s_number_val;
    std::string file_name_;
    std::ifstream is_;

    bool IsFileValid();

    int GetChar();
};

#endif //TOY_LANGUAGE_LEXER_H
