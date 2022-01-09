#include "matrice.h"

int main()
{   
    int n,i;
    int rand = 1;
    int ex;
    int th;
    float conv;
    Matrice A;

    double timeExec = 0.0;

    printf("Tapez la taille de la matrice carré souhaitez\n");
    scanf("%d",&n);
    init_matrice(&A, n);

    do {

        printf("Voulez vous tapez les valeurs ? (0 : oui, 1 : non)\n");
        scanf("%d",&rand);
        init_val(&A,rand);
        printf("Taux de convergence souhaiter\n");
        scanf("%f",&conv);
        printf("Execution souhaiter (0 : seq, 1 : para)\n");
        scanf("%d",&ex);
        
        if (ex == 1)
        {
            printf("Nombre de Thread\n");
            scanf("%d",&th);
            if (n<=10)
            {
                print_matrice(A);
            }
            timeExec = calcul_valeurProprePara(A,th,conv);
            printf("Temps d'execution de l'algo en parralele avec %d threads : %f (en s)\n\n\n\n",th,timeExec);
        }
        else
        {
            if (n<=10)
            {
                print_matrice(A);
            }
            timeExec = calcul_valeurPropre(A,conv);
            printf("Temps d'execution de l'algo en sequentielle : %f (en s)\n\n\n\n",timeExec);
        }
        

        /*for (i = 2; i < 18; i++)
        {
           timeExec = calcul_valeurProprePara(A,i,conv);
           i++;
           printf("%f\n",timeExec);
        }   */
       
        suppr_matrice(&A);
        printf("Tapez la taille de la matrice carré souhaitez (-1 si vous voulez arreter)\n");
        scanf("%d",&n);
        init_matrice(&A, n);
    }
    while (n != -1);

    return 0;
}