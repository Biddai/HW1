all: clean compile link

link:
	g++ -o bin/test bin/parser.o

compile:
	g++ -g -Wall -Weffc++ -c -Iinclude -o bin/parser.o src/parser.cpp

clean:
	rm -f bin/*
