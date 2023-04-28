win_bison -d -o ../src/parser.cpp till.y
win_flex -+ -o../src/lexer.cpp till.l
clang++ -c -o parser.o ../src/parser.cpp -I C:\Windows\GnuWin32\FlexAndBison
clang++ -c -o lexer.o ../src/lexer.cpp -I C:\Windows\GnuWin32\FlexAndBison
clang++ -o till lexer.o parser.o ../src/till.cpp -I C:\Windows\GnuWin32\FlexAndBison
