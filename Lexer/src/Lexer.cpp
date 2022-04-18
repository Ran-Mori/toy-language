//
// Created by Izumi Sakai on 4/16/22.
//

#include <iostream>
#include <utility>
#include "Lexer.h"
#include "Token.h"

Lexer::Lexer(std::string file_name) : file_name_(std::move(file_name)) {
    if (!IsFileValid()) { exit(1); }
}

Lexer::~Lexer() { is_.close(); }

std::string Lexer::s_identifier_str;
double Lexer::s_number_val = 0.0;

std::string &Lexer::identifier_str() { return s_identifier_str; }

double Lexer::number_val() { return s_number_val; }

bool Lexer::IsFileValid() {
    if (file_name_.empty()) return false;

    is_.open(file_name_);

    if (!is_) {
        std::cerr << "file_name:" << file_name_ << " is_ invalid, please check it again." << std::endl;
        is_.close();
        return false;
    } else {
        return true;
    }
}

int Lexer::GetChar() {
    if (is_.eof()) {
        return Token::tok_eof;
    } else {
        return is_.get();
    }
}

int Lexer::GetToken() {
    static int LastChar = ' ';

    // Skip any whitespace.
    while (isspace(LastChar))
        LastChar = GetChar();

    if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
        s_identifier_str = LastChar;
        while (isalnum((LastChar = GetChar())))
            s_identifier_str += LastChar;

        if (s_identifier_str == "def")
            return Token::tok_def;
        if (s_identifier_str == "extern")
            return Token::tok_extern;
        return Token::tok_identifier;
    }

    if (isdigit(LastChar) || LastChar == '.') { // Number: [0-9.]+
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = GetChar();
        } while (isdigit(LastChar) || LastChar == '.');

        s_number_val = strtod(NumStr.c_str(), nullptr);
        return Token::tok_number;
    }

    if (LastChar == '#') {
        // Comment until end of line.
        do
            LastChar = GetChar();
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
            return GetToken();
    }

    // Check for end of file.  Don't eat the EOF.
    if (LastChar == EOF)
        return Token::tok_eof;

    // Otherwise, just return the character as its ascii value.
    int ThisChar = LastChar;
    LastChar = GetChar();
    return ThisChar;
}
