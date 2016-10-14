
main: main.o position.o clist.o
	gcc main.o clist.o position.o -o main

main.o: ./src/main.c ./include/position.h ./include/clist.h
	gcc -c -std=c99 ./src/main.c -o main.o

position.o: ./src/position.c ./include/position.h ./include/clist.h
	gcc -c -std=c99 ./src/position.c -o position.o

clist.o: ./src/clist.c ./include/clist.h
	gcc -c -std=c99 ./src/clist.c -o clist.o

clean:
	rm main.o clist.o position.o ./main
