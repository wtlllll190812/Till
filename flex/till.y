%{
    #include "node.h"
    Program *program; /* the top level root node of our final AST */

    extern int yylex();
    void yyerror(const char *s) { printf("ERROR: %s\n", s); }
%}

/* Represents the many different ways we can access our data */
%union {
    Program*        program;
    Block*          block;
    Statement*      statement;

    Expression*     expr;
    AssignExpr*     assign;
    BoolExpr*       bool;
    IDENTIFIER*     identifier;  
    Object*         object;   
     
    std::string string;
}


%token  IDENTIFIER INTEGER DOUBLE STRING OBJECT             //标识符和变量
%token  EQ NE LT LE GT GE                                   //比较运算符
%token  LPAREN RPAREN LBRACE RBRACE COMMA DOT SEMICOLON     //括号和逗号
%token  PLUS MINUS MUL DIV                                  //算术运算符
%token  ASSIGN                                              //赋值运算符
%token  IF ELSE WHILE FOR                                   //控制语句
%token  LET RETURN FUNC                                     //关键字

// %type  numeric expr
// %type  func_decl_args
// %type  call_args
// %type  program stmts block
// %type  stmt var_decl func_decl
// %type  comparison

/* Operator precedence for mathematical operators */
%left TPLUS TMINUS
%left TMUL TDIV

%type <program>         program
%type <block>           stmts
%type <statement>       stmt
%type <identifier>      IDENTIFIER
%type <object>          OBJECT, INTEGER, DOUBLE, STRING
%type <expression>      assign_expr, if_expr, while_expr, bool_expr, expr

%start program

%%
program:        stmts           { $$->statements=$1; }
                ;

stmts:          stmt            { $$.push_back($1); }
                | stmts stmt    { $$.push_back($2); }
                ;

stmt:           assign_expr     { $$=new Statement($1); }
                ;

assign_expr:    LET IDENTIFIER ASSIGN OBJECT SEMICOLON      { $2 = new Object($4); }
                ;   

if_expr:        IF LPAREN expr RPAREN stmts                 { $$ = new If($3, $5); }
                | IF LPAREN expr RPAREN stmts ELSE stmts    { $$ = new If($3, $5, $7); }
                ;

while_expr:     WHILE LPAREN expr RPAREN stmts              { $$ = new While($3, $5); }
                ;

bool_expr:      OBJECT EQ OBJECT                            { $$ = new Bool($1, $2, $3); }
                | OBJECT NE OBJECT                          { $$ = new Bool($1, $2, $3); }
                | OBJECT LT OBJECT                          { $$ = new Bool($1, $2, $3); }
                | OBJECT LE OBJECT                          { $$ = new Bool($1, $2, $3); }
                | OBJECT GT OBJECT                          { $$ = new Bool($1, $2, $3); }
                | OBJECT GE OBJECT                          { $$ = new Bool($1, $2, $3); }
                ;
%%