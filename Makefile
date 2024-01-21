main: main.o
	g++ -o compiler main.o

main.o: main.c
	g++ -c main.c

clean:
	rm *.o compiler