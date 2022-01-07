CC=gcc
CFLAGS= -Wall -fopenmp
EXE=para
DOSSIER=src

all: $(DOSSIER)/main.o $(DOSSIER)/matrice.o
	rm -f $(EXE)
	$(CC) $(CFLAGS) $(DOSSIER)/main.o $(DOSSIER)/matrice.o -o $(EXE)

exe: $(DOSSIER)/matrice.o $(DOSSIER)/main.o
	clear
	./$(EXE)

main.o: $(DOSSIER)/main.c $(DOSSIER)/main.h
	$(CC) $(CFLAGS) -c $(DOSSIER)/main.c

matrice.o: matrice.c matrice.h
	$(CC) $(CFLAGS) -c $(DOSSIER)/matrice.c

clean:
	rm -f *.o
	rm -f $(EXE)
