CC=gcc
CFLAGS= -Wall -fopenmp
EXE=para
DOSSIER=src
MAIN=$(DOSSIER)/main.c
HEADERS=$(DOSSIER)/matrice.h
PRECOMP=$(DOSSIER)/matrice.o	

all: $(PRECOMP)
	rm -f $(EXE)
	$(CC) $(CFLAGS) $(MAIN) $(PRECOMP) -o $(EXE)

exe: $(PRECOMP)
	clear
	./$(EXE)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f $(DOSSIER)/*.o
	rm -f $(EXE)
