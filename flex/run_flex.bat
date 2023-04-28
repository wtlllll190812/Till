bison --yacc -dv till.y
flex till.l
gcc -o till y.tab.c lex.yy.c