#include "lexer.hpp"

namespace lexer {
    std::vector<Token> lexicalAnalize(std::string &content) {
        std::vector<Token> tokens;
        Token currentToken;

        return tokens;
    }

    void Token::debug_print() {
        printf("\x1B[34mTOKEN\033[0m \x1B[35m [ %s | %s | %d:%d ] \033[0m", type, content, lineNo, charNo);
    }
}