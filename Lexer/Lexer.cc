#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>

#include "../Token/Token.h"
#include "Lexer.h"

// Identifiers
bool is_space(char c) noexcept {
    switch (c) {
        case ' ':
        case '\t':
        case '\r':
        case '\n':
            return true;
    }

    return false;
}

bool is_endline(char c) noexcept {
    return (c == '\n') ? true : false;
}

bool is_digit(char c) noexcept {
    if (c >= '0' and c <= '9') return true;
    return false;
}

bool is_valid_char(char c) noexcept {
    if (c >= 'a' and c <= 'z') return true;
    if (c >= 'A' and c <= 'Z') return true;

    return false;
}

bool is_identifier(char c) noexcept {
    if (is_valid_char(c)) return true;
    if (c == '_') return true;
    return false;
}

Lexer::Lexer(const char* beg) noexcept : m_beg{beg} {}

Token Lexer::atom(Token::Kind kind) noexcept { return Token(kind, m_beg++, 1); }

Token Lexer::next() noexcept {
    while(is_space( peek() )) get();

    char c = peek();

    if (c == '\0') return Token(Token::Kind::End, m_beg, 1);
    if (is_identifier(c))   return identifier();
    if (is_digit(c))        return number();
    if (c == '#')           return comment();
    switch (c) {
        case '(':   return atom(Token::Kind::LeftParenthesis);
        case ')':   return atom(Token::Kind::RightParenthesis);
        case '{':   return atom(Token::Kind::LeftBrace);
        case '}':   return atom(Token::Kind::RightBrace);
        case '[':   return atom(Token::Kind::LeftBracket);
        case ']':   return atom(Token::Kind::RightBracket);
        case '<':   return this->point('<');
        case '>':   return this->point('>');
        case '=':   return atom(Token::Kind::Equal);
        case '+':   return atom(Token::Kind::Plus);
        case '-':   return atom(Token::Kind::Minus);
        case '/':   return atom(Token::Kind::Slash);
        case '*':   return atom(Token::Kind::Asterisk);
        case '.':   return atom(Token::Kind::Dot);
        case ',':   return atom(Token::Kind::Comma);
        case ':':   return atom(Token::Kind::Colon);
        case ';':   return atom(Token::Kind::Semicolon);
        case '\'':  return atom(Token::Kind::SimpleQuote);
        case '|':   return atom(Token::Kind::Pipe);
        case '"':   return this->string();
    }

    std::cerr << "[Unexpected] Token: " << c << std::endl;
    return atom(Token::Kind::Unexpected);
}

char Lexer::peek() noexcept {
    return *(this->m_beg);
}

char Lexer::get() noexcept {
    return *(this->m_beg++);
}

void Lexer::move() noexcept {
    ++this->m_beg;
}

const char* block_word      = "block";
const char* break_word      = "break";
const char* continue_word   = "continue";
const char* repeat_word     = "repeat";
const char* return_word     = "return";

Token Lexer::identifier() noexcept {
    const char* start = m_beg, *pos = m_beg;
    this->get();

    while(is_valid_char(this->peek())) this->get();
    
    bool is_block, is_break, is_continue, is_repeat, is_return;
    is_block = is_break = is_continue = is_repeat = is_return = true;

    size_t char_pos = 0;
    while (pos != m_beg) {
        //std::cerr << "[Pos] " << *pos << std::endl;
        if (block_word[char_pos] != *pos and char_pos < 5)
            is_block = 0;

        if (break_word[char_pos] != *pos and char_pos < 5)
            is_break = 0;
        
        if (continue_word[char_pos] != *pos and char_pos < 8)
            is_continue = 0;

        if (repeat_word[char_pos] != *pos and char_pos < 6)
            is_repeat = 0;

        if (return_word[char_pos] != *pos and char_pos < 6)
            is_return = 0;

        pos++, char_pos++;
    }

    /*
    std::cerr << "[Flow control Lexer] Is block? " << is_block << std::endl;
    std::cerr << "[Flow control Lexer] Is break? " << is_break << std::endl;
    std::cerr << "[Flow control Lexer] Is continue? " << is_continue << std::endl;
    std::cerr << "[Flow control Lexer] Is repeat? " << is_repeat << std::endl;
    */

    if (is_block)       return Token(Token::Kind::Block, start, m_beg);
    if (is_break)       return Token(Token::Kind::Break, start, m_beg);
    if (is_continue)    return Token(Token::Kind::Continue, start, m_beg);
    if (is_repeat)      return Token(Token::Kind::Repeat, start, m_beg);
    if (is_return)      return Token(Token::Kind::Return, start, m_beg);
    
    return Token(Token::Kind::Identifier, start, m_beg);
}

Token Lexer::number() noexcept {
    const char* start = m_beg;
    this->get();
    
    bool is_decimal = false;

    while(is_digit(this->peek()) or this->peek() == '.') {
        if (this->peek() == '.' and is_decimal) 
            return Token(Token::Kind::Unexpected, m_beg, 1);

        if (this->peek() == '.') is_decimal = true;
        this->get();
    }

    
    return (is_decimal) ? Token(Token::Kind::Decimal, start, m_beg) : Token(Token::Kind::Integer, start, m_beg);

}

Token Lexer::string() noexcept {

    const char* start = m_beg;
    this->get();

    while (this->peek() != '\"' and this->peek() != '\0') {
        //std::cerr << "[Peeking] " << this->peek() << std::endl;
        this->get();
    }

    if (this->peek() == '\"') return Token(Token::Kind::String, start, ++m_beg);

    std::cerr << "[Error] Expected closed double quotes" << std::endl;
    return atom(Token::Kind::Unexpected);
}

Token Lexer::point(char point_type) noexcept {
    const char* start = m_beg;
    this->get();
    
    //std::cerr << "[Peeking] " << this->peek() << std::endl;

    if (this->peek() == '-' and point_type == '<') {
        this->move();
        return Token(Token::Kind::LeftAssign, start, 2);
    }
    if (this->peek() == '=' and point_type == '<')
        return Token(Token::Kind::LesserEqualThan, start, 2);

    if (this->peek() == '=' and point_type == '>') {
        this->move();
        return Token(Token::Kind::GreaterEqualThan, start, 2);
    }
    if (point_type == '>')
        return Token(Token::Kind::GreaterThan, start, 1);

    if (point_type == '<')
        return Token(Token::Kind::LesserThan, start, 1);

    return Token(Token::Kind::Unexpected, m_beg, 2);
}


Token Lexer::comment() noexcept {
    const char* start = m_beg;
    //    get();

    if (this->peek() == '#') {
        this->get();
        start = m_beg;
        while (this->peek() != '\0') {
            //std::cerr << "[Peeking] " << peek() << std::endl;
            if(is_endline(this->get()))
                return Token(Token::Kind::Comment, start, std::distance(start, m_beg)-1);
        }
    
    }

    std::cerr << "[Error] Unexpected character: " << peek() << std::endl;
    return Token(Token::Kind::Unexpected, m_beg, 1);
}
