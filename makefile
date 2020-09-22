FLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm

all: cluster
clean:
	rm -rf *.o cluster

cluster: stack.o spmat.o BHatMatrix.o linkedList.o graph.o algorithm3.o algorithm2.o algorithm4.o errorHandler.o main.o
	gcc stack.o spmat.o BHatMatrix.o linkedList.o graph.o algorithm3.o algorithm2.o algorithm4.o errorHandler.o main.o -o cluster $(LIBS)

stack.o: stack.c stack.h graph.h errorHandler.h
	gcc $(FLAGS) -c stack.c

spmat.o: spmat.c spmat.h linkedList.h graph.h errorHandler.h
	gcc $(FLAGS) -c spmat.c

linkedList.o: linkedList.c linkedList.h graph.h errorHandler.h
	gcc $(FLAGS) -c linkedList.c

graph.o: graph.c graph.h errorHandler.h
	gcc $(FLAGS) -c graph.c

BHatMatrix.o:  BHatMatrix.c BHatMatrix.h algorithm2.h graph.h spmat.h linkedList.h errorHandler.h
	gcc $(FLAGS) -c BHatMatrix.c

errorHandler.o: errorHandler.c errorHandler.h
	gcc $(FLAGS) -c errorHandler.c

algorithm2.o: algorithm2.c algorithm2.h graph.h BHatMatrix.h errorHandler.h
	gcc $(FLAGS) -c algorithm2.c
	
algorithm3.o: algorithm3.c algorithm3.h algorithm2.h algorithm4.h graph.h spmat.h BHatMatrix.h stack.h errorHandler.h 
	gcc $(FLAGS) -c algorithm3.c

algorithm4.o: algorithm4.c algorithm4.h graph.h BHatMatrix.h errorHandler.h
	gcc $(FLAGS) -c algorithm4.c

main.o: main.c algorithm3.h graph.h errorHandler.h
	gcc $(FLAGS) -c main.c
