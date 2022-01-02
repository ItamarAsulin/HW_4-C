CC=gcc
AR=ar
OBJECTS_MAIN=main.o
OBJECTS_MAT=my_mat.o
FLAGS= -Wall -g



all: graph

graph: main.o graph2.a
	$(CC) $(FLAGS) -o graph main.o graph2.a

main.o: main.c graph2.h
	$(CC) $(FLAGS) -c main.c

graph2.a: graph2.o
	$(AR) -rcs graph2.a graph2.o

graph2.o: graph2.c
	$(CC) $(FLAGS) -c graph2.c

clean: 
	rm -f *.o *.a *.so graph
