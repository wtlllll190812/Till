%{
#include<string>
#include "ast.h"
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
#define OPERA(op) (yylval.token = op)
%}
%option noyywrap

%%
[ \t\n]                 ;/* ignore whitespace */
"/*"([^*]|\*[^/])*"*/"  ;/* ignore comments */
"=="                    TOKEN((int)Opera::EQ); return EQ;
"!="                    TOKEN((int)Opera::NE); return NE;
"<"                     TOKEN((int)Opera::LT); return LT;
">"                     TOKEN((int)Opera::GT); return GT;
"<="                    TOKEN((int)Opera::LE); return LE;
">="                    TOKEN((int)Opera::GE); return GE;
"+"                     TOKEN((int)Opera::ADD); return ADD;
"-"                     TOKEN((int)Opera::SUB); return SUB;
"*"                     TOKEN((int)Opera::MUL); return MUL;
"/"                     TOKEN((int)Opera::DIV); return DIV;
"("                     TOKEN(LPAREN); return LPAREN;
")"                     TOKEN(RPAREN); return RPAREN;
"{"                     TOKEN(LBRACE); return LBRACE;
"}"                     TOKEN(RBRACE); return RBRACE;
";"                     TOKEN(SEMICOLON); return SEMICOLON;
","                     TOKEN(COMMA); return COMMA;
"="                     TOKEN(ASSIGN); return ASSIGN;
"scall"                 TOKEN(SCALL); return SCALL;
"func"                  TOKEN(FUNC); return FUNC;
"let"                   TOKEN(LET); return LET;
"if"                    TOKEN(IF); return IF;
"else"                  TOKEN(ELSE); return ELSE;
"while"                 TOKEN(WHILE); return WHILE;
"return"                TOKEN(RETURN); return RETURN;
[a-zA-Z_][a-zA-Z0-9_]*  SAVE_TOKEN; return IDENTIFIER;
[0-9]+                  SAVE_TOKEN; return INTEGER;
[0-9]+\.[0-9]*          SAVE_TOKEN; return DOUBLE;
\"(\\.|[^"\n])*$        SAVE_TOKEN; return STRING;
%%