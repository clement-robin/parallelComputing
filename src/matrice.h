#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

typedef struct Matrice Matrice;

struct Matrice
{
    int n;
    double **tabMatrice;
};

void init_matrice(Matrice *matrice, int parN);

void print_matrice(Matrice matrice);

double algo_puissanceItere(Matrice A, double *v, int n);

double calcul_valeurPropre(Matrice A);

double algo_puissanceIterePara(Matrice A, double *v, int n, int num_th);

double calcul_valeurProprePara(Matrice A, int num_th);