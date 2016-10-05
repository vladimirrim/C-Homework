PROG=MergeSort
LIST=$(addprefix $(./bin/)/, $(PROG))

MergeSor: main.o mergesort.o
	gcc main.o mergesort.o -o MergeSort

main.o: ./src/main.c ./include/merge.h
	gcc -c ./src/main.c -o main.o

mergesort.o: ./src/mergesort.c ./include/merge.h
	gcc -c ./src/mergesort.c -o mergesort.o

clean:
	rm main.o mergesort.o ./MergeSort
