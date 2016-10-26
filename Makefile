main: main.o parser.o phonebook.o
	gcc main.o parser.o phonebook.o -lexpat -o main

main.o: ./src/main.c ./include/phonebook.h
	gcc -c -std=c99 ./src/main.c -o main.o

phonebook.o: ./src/phonebook.c ./include/phonebook.h ./include/names.h
	gcc -c -std=c99 ./src/phonebook.c -o phonebook.o

parser.o: ./src/parser.c ./include/phonebook.h
	gcc -c -std=c99 ./src/parser.c -o parser.o
