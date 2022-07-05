#include "Lexer/lexer.hpp"

#include <iostream>
#include <vector>
#include <fstream>

int main(int argc, char **argv) {
    // get all args
    std::vector<std::string> args(argv, argv + argc);
    
    //get all file content
    std::ifstream ifs(args[1]);
    std::string content((std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>()));

    std::vector<lexer::Token> tokens = lexer::lexicalAnalize(content);

    for(lexer::Token t : tokens) {
        t.debugPrint();
    }
}