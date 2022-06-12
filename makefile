all:
	g++ Shell.cc Token/Token.h Token/Token.cc Lexer/Lexer.h Lexer/Lexer.cc Parser/Parser.h Parser/Parser.cc -Wall -Wpedantic -Wextra -Werror -o block

lexer:
	g++ Lexer/Lexer.cc -Wall -Wpedantic -Wextra -Werror -o lexerprogram

mathparser:
	g++ MathParser.c
	c Token/Token.h Token/Token.cc Lexer/Lexer.h Lexer/Lexer.cc -Wall -Wpedantic -Wextra -Werror -o mathparser
	make run

clean:
	rm block
	rm a.out
	rm mathparser
	rm Token/*.h.gch
	rm Lexer/*.h.gch

run:
	./block