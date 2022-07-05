#pragma once

#include <iostream>
#include <vector>

namespace lexer {

    // Types of tokens
    enum Type {
        UNDIFINED = -1,
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

        void debug_print();
    };

    // Main lexer method
    std::vector<Token> lexicalAnalize(std::string &input);
}