#pragma once

#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>

namespace lexer {

    const std::string keywordsList[] = {"if", "elif", "else", "loop", "int", "float", "string", "bool", "#"};
    const char operatorsList[] = {'+', '-', '*', '/', '%', '='};
    const char logicalsList[] = {'>', '<', '&', '|', '!'};
    const char punctuationsList[] = {'(', ')', '{', '}', '[', ']', ';', ':', ',', '.', '"', '\''};

    // Types of tokens
    enum Type {
        UNDEFINED = -1,
        IDENTIFIER = 0,
        KEYWORD = 1,
        OPERATOR = 2,
        LOGICAL = 3,
        PUNCTUATION = 4,
        INTEGER = 5,
        FLOAT = 6,
        CHAR = 7,
        STRING = 8,
    };

    struct Token {
        enum Type type;
        std::string content;

        int lineNo;
        int charNo;

        void debugPrint();
    };

    // Main lexer method
    std::vector<Token> lexicalAnalize(std::string &input);
}