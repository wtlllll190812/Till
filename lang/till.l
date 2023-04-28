%{
#include 
#include "ast.h"
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
extern "C" int yywrap() { }
%}

%%
[ \t\n]                 ;/* ignore whitespace */
"/*"([^*]|\*[^/])*"*/"  ;/* ignore comments */
"("                     TOKEN(LPAREN); return LPAREN;
")"                     TOKEN(RPAREN); return RPAREN;
"{"                     TOKEN(LBRACE); return LBRACE;
"}"                     TOKEN(RBRACE); return RBRACE;
";"                     TOKEN(SEMICOLON); return SEMICOLON;
","                     TOKEN(COMMA); return COMMA;
"="                     TOKEN(ASSIGN); return ASSIGN;
"=="                    TOKEN(EQ); return EQ;
"!="                    TOKEN(NEQ); return NEQ;
"<"                     TOKEN(LT); return LT;
">"                     TOKEN(GT); return GT;
"<="                    TOKEN(LEQ); return LEQ;
">="                    TOKEN(GEQ); return GEQ;
"+"                     TOKEN(PLUS); return PLUS;
"-"                     TOKEN(MINUS); return MINUS;
"*"                     TOKEN(MUL); return MUL;
"/"                     TOKEN(DIV); return DIV;
"%"                     TOKEN(MOD); return MOD;
"if"                    TOKEN(IF); return IF;
"else"                  TOKEN(ELSE); return ELSE;
"while"                 TOKEN(WHILE); return WHILE;
"return"                TOKEN(RETURN); return RETURN;
[a-zA-Z_][a-zA-Z0-9_]*  SAVE_TOKEN; return IDENTIFIER;
[0-9]+                  SAVE_TOKEN; return INT;
[0-9]+\.[0-9]*          SAVE_TOKEN; return FLOAT;
\"(\\.|[^"\n])*$        SAVE_TOKEN; return STRING;
%%