CC=gcc
CFLAGS= -Wall -fopenmp
EXE=para

all: main.o matrice.o
	rm -f $(EXE)
	$(CC) $(CFLAGS) main.o matrice.o -o $(EXE)

exe: matrice.o main.o
	clear
	./$(EXE)

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

matrice.o: matrice.c matrice.h
	$(CC) $(CFLAGS) -c matrice.c

clean:
	rm -f *.o
	rm -f $(EXE)