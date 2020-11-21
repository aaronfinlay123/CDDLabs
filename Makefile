#Developer: Aaron Finlay
#Date:  20/11/20
#Use: Make file used to manage the compilattion, deubg and execution of L4
#Equivalent(?) to a proj file in VS Code
CC=g++

CGFLAGS= -std=c++11 -pthread -I.

OBJFILES=Semaphore.o main.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

BUILD: $(OBJFILES)
	$(CC) -o mutex $(OBJFILES) $(CGFLAGS)

DEBUG: $(OBJFILES)
	DEBUGFLAGS= -g -O0
	$(CC) -o mutex $(OBJFILES) $(CFLAGS) $(DEBUGFLAGS)

CLEAN:
	rm  *.o
INSTALL: cp ./mutex ~/bin/
