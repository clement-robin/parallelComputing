#include "matrice.h"

void init_matrice(Matrice *matrice, int parN)
{
    matrice->n = parN;

    matrice->tabMatrice = NULL;

    matrice->tabMatrice = malloc((parN * parN) * sizeof(float));

    for (int i = 1; i <= parN; i++)
    {
        for (int j = 1; j <= parN; j++)
        {
            printf("A[%d][%d]=", i,j);
            scanf("%f",&matrice->tabMatrice[(i-1) * parN + j]);
            //matrice->tabMatrice[i * j] = i+j-1;
        }
    }
}

void print_matrice(Matrice matrice)
{
    printf("\nDISPLAY MATRIX\n");
    for (int i = 1; i <= matrice.n; i++)
    {
        printf("[");
        for (int j = 1; j <= matrice.n; j++)
        {
            printf(" %.3f ", matrice.tabMatrice[(i-1) * matrice.n + j]);
        }
        printf("]\n");
    }
}

float algo_puissanceItere(Matrice A, float *v, int n, int m){
    
    int i,j,k;
    float vk[n+1],ak;

    for (i = 0; i < m; i++) { // JUSQU'A CONVERGENCE

        //Creation de vk (parallelisable)
        for(j=1; j<=n; j++)
        {
            vk[j]=0;
            //(parallelisable)
            for(k=1; k<=n; k++)
            {
                //Reduction
                vk[j] = vk[j] + A.tabMatrice[(j-1) * n + k]*v[k];
            }
        }

        if (i == 0)
        {
            ak=vk[1];
            for(j=2; j<=n; j++)
            {
                if(vk[j]>ak)
                {
                    ak=vk[j];
                }      
            }
        }

        //(parallelisable)
        for(j=1; j<=n; j++)
        {
            vk[j]=vk[j]/ak;
        }
        //(parallelisable)
        for(j=1; j<=n; j++)
        {
            v[j]=vk[j];
        }

        //ARGMAX (parallelisable)
        ak=fabs(vk[1]);
        for(j=2; j<=n; j++)
        {
            if((fabs(vk[j]))>ak)
                ak=fabs(vk[j]);
        }
    }

    printf("\nValeur propre max : %f",ak);
    printf("\n");
    printf("\nVecteur propre max :\n");
    for(i=1; i<=A.n; i++)
    {
        printf("%f\t",vk[i]);
    }
    printf("\n");

    return ak;
}

void calcul_valeurPropre(Matrice A, int m){
    float v[A.n+1],vprope;
    v[1] = 1;
    v[2] = 0;
    v[3] = 0;

    double start,end;
    start = omp_get_wtime();
    vprope = algo_puissanceItere(A,v,A.n,m);
    end = omp_get_wtime();
    printf("Algo seq %f seconds\n", end - start);
}

float algo_puissanceIterePara(Matrice A, float *v, int n, int m){
    
    int i,j,k;
    float vk[n+1],ak;

    for (i = 0; i < m; i++) { // JUSQU'A CONVERGENCE

        //Creation de vk (parallelisable)
        for(j=1; j<=n; j++)
        {
            vk[j]=0;
            //(parallelisable)
            for(k=1; k<=n; k++)
            {
                //Reduction
                vk[j] = vk[j] + A.tabMatrice[(j-1) * n + k]*v[k];
            }
        }

        if (i == 0)
        {
            ak=vk[1];
            for(j=2; j<=n; j++)
            {
                if(vk[j]>ak)
                {
                    ak=vk[j];
                }      
            }
        }

        //(parallelisable)
        for(j=1; j<=n; j++)
        {
            vk[j]=vk[j]/ak;
        }
        //(parallelisable)
        for(j=1; j<=n; j++)
        {
            v[j]=vk[j];
        }

        //ARGMAX (parallelisable)
        ak=fabs(vk[1]);
        for(j=2; j<=n; j++)
        {
            if((fabs(vk[j]))>ak)
                ak=fabs(vk[j]);
        }
    }

    printf("\nValeur propre max : %f",ak);
    printf("\n");
    printf("\nVecteur propre max :\n");
    for(i=1; i<=A.n; i++)
    {
        printf("%f\t",vk[i]);
    }
    printf("\n");

    return ak;
}

void calcul_valeurProprePara(Matrice A, int m){
    float v[A.n+1],vprope;
    v[1] = 1;
    v[2] = 0;
    v[3] = 0;

    double start,end;
    start = omp_get_wtime();
    vprope = algo_puissanceIterePara(A,v,A.n,m);
    end = omp_get_wtime();
    printf("Algo para %f seconds\n", end - start);
}