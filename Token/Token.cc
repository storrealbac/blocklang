#include<string>
#include "Token.h"

Token::Token(Kind kind) noexcept : m_kind{kind} {}

Token::Token(Kind kind, const char* beg, const char* end) noexcept 
    : m_kind{kind}, m_lexeme(beg, std::distance(beg, end)) {}

Token::Token(Kind kind, const char* beg, std::size_t len) noexcept 
    : m_kind{kind}, m_lexeme(beg, len) {}

Token::Kind Token::kind() noexcept { return this->m_kind; }

bool Token::is(Kind kind) const noexcept {
    return this->m_kind == kind;
}

bool Token::is_not(Kind kind) const noexcept {
    return this->m_kind != kind;
}

std::string Token::lexeme() noexcept {
    return this->m_lexeme;
}

void Token::lexeme(std::string lexeme) noexcept {
    this->m_lexeme = std::move(lexeme);
}