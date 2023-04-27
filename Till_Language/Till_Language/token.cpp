#include "token.h"

static std::map<token::token_type, std::string> s_token_type = 
{
    {token::ILLEGAL, "ILLEGAL"},
    {token::ASSIGN, "ASSIGN"},
    {token::PLUS, "PLUS"},
    {token::MINUS, "MINUS"},
    {token::ASTERISK, "ASTERISK"},
    {token::SLASH, "SLASH"},
    {token::BANG, "BANG"},
    {token::LT, "LT"},
    {token::LTE, "LTE"},
    {token::GT, "GT"},
    {token::GTE, "GTE"},
    {token::EQ, "EQ"},
    {token::NEQ, "NEQ"},
    {token::LPAREN, "LPAREN"},
    {token::RPAREN, "RPAREN"},
    {token::LBRACE, "LBRACE"},
    {token::RBRACE, "RBRACE"},
    {token::LBRACKET, "LBRACKET"},
    {token::RBRACKET, "RBRACKET"},
    {token::COMMA, "COMMA"},
    {token::COLON, "COLON"},
    {token::SEMICOLON, "SEMICOLON"},
    {token::LET, "LET"},
    {token::IDENT, "IDENT"},
    {token::FUNCTION, "FUNCTION"},
    {token::INT, "INT"},
    {token::TRUE, "TRUE"},
    {token::FALSE, "FALSE"},
    {token::IF, "IF"},
    {token::ELSE, "ELSE"},
    {token::RETURN, "RETURN"},
    {token::STRING, "STRING"},
    {token::END, "END"},
};

std::map<std::string, token::token_type> token::keywords = 
{
    {"fn", token::FUNCTION},
    {"let", token::LET},
    {"true", token::TRUE},
    {"false", token::FALSE},
    {"if", token::IF},
    {"else", token::ELSE},
    {"return", token::RETURN},
};


token::token_type token::lookup(const std::string& token)
{
    auto it = token::keywords.find(token);
    
    if (it != token::keywords.end()) 
    {
        return it->second;
    }

    return token_type::IDENT;
}
