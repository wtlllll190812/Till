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
    Block*                      block;
    Expression*                 expression;
    Object*                     object;   
    std::string*                string;
    std::vector<std::string>*   string_vector;
    std::vector<Expression*>*   expr_vector;

    int                         token;
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
%type <expression>      assign_expr declare_expr if_expr while_expr func_decl return_expr func_call
%type <expression>      expr term factor stmt
%type <object>          value
%type <string_vector>   func_decl_args
%type <expr_vector>     call_args
%type <token>           ASSIGN EQ NE LT LE GT GE ADD SUB MUL DIV assign_operator relational_operator
%type <string>          INTEGER DOUBLE STRING IDENTIFIER

%left ADD SUB 
%left MUL DIV

%start program

%%
//AST根
program:        block           { program=$1; }
                ;

//代码块
block:          stmt            { $$=new Block();$$->add_expr($1); }
                | block stmt    { $1->add_expr($2); }
                ;

//语句
stmt:           declare_expr    { $$=$1; }
                | if_expr       { $$=$1; }
                | while_expr    { $$=$1; }
                | assign_expr   { $$=$1; }
                | func_decl     { $$=$1; }
                | return_expr   { $$=$1; }
                | func_call     { $$=$1; }
                ;
//函数声明
func_decl:      FUNC IDENTIFIER LPAREN func_decl_args RPAREN LBRACE block RBRACE { $$ = new FunctionDeclareExpression(*$2, *$4, *$7); }
                ;

//函数参数
func_decl_args: IDENTIFIER                                  { $$ = new std::vector<std::string>(); $$->push_back(*$1);}
                | func_decl_args COMMA IDENTIFIER           { $1->push_back(*$3);}
                ;

return_expr:    RETURN expr SEMICOLON                       { $$ = new ReturnExpression($2); }
                ;

//函数调用
func_call:      IDENTIFIER LPAREN call_args RPAREN SEMICOLON { $$ = new FunctionCallExpression(*$1, *$3); }
                ;

//函数调用参数
call_args:      expr                                        { $$ = new std::vector<Expression*>(); $$->push_back($1); }
                | call_args COMMA expr                      { $1->push_back($3); }
                ;

//声明语句
declare_expr:    LET IDENTIFIER ASSIGN expr SEMICOLON                          { $$ = new VarDeclareExpression(*$2, $4); }
                ;   

//赋值语句
assign_expr:    IDENTIFIER assign_operator expr SEMICOLON                      { $$ = new AssignExpression(*$1,$2, $3); }
                |IDENTIFIER assign_operator func_call                          { $$ = new AssignExpression(*$1,$2, $3); }
                ;

//关键字
if_expr:        IF LPAREN expr RPAREN LBRACE block RBRACE                                           { $$ = new IfExpression($3, *$6); }
                | IF LPAREN expr RPAREN LBRACE block RBRACE ELSE LBRACE block RBRACE                { $$ = new IfExpression($3, *$6, *$10); }
                ;

while_expr:     WHILE LPAREN expr RPAREN LBRACE block RBRACE                                        { $$ = new WhileExpression($3, *$6); }
                ;



//表达式
expr            : term                                  {$$=$1;}
                | expr ADD term                         {$$=new BinaryExpression($1, $2, $3);}
				| expr SUB term                         {$$=new BinaryExpression($1, $2, $3);}
                | factor relational_operator factor     {$$=new BinaryExpression($1, $2, $3);}
                ;

term            : term MUL factor  		        {$$=new BinaryExpression($1, $2, $3);}
				| term DIV factor 		        {$$=new BinaryExpression($1, $2, $3);}
                | factor                        {$$=$1;}
				;

factor:         LPAREN expr RPAREN             {$$=$2;}
                | value                        {$$=new ValueExpression(*$1);}
                ;

value:          INTEGER             {$$=new Object(*$1,Object::Int);}
                | DOUBLE            {$$=new Object(*$1,Object::Double);}
                | STRING            {$$=new Object(*$1,Object::String);}
                | IDENTIFIER        {$$=new Object(*$1,Object::Variable);}
                ;

//运算符
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