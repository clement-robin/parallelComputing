#include "main.h"

int main()
{
    int n = 3, m=10;
    Matrice A;
    init_matrice(&A, n);
    print_matrice(A);

    calcul_valeurPropre(A,m);

    calcul_valeurProprePara(A,m);

    return 0;
}