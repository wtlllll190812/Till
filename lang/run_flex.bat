bison -d -o ../out/parser.cpp till.y
flex -+ -o../out/lexer.cpp till.l
@REM # @REM gcc -o till y.tab.c lex.yy.c