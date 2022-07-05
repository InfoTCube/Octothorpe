#include "lexer.hpp"

namespace lexer {
    std::vector<Token> lexicalAnalize(std::string &content) {
        std::vector<Token> tokens;
        int cLineNo = 1, cCharNo=1;
        Token currentToken { Type::UNDEFINED, "", cLineNo, cCharNo };
        char cChar;

        for(int i=0; i<content.length(); ++i) {
            cChar = content[i];

            if(cChar == '"') {
                //parse string
                currentToken = { Type::STRING, "", cLineNo, cCharNo };
                ++i; ++cCharNo;
                cChar = content[i]; 
    
                while(cChar != '"') {
                    if(cChar == '\\') {
                        ++i; ++cCharNo;
                        cChar = content[i];
                        if(cChar == 'n')
                            currentToken.content.append(1, '\n');
                        else if(cChar == 't') 
                            currentToken.content.append(1, '\t');
                    } else {
                        currentToken.content.append(1, cChar);
                    }
                    ++i; ++cCharNo;
                    cChar = content[i];
                }

                tokens.emplace_back(currentToken);
                currentToken = { Type::UNDEFINED, "", cLineNo, cCharNo};

            } else if(isspace(cChar)) {
                //parse whitespace
                if (currentToken.type != Type::UNDEFINED) {
                    tokens.emplace_back(currentToken);
                    currentToken = { Type::UNDEFINED, "", cLineNo, cCharNo };
                }
                if(cChar == '\n') { ++cLineNo; cCharNo=0; }

            } else if(isdigit(cChar)) {
                //parse numbers
                currentToken = { Type::INTEGER, "", cLineNo, cCharNo };
                while(isdigit(cChar) || cChar == '_' || cChar == '.') {
                    if(isdigit(cChar)) {
                        currentToken.content += cChar;
                    } else if(cChar == '.') {
                        if(currentToken.type == Type::INTEGER) {
                            currentToken.type = Type::FLOAT;
                            currentToken.content += cChar;
                        }
                    }

                    ++i; ++cCharNo;
                    cChar = content[i];
                }

                tokens.emplace_back(currentToken);
                currentToken = { Type::UNDEFINED, "", cLineNo, cCharNo};

            } else if(std::find(std::begin(operatorsList), std::end(operatorsList), cChar) != std::end(operatorsList)) {
                //parse operators
            } else if(std::find(std::begin(logicalsList), std::end(logicalsList), cChar) != std::end(logicalsList)) {
                //parse logicals
            } else if(std::find(std::begin(punctuationsList), std::end(punctuationsList), cChar) != std::end(punctuationsList)) {
                //parse punctuations
            } else {
                //parse indetifier or keyword 
            }

            ++cCharNo;
        }

        if (currentToken.type != Type::UNDEFINED)
            tokens.emplace_back(currentToken);

        return tokens;
    }

    void Token::debugPrint() {
        printf("\x1B[34mTOKEN\033[0m \x1B[35m [ %d | %s | %d:%d ] \033[0m\n", type, content.c_str(), lineNo, charNo);
    }
}