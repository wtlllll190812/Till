%{
#include<string>
#include "ast.hpp"
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
%}

%option noyywrap
%option yyclass="Scanner"
%option prefix="EzAquarii_"

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
"!="                    TOKEN(NE); return NE;
"<"                     TOKEN(LT); return LT;
">"                     TOKEN(GT); return GT;
"<="                    TOKEN(LE); return LE;
">="                    TOKEN(GE); return GE;
"+"                     TOKEN(ADD); return ADD;
"-"                     TOKEN(SUB); return SUB;
"*"                     TOKEN(MUL); return MUL;
"/"                     TOKEN(DIV); return DIV;
"if"                    TOKEN(IF); return IF;
"else"                  TOKEN(ELSE); return ELSE;
"while"                 TOKEN(WHILE); return WHILE;
"return"                TOKEN(RETURN); return RETURN;
[a-zA-Z_][a-zA-Z0-9_]*  SAVE_TOKEN; return IDENTIFIER;
[0-9]+                  SAVE_TOKEN; return INTEGER;
[0-9]+\.[0-9]*          SAVE_TOKEN; return DOUBLE;
\"(\\.|[^"\n])*$        SAVE_TOKEN; return STRING;
%%