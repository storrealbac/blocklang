#ifndef TOKEN_H
#define TOKEN_H

#include<string>

class Token {
    public:
        enum class Kind {

            Identifier,

            // Flow control
            Block,
            Break,
            Continue,
            Repeat,
            Return,
            
            // Open and close
            LeftBrace,
            RightBrace,
            LeftParenthesis,
            RightParenthesis,
            LeftBracket,
            RightBracket,
            DoubleQuote,
            SimpleQuote,
            Pipe,

            // Comment
            Comment,

            // Datatypes
            Integer,
            Decimal,
            String,

            // Binary operators
            LesserThan,
            LesserEqualThan,
            GreaterThan,
            GreaterEqualThan,
            Equal,
            LeftAssign,
            //RightAssign,

            // Unary operators
            Negation,

            // Aritmethic operator
            Plus,
            Minus,
            Slash,
            Asterisk,
            Dot,
            Comma,
            Colon,
            Semicolon,

            // Error
            End,
            Unexpected
        };
        
        Token(Kind kind) noexcept;
        Token(Kind kind, const char* beg, const char* end) noexcept;
        Token(Kind kind, const char* beg, size_t len) noexcept;
        Kind kind() noexcept;

        bool is(Kind kind) const noexcept;
        bool is_not(Kind kind) const noexcept;

        std::string lexeme() noexcept;
        void lexeme(std::string lexeme) noexcept;
    private:
        Kind m_kind{};
        std::string m_lexeme{}; 
};

#endif
