all: my_malloc

my_malloc: my_malloc.o main.o
	gcc -o my_malloc my_malloc.o main.o

my_malloc.o: my_malloc.c my_malloc.h
	gcc -c my_malloc.c

main.o: main.c
	gcc -c main.c

clean:
	rm -f my_malloc.o main.o
