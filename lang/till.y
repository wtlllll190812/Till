%{
    #include "ast.h"
    #include <cstdio>
    #include <cstdlib>
    Block *program; /* the top level root node of our final AST */

    extern int yylex();
    void yyerror(const char *s) { printf("ERROR: %s\n", s); }
%}

/* Represents the many different ways we can access our data */
%union {
    Block*          block;
    Statement*      statement;
    Expression*     expression;
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
%type <expression>      assign_expr declare_expr if_expr while_expr 
%type <expression>      expr term factor
%type <object>          value
%type <token>           ASSIGN EQ NE LT LE GT GE ADD SUB MUL DIV assign_operator relational_operator
%type <string>          INTEGER DOUBLE STRING IDENTIFIER

%left ADD SUB 
%left MUL DIV

%start program

%%
program:        block           { program=$1; }
                ;

block:          stmt            { $$=new Block();$$->Append($1); }
                | block stmt    { $1->Append($2); }
                ;

stmt:           declare_expr     { $$=new Statement(*$1); }
                | if_expr       { $$=new Statement(*$1); }
                | while_expr    { $$=new Statement(*$1); }
                | assign_expr   { $$=new Statement(*$1); }
                ;

declare_expr:    LET IDENTIFIER ASSIGN expr SEMICOLON                          { $$ = new DeclareExpression(*$2, *$4); }
                ;   

assign_expr:    IDENTIFIER assign_operator expr SEMICOLON                      { $$ = new AssignExpression(*$1,$2, *$3); }
                ;

if_expr:        IF LPAREN expr RPAREN LBRACE block RBRACE                                           { $$ = new IfExpression(*$3, *$6); }
                | IF LPAREN expr RPAREN LBRACE block RBRACE ELSE LBRACE block RBRACE                { $$ = new IfExpression(*$3, *$6, *$10); }
                ;

while_expr:     WHILE LPAREN expr RPAREN LBRACE block RBRACE                                        { $$ = new WhileExpression(*$3, *$6); }
                ;

expr            : term                                  {$$=$1;}
                | expr ADD term                         {$$=new BinaryExpression(*$1, $2, *$3);}
				| expr SUB term                         {$$=new BinaryExpression(*$1, $2, *$3);}
                | factor relational_operator factor     {$$=new BinaryExpression(*$1, $2, *$3);}
                ;

term            : term MUL factor  		        {$$=new BinaryExpression(*$1, $2, *$3);}
				| term DIV factor 		        {$$=new BinaryExpression(*$1, $2, *$3);}
                | factor                        {$$=$1;}
				;

factor:         LPAREN expr RPAREN             {$$=$2;}
                | value                        {$$=new ConstExpression(*$1);}
                ;

value:          INTEGER             {$$=new Object(*$1);delete $1;}
                | DOUBLE            {$$=new Object(*$1);delete $1;}
                | STRING            {$$=new Object(*$1);delete $1;}
                | IDENTIFIER        {$$=new Object(*$1);delete $1;}
                ;

relational_operator:    EQ
                        | NE
                        | LT
                        | LE
                        | GT
                        | GE
                        ;

assign_operator:        ASSIGN
                        ;
%%