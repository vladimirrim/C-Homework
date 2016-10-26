<<<<<<< HEAD
main: main.o parser.o phonebook.o
	gcc main.o parser.o phonebook.o -lexpat -o main

main.o: ./src/main.c ./include/phonebook.h
	gcc -c -std=c99 ./src/main.c -o main.o

phonebook.o: ./src/phonebook.c ./include/phonebook.h ./include/names.h
	gcc -c -std=c99 ./src/phonebook.c -o phonebook.o

parser.o: ./src/parser.c ./include/phonebook.h
	gcc -c -std=c99 ./src/parser.c -o parser.o
=======
main: main.o
	gcc main.o -lexpat -o main

main.o: main.c
	gcc -c -std=c99 main.c -o main.o

clean:
	rm main.o clist.o position.o ./main
>>>>>>> 52bfa87d74c8bf47fc4467e13b45f2fdc415f0b1
