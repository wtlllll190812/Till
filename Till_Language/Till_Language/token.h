#pragma once
#include<string>
#include<map>

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
        IDENT,		   // ��ʶ��
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

	static std::map<std::string, token_type> keywords;
	static token_type lookup(const std::string& token);

	token_type type;
	std::string value;
};