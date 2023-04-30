include=C:\Windows\GnuWin32\FlexAndBison

OBJS= 	lexer.o 	\
		parser.o 	\
		till.o 		\
		ast.o 		\
		env.o 		\
		object.o 	\

till.exe:${OBJS}
	g++ ${CFLAG} -o $@ $^ -I $(include) 

%.o: src/%.cpp
	g++ ${CFLAG} -c -o $@ $< -I $(include) 

src/%.cpp:
	parser
	lexer

parser:
	echo "Generating parser..."
	win_bison -d -o src/parser.cpp lang/till.y -Wcounterexamples --debug

lexer:
	echo "Generating lexer..."
	win_flex -osrc/lexer.cpp lang/till.l

clean:
	echo "Cleaning..."
	$(RM) -rf till.exe $(OBJS)

cleanAll:
	echo "Cleaning..."
	$(RM) -rf src/parser.cpp src/parser.hpp src/lexer.cpp till.exe $(OBJS)  