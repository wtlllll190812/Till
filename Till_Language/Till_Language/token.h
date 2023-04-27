#pragma once
#include<string>
#include<map>
#include <iostream>

struct token
{
	enum token_type
	{
        ILLEGAL = 0,    
        ASSIGN,        // =
        PLUS,	       // +
        MINUS,		   // -
        ASTERISK,	   // *
        SLASH,		   // /
        BANG,		   // !
        LT,			   // <
        LTE,		   // <=
        GT, 		   // >
        GTE,		   // >=
        EQ,			   // ==
        NEQ,		   // !=
        LPAREN,		   // (
        RPAREN,		   // )
        LBRACE,		   // {
        RBRACE,		   // }
        LBRACKET,      // [
        RBRACKET,      // ]
        COMMA,  	   // ,
        COLON,		   // :
        SEMICOLON,	   // ;
        LET,		   // let
        IDENT,		   // ±êÊ¶·û
        FUNCTION,	   // func
        INT,		   // 1343456
        TRUE,   	   // true
        FALSE,  	   // false
        IF,	 	       // if
        ELSE,   	   // else
        RETURN, 	   // return
        STRING, 	   // string
        END,		   // end of file
	};

public:
    token(token_type type, std::string value);
    token();

    bool operator==(const token& rhs) const;
    friend std::ostream& operator<<(std::ostream& out, const token& token);

public:
    static std::map<std::string, token_type> keywords;
    static token_type str2type(const std::string& token);
	token_type type;
	std::string value;
};
std::ostream& operator<<(std::ostream& out, const token& token);
