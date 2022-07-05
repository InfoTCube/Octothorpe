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
                if (currentToken.type != Type::UNDEFINED) { tokens.emplace_back(currentToken); }

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
                if (currentToken.type != Type::UNDEFINED) { tokens.emplace_back(currentToken); }

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
                --i; --cCharNo;
                cChar = content[i];
                currentToken = { Type::UNDEFINED, "", cLineNo, cCharNo };

            } else if(std::find(std::begin(operatorsList), std::end(operatorsList), cChar) != std::end(operatorsList)) {
                //parse operators
                if (currentToken.type != Type::UNDEFINED) { tokens.emplace_back(currentToken); }

                currentToken = { Type::OPERATOR, "", cLineNo, cCharNo };
                currentToken.content = cChar;
                if(i+1<content.length()) {
                    switch(cChar) {
                        case '+':
                            if(content[i+1] == '+' || content[i+1] == '=') { currentToken.content += content[i+1]; ++i; ++cCharNo; cChar = content[i]; }
                            break;
                        case '-':
                            if(content[i+1] == '-' || content[i+1] == '=') { currentToken.content += content[i+1]; ++i; ++cCharNo; cChar = content[i]; }
                            break;
                        case '*':
                            if(content[i+1] == '*' || content[i+1] == '=') { currentToken.content += content[i+1]; ++i; ++cCharNo; cChar = content[i]; }
                            break;
                        case '/':
                            if(content[i+1] == '=') { currentToken.content += '='; ++i; ++cCharNo; cChar = content[i]; }
                            break;
                        case '%':
                            if(content[i+1] == '=') { currentToken.content += '='; ++i; ++cCharNo; cChar = content[i]; }
                            break;
                        case '=':
                            if(content[i+1] == '=') {
                                currentToken.content += '=';
                                currentToken.type = Type::LOGICAL;
                                ++i; ++cCharNo; cChar = content[i];
                            }
                            break;
                    }
                }

                tokens.emplace_back(currentToken);
                currentToken = { Type::UNDEFINED, "", cLineNo, cCharNo};

            } else if(std::find(std::begin(logicalsList), std::end(logicalsList), cChar) != std::end(logicalsList)) {
                //parse logicals
                if (currentToken.type != Type::UNDEFINED) { tokens.emplace_back(currentToken); }

                currentToken = { Type::LOGICAL, "", cLineNo, cCharNo };
                currentToken.content = cChar;
                if(i+1<content.length()) {
                    switch(cChar) {
                        case '<':
                            if(content[i+1] == '=') { currentToken.content += '='; ++i; ++cCharNo; cChar = content[i]; }
                            break;
                        case '>':
                            if(content[i+1] == '=') { currentToken.content += '='; ++i; ++cCharNo; cChar = content[i]; }
                            break;
                        case '!':
                            if(content[i+1] == '=') { currentToken.content += '='; ++i; ++cCharNo; cChar = content[i]; }
                            break;
                        case '&':
                            if(content[i+1] == '&') { currentToken.content += '&'; ++i; ++cCharNo; cChar = content[i]; }
                            break;
                        case '|':
                            if(content[i+1] == '|') { currentToken.content += '|'; ++i; ++cCharNo; cChar = content[i]; }
                            break;
                    }
                }

                tokens.emplace_back(currentToken);
                currentToken = { Type::UNDEFINED, "", cLineNo, cCharNo};

            } else if(std::find(std::begin(punctuationsList), std::end(punctuationsList), cChar) != std::end(punctuationsList)) {
                //parse punctuations
                if (currentToken.type != Type::UNDEFINED) { tokens.emplace_back(currentToken); }

                currentToken = { Type::PUNCTUATION, "", cLineNo, cCharNo };
                currentToken.content = cChar;
                tokens.emplace_back(currentToken);
                currentToken = { Type::UNDEFINED, "", cLineNo, cCharNo};

            } else {
                //parse indetifier or keyword 
                if (currentToken.type == Type::UNDEFINED) {
                    currentToken.type = Type::IDENTIFIER;
                    currentToken.content.append(1, cChar);
                } else if (currentToken.type == Type::IDENTIFIER) {
                    currentToken.content.append(1, cChar);
                } else if(currentToken.type != Type::UNDEFINED){
                    tokens.emplace_back(currentToken);
                    currentToken.type = Type::IDENTIFIER;
                    currentToken.content = cChar;
                }
            }

            ++cCharNo;
        }

        if (currentToken.type != Type::UNDEFINED)
            tokens.emplace_back(currentToken);

        for(int i=0; i<tokens.size(); ++i)
            if(std::find(std::begin(keywordsList), std::end(keywordsList), tokens[i].content) != std::end(keywordsList)) { tokens[i].type = Type::KEYWORD; }

        return tokens;
    }

    void Token::debugPrint() {
        printf("\x1B[34mTOKEN\033[0m \x1B[35m [ %d | %s | %d:%d ] \033[0m\n", type, content.c_str(), lineNo, charNo);
    }
}