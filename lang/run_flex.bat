win_bison -d -o ../src/parser.cpp till.y
clang -c ../src/parser.cpp -o ../src/parser.o  -I C:\Windows\GnuWin32\FlexAndBison
win_flex -+ -o../src/lexer.cpp till.l
clang -c ../src/lexer.cpp -o ../src/lexer.o  -I C:\Windows\GnuWin32\FlexAndBison
clang -o till ../src/parser.o ../src/lexer.o