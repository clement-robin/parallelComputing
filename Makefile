CC=gcc
CFLAGS= -Wall -fopenmp
EXE=para
DOSSIER=src
MAIN=$(DOSSIER)/Deshayes-Lucas_Robin-Clement_codeSourcePUISS.c
	

all: $(PRECOMP)
	rm -f $(EXE)
	$(CC) $(CFLAGS) $(MAIN) -o $(EXE)
	./$(EXE)




clean:
	rm -f $(EXE)
