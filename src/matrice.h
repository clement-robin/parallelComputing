#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

typedef struct Matrice Matrice;

struct Matrice
{
    int n;
    float *tabMatrice;
};

void init_matrice(Matrice *matrice, int parN);

void print_matrice(Matrice matrice);

float algo_puissanceItere(Matrice A, float *v, int n, int m);

void calcul_valeurPropre(Matrice A, int m);

float algo_puissanceIterePara(Matrice A, float *v, int n, int m);

void calcul_valeurProprePara(Matrice A, int m);