#ifndef LEXER_H
#define LEXER_H

#include<string>

#include "../Token/Token.h"

class Lexer {
    public:
        Lexer(const char* beg) noexcept;
        Token next() noexcept;

    private:
        Token identifier() noexcept;
        Token number() noexcept;
        Token string() noexcept;
        Token point(char point_type) noexcept;
        Token comment() noexcept;
        Token atom(Token::Kind) noexcept;
        
        char peek() noexcept;
        char get() noexcept;
        void move() noexcept;

        const char* m_beg;
};

#endif