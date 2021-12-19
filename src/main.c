#include "main.h"

int main()
{
    int n = 10000;
    Matrice A;
    init_matrice(&A, n);
    int i;
    double timeSeq = 0.0;
    double timePara = 0.0;
    //print_matrice(A);

   
    timeSeq = calcul_valeurPropre(A);
    printf("%f secondes\n",timeSeq);

    for (i = 0; i < 16; i++)
    {
        timePara = calcul_valeurProprePara(A,i+2);
        printf("Temps para pour %d threads : %f secondes\n",i+2,timePara);
        i++;
    }

    return 0;
}