#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>

#include "Lexer/Lexer.h"
#include "Token/Token.h"
#include "Parser/Parser.h"

std::ostream& operator<<(std::ostream& os, const Token::Kind& kind) {
    static const char* const names[] {
        "Identifier",

        "Block",
        "Break",
        "Continue",
        "Repeat",
        "Return",
        
        "LeftBrace",
        "RightBrace",
        "LeftParenthesis",
        "RightParenthesis",
        "LeftBracket",
        "RightBracket",
        "DoubleQuote",
        "SimpleQuote",
        "Pipe",

        "Comment",

        "Integer",
        "Decimal",
        "String",

        "LesserThan",
        "LesserEqualThan",
        "GreaterThan",
        "GreaterEqualThan",
        "Equal",
        "LeftAssign",
        //"RightAssign",

        "Negation",

        "Plus",
        "Minus",
        "Slash",
        "Asterisk",
        "Dot",
        "Comma",
        "Colon",
        "Semicolon",

        "End",
        "Unexpected"
    };

    return os << names[static_cast<int>(kind)];
}

/*
void shell() {

    std::cout << "┌─────────────────┐" << std::endl;
    std::cout << "| Blocklang 1.0.0 |" << std::endl;
    std::cout << "|  on GNU/Linux   |" << std::endl;
    std::cout << "└─────────────────┘" << std::endl;

    std::cout << "Type \"help\" for help" << std::endl;

    std::string line;
    while (1) {
        std::cout << "> ";
        std::getline(std::cin, line);        
    }

}
*/

void run(std::string filename) {
    std::cerr << "[Blocklang] Openning: " << filename << std::endl;

    std::cout << "#include<iostream> \n int main() {";

    std::ifstream file;
    file.open(filename);

    if (file.fail()) {
        std::cout << "[Error] The file doesnt exist!" << std::endl;
        return;
    }

    std::string code;

    // character
    char c;
    while(file.get(c))
        code.push_back(c);

    Lexer lex(code.c_str());
    auto token = lex.next();
    while ( token.is_not(Token::Kind::End) and token.is_not(Token::Kind::Unexpected) ) {
        //std::cout << token.kind() << "    \t| " << token.lexeme() << std::endl;
        //std::cout << std::setw(16) << token.kind() << " | " << token.lexeme() << std::endl;
        token = lex.next();
    }

    Lexer parser_lexer(code.c_str());
    Parser pars(parser_lexer);

    std::cout << " return 0;}";
}

int32_t main(int32_t argc, char const *argv[]) {

    if (argc <= 1) {
        std::cout << "[Error] Not enough arguments" << std::endl;
        return 0;
    }

    run(argv[1]);

    return 0;
}