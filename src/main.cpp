#include <iostream>
#include <fstream>
#include <streambuf>
#include "globals.hpp"
#include "parser.hpp"
#include "expression.hpp"

int main (int argc, char **argv)
{
    for (int i = 1; i < argc; i++) {
        char *filename = argv[i];

        std::ifstream file(filename);
        std::string content;

        file.seekg(0, std::ios::end);
        content.reserve(file.tellg());
        file.seekg(0, std::ios::beg);

        content.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::cout << content << std::endl; //TODO: For debugging only. Oskar Mendel 2018-03-29

        TheModule = llvm::make_unique<llvm::Module>("Brk", TheContext);


        // std::unique_ptr<Expression> e = std::unique_ptr<Expression>{new IntegerExpression(9)};
        // std::unique_ptr<Expression> e1 = std::unique_ptr<Expression>{new IntegerExpression(1)};
        // AddExpression b(std::move(e), std::move(e1));
        // auto ir = b.codegen();
        // ir->print(llvm::errs(), nullptr);

        //Lexer lexer(content);
        Parser parser(content);
        parser.parse();
        parser.parse();
        parser.parse();
        parser.parse();
        parser.parse();
        parser.parse();
        parser.parse();
        parser.parse();
        parser.parse();
        parser.parse();
        parser.parse();
        parser.parse();
        
        // Token t = lexer.getToken();
        // std::cout << "TokenKeyword: " << Tokens[t.type].tokenString << ": " << t.str << std::endl;
        // //
        // while(t.type != TOKEN_EOF) {
        //     t = lexer.getToken();
        //     if (t.type == TOKEN_FLOAT64) {
        //         std::cout << "TokenKeyword: " << Tokens[t.type].tokenString << ": " << t.float64Val << std::endl;
        //     } else {
        //         std::cout << "TokenKeyword: " << Tokens[t.type].tokenString << ": " << t.str << std::endl;
        //     }
        // }
    }

    return 0;
}