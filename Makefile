CC=gcc
CFLAGS= -Wall -fopenmp
EXE=para
DOSSIER=src
HEADERS=$(DOSSIER)/main.h $(DOSSIER)/matrice.h
PRECOMP=$(DOSSIER)/main.o $(DOSSIER)/matrice.o	

all: $(PRECOMP)
	rm -f $(EXE)
	$(CC) $(CFLAGS) $(PRECOMP) -o $(EXE)

exe: $(PRECOMP)
	clear
	./$(EXE)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f $(DOSSIER)/*.o
	rm -f $(EXE)
