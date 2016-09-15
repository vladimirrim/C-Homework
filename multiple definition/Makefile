lab1: ./bin/main.o ./bin/util.o ./bin/algorithm.o
	gcc ./bin/main.o ./bin/util.o ./bin/algorithm.o -o lab1

./bin/main.o: ./src/main.c ./include/util.h ./include/algorithm.h
	gcc -c ./src/main.c -o ./bin/main.o
./bin/algorithm.o: ./src/algorithm.c ./include/algorithm.h ./include/util.h 
	gcc -c ./src/algorithm.c -o ./bin/algorithm.o
./bin/util.o: ./src/util.c ./include/util.h 
	gcc -c ./src/util.c -o ./bin/util.o
clean:
	rm ./bin/main.o ./bin/util.o ./bin/io.o ./bin/algorithm.o ./lab1
