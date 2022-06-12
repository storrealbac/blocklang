#include<iostream>
#include<iomanip>
#include<map>
#include<string>

#include "Parser.h"
#include "../Lexer/Lexer.h"
#include "../Token/Token.h"

/* Syntax tree

    -> Identifier
        -> Assign
            -> Datatype info
        -> Function
            -> Parameters
*/

Parser::Parser(Lexer &lex) noexcept {
    
    Token token = lex.next();
    while ( token.is_not(Token::Kind::End) and token.is_not(Token::Kind::Unexpected) ) {
        //std::cout << token.kind() << "    \t| " << token.lexeme() << std::endl;
        //std::cout << std::setw(16) << token.kind() << " | " << token.lexeme() << std::endl;

        /*
        std::cout << "<Parser> Lexeme: " << token.lexeme();
        if (Token::Kind::Integer == token.kind() ) std::cout<< " <Integer>";
        if (Token::Kind::Identifier == token.kind() ) std::cout<< " <Identifier>";
        if (Token::Kind::LeftAssign == token.kind() ) std::cout<< " <LeftAssign>";
        */

        if (Token::Kind::Identifier == token.kind()) {
            std::string identifier_name = token.lexeme();

            token = lex.next();

            if (token.kind() == Token::Kind::Unexpected) {
                std::cerr << "[Error] Unexpected end of file" << std::endl;
                break;
            }         

            if (Token::Kind::LeftAssign == token.kind()) {
                
                token = lex.next();
                if (token.kind() == Token::Kind::Unexpected) {
                    //std::cerr << "[Error] Unexpected end of file" << std::endl;
                    break;
                }      

                if (token.is(Token::Kind::Integer)) {
                    //std::cout << "[Expression found] int64_t " << identifier_name << " = " << token.lexeme() << ";" << std::endl;
                    std::cout << "int64_t " << identifier_name << " = " << token.lexeme() << ";";
                    continue;
                }

                if (token.is(Token::Kind::String)) {
                    //std::cout << "[Expression found] std::string " << identifier_name << " = " << token.lexeme() << ";" << std::endl;
                    std::cout << "std::string " << identifier_name << " = " << token.lexeme() << ";";
                    continue;
                }

                if (token.is(Token::Kind::Decimal)) {
                    //std::cout << "[Expression found] long double " << identifier_name << " = " << token.lexeme() << ";" << std::endl;
                    std::cout << "long double " << identifier_name << " = " << token.lexeme() << ";";
                    continue;
                }

                continue;
            }

            if (Token::Kind::Pipe == token.kind()) {
                
                token = lex.next();
                if (identifier_name == "print") {
                    //std::cout << "Pipe found" << std::endl;
                    std::string parameters = "";

                    while (token.kind() != Token::Kind::Pipe) {
                        if (token.is(Token::Kind::End) and token.is(Token::Kind::Unexpected))
                            break;
                        parameters += token.lexeme();
                        token = lex.next();
                    }

                    //std::cout << "[Expression found] std::cout << " << parameters << " << std::endl" <<std::endl;         
                    std::cout << "std::cout << " << parameters << " << std::endl;";         
                }
                continue;
            }
        } /*else {
            // Unexpected token
            std::cerr << "[Error] Unexpected token" << std::endl;
            break;
        }*/
        
        token = lex.next();
    }

    //std::cout << "Compiled!" << std::e    ndl;
}
