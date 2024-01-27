main: main.o parser.o tools.o
	g++ -o compiler main.o parser.o tools.o

main.o: main.c
	g++ -c main.c

parser.o: parser.c parser.h
	g++ -c parser.c

tools.o: tools.c tools.h
	g++ -c tools.c

clean:
	rm *.o compiler