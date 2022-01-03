CC=gcc
AR=ar
OBJECTS_MAIN=main.o
OBJECTS_MAT=my_mat.o
FLAGS= -Wall -g



all: graph

graph: main.o graph.a
	$(CC) $(FLAGS) -o graph main.o graph.a

main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c

graph.a: graph.o queue.o
	$(AR) -rcs graph.a graph.o queue.o

graph.o: graph.c queue.h
	$(CC) $(FLAGS) -c graph.c

queue.o: queue.c
	$(CC) $(FLAGS) -c queue.c

clean: 
	rm -f *.o *.a *.so graph
