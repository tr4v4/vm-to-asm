main: main.o parser.o codewriter.o tools.o
	g++ -o compiler main.o parser.o codewriter.o tools.o

main.o: main.c
	g++ -c main.c

parser.o: parser.c parser.h
	g++ -c parser.c

codewriter.o: codewriter.c codewriter.h
	g++ -c codewriter.c

tools.o: tools.c tools.h
	g++ -c tools.c

clean:
	rm *.o compiler