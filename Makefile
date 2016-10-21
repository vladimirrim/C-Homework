main: main.o
	gcc main.o -lexpat -o main

main.o: main.c
	gcc -c -std=c99 main.c -o main.o

clean:
	rm main.o clist.o position.o ./main
