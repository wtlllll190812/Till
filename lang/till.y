%{
    #include "ast.hpp"
    #include <cstdio>
    #include <cstdlib>
    namespace EzAquarii {
        class Scanner;
    }

    Block *program; /* the top level root node of our final AST */
    
    static int yylex() {
        return scanner.get_next_token();
    }

    // extern int yylex();
    void yyerror(const char *s) { printf("ERROR: %s\n", s); }
%}

/* Represents the many different ways we can access our data */
%union {
    Block*          block;
    Statement*      statement;
    Expression*     expression;
    Identifier*     identifier;
    Object*         object;   
    std::string*    string;
    int             token;
}


%token  IDENTIFIER INTEGER DOUBLE STRING                    //标识符和变量
%token  EQ NE LT LE GT GE                                   //比较运算符
%token  LPAREN RPAREN LBRACE RBRACE COMMA DOT SEMICOLON     //括号和逗号
%token  ADD SUB MUL DIV                                     //算术运算符
%token  ASSIGN                                              //赋值运算符
%token  IF ELSE WHILE FOR                                   //控制语句
%token  LET RETURN FUNC                                     //关键字

// %type  numeric expr
// %type  func_decl_args
// %type  call_args
// %type  program stmts block
// %type  stmt var_decl func_decl
// %type  comparison



%type <block>           block program
%type <statement>       stmt
%type <identifier>      IDENTIFIER
%type <expression>      assign_expr if_expr while_expr expr term
%type <string>          INTEGER DOUBLE STRING 
%type <object>          value
%type <token>           EQ NE LT LE GT GE ADD SUB MUL DIV


%left ADD SUB 
%left MUL DIV
%left ELSE

%start program

%%
program:        block           { program=$1; }
                ;

block:          stmt            { $$=new Block();$$->Append($1); }
                | block stmt    { $1->Append($2); }
                ;

stmt:           assign_expr     { $$=new Statement(*$1); }
                | if_expr       { $$=new Statement(*$1); }
                | while_expr    { $$=new Statement(*$1); }
                ;

assign_expr:    LET IDENTIFIER ASSIGN value SEMICOLON       { $$ = new AssignExpression(*$2, *$4); }
                ;   

if_expr:        IF LPAREN expr RPAREN block                 { $$ = new IfExpression(*$3, *$5); }
                | IF LPAREN expr RPAREN block ELSE block    %prec ELSE { $$ = new IfExpression(*$3, *$5, *$7); }
                ;

while_expr:     WHILE LPAREN expr RPAREN block              { $$ = new WhileExpression(*$3, *$5); }
                ;

expr            : term 
                | expr ADD term   {$$=new BinaryExpression(*$1, $2, *$3);}
				| expr SUB term   {$$=new BinaryExpression(*$1, $2, *$3);}
                ;

term            : value SEMICOLON               {$$=new ConstExpression(*$1);}
				| term MUL value SEMICOLON 		{$$=new BinaryExpression(*$1, $2, *$3);}
				| term DIV value SEMICOLON		{$$=new BinaryExpression(*$1, $2, *$3);}
				;

value:          INTEGER             {$$=new Object(*$1);delete $1;}
                | DOUBLE            {$$=new Object(*$1);delete $1;}
                | STRING            {$$=new Object(*$1);delete $1;}
                | IDENTIFIER        {$$=$1->get_value();}
                ;
%%