#include "matrice.h"

/**
 * La fonction init_matrice permet d'initialiser une matrice carre de taille n donnee en parametre
 * La fonction alloue la memoire dynamiquement en fonction de la taille souhaiter
 * 
 * @param matrice matrice que l'on souhaite initialiser
 * @param n taille de la matrice que l'on souhaite initialiser
 */

void init_matrice(Matrice *matrice, int n)
{
    int i,j;

    matrice->n = n;
    matrice->tabMatrice = (double**)malloc(n*sizeof(double *));;

    for (i = 0; i < n; i++)
    {   
        matrice->tabMatrice[i] = (double *)calloc(n,sizeof(double));
        for (j = 0; j < n; j++)
        {
            //matrice->tabMatrice[i][j] = i+j;
            /*printf("A[%d][%d]=", i,j);
            scanf("%lf",&matrice->tabMatrice[i][j]);*/
        }
    }
    
    /*matrice->tabMatrice[0][0] = -6;
    matrice->tabMatrice[0][1] = 4;
    matrice->tabMatrice[0][2] = 45;
    matrice->tabMatrice[0][3] = -14;
    matrice->tabMatrice[1][0] = -14;
    matrice->tabMatrice[1][1] = 51;
    matrice->tabMatrice[1][2] = -25;
    matrice->tabMatrice[1][3] = 524;
    matrice->tabMatrice[2][0] = 144;
    matrice->tabMatrice[2][1] = -24;
    matrice->tabMatrice[2][2] = 24;
    matrice->tabMatrice[2][3] = 142;
    matrice->tabMatrice[3][0] = -214;
    matrice->tabMatrice[3][1] = 452;
    matrice->tabMatrice[3][2] = 1421;
    matrice->tabMatrice[3][3] = -45;*/
}

void init_val(Matrice *matrice, int rand){
    
    int i,j;

    for (i = 0; i < matrice->n; i++)
    {   
        for (j = 0; j < matrice->n; j++)
        {
            if (rand == 1){
                matrice->tabMatrice[i][j] = i+j;
            }
            else
            {
                printf("A[%d][%d]=", i,j);
                scanf("%lf",&matrice->tabMatrice[i][j]);
            }
            
        }
    }
}

/**
 * La fonction print_matrice permet d'afficher la matrice de la maniere suivante :
 *  [ 1 2 ]
 *  [ 3 4 ]
 * @param matrice matrice que l'on souhaite afficher
 */
void print_matrice(Matrice matrice)
{
    printf("\nMatrice\n");

    for (int i = 0; i < matrice.n; i++)
    {
        printf("[");
        for (int j = 0; j < matrice.n; j++)
        {
            printf(" %.3lf ", matrice.tabMatrice[i][j]);
        }
        printf("]\n");
    }
}

double algo_puissanceItere(Matrice A, double *v, int n, float conv){
    
    int i,j,c = 0;
    double vk[n],ak,e[n],emax;

    //for (c = 0; c < 50; c++) { // JUSQU'A CONVERGENCE
    do { // Convergence

        // Creation de vk
        for(i=0; i< n; i++)
        {
            vk[i]=0;
            for (j = 0; j < n; j++)
            {
                vk[i] = vk[i] + A.tabMatrice[i][j]*v[j];
            }   
        }

        // Init ak pour la premiere itération
        if (c == 0)
        {
            c++;
            ak=vk[0];
            for(j=1; j<n; j++)
            {
                if(vk[j]>ak)
                {
                    ak=vk[j];
                }      
            }
        }
        
        // Calcul de vk et v
        for(j=0; j<n; j++)
        {
            vk[j]=vk[j]/ak;
            e[j] = fabs(fabs(vk[j])-fabs(v[j])); // Calcul du taux d'erreur
            v[j]=vk[j];
        }

        emax = e[0];
        ak=vk[0];
        for(i=1; i<n; i++)
        {   
            if(e[i]>emax)
            {
                emax=e[i];
            }
            if((fabs(vk[i]))>ak)
            {
                ak=vk[i];
            }
        }     
    }
    while (emax>conv);

    if (n<=10){
        printf("\nVecteur propre max :\n");
        for(i=0; i<A.n; i++)
        {
            printf("%lf\t",vk[i]);
        }
        printf("\n");
    }

    return ak;
}

double calcul_valeurPropre(Matrice A, float conv){

    double v[A.n],vprope;
    int i;
    v[0] = 1;
    for (i = 1; i < A.n; i++)
    {
        v[i]=0;
    }

    double start,end;
    start = omp_get_wtime();
    vprope = algo_puissanceItere(A,v,A.n,conv);
    end = omp_get_wtime();
    printf("\nValeur propre max : %lf\t",vprope);
    printf("\n");
    return end-start;
}

double algo_puissanceIterePara(Matrice A, double *v, int n, int num_th, float conv){

    int i,j,c = 0;
    double vk[n],ak,e[n],emax;

    //for (c = 0; c < 50; c++) { // JUSQU'A CONVERGENCE
    do {
        
        // Creation de vk (1)
        #pragma omp parallel for schedule(static,n/num_th) num_threads(num_th)
        for(i=0; i< n; i++)
        {
            vk[i]=0;
            #pragma omp parallel for schedule(static,n/num_th) num_threads(num_th)
            for (j = 0; j < n; j++)
            {
                vk[i] = vk[i] + A.tabMatrice[i][j]*v[j];
            }
        }

        // si premier tour de boucle , initialisation de la valeur propre
        if (c == 0)
        {      
            c++;
            ak=vk[0];    
            #pragma omp parallel for schedule(static,n/num_th) num_threads(num_th)
            for(j=1; j<n; j++)
            {   
                #pragma omp critical
                {
                    if(vk[j]>ak){
                    ak=vk[j];
                    }
                }
            }   
        }
        
        // (2)
        #pragma omp parallel for schedule(static,n/num_th) num_threads(num_th)
        for(j=0; j<n; j++)
        {
            vk[j] = vk[j]*(1/ak); // Calcul du vecteur vk (vk = vk/ak)
            e[j] = fabs(fabs(vk[j])-fabs(v[j])); // Calcul du taux d'erreur
            v[j] = vk[j];
        }

        //(3)
        emax = e[0];
        ak=vk[0];
        #pragma omp parallel for schedule(static,n/num_th) num_threads(num_th)
        for(i=1; i<n; i++)
        {   
            #pragma omp critical
            {
                if(e[i]>emax)
                {
                    emax=e[i];
                }
                if((fabs(vk[i]))>ak)
                {
                    ak=vk[i];
                } 
            }
        }  
    }
    while (emax>conv);

    if (n<=10){
        printf("\nVecteur propre max :\n");
        for(i=0; i<A.n; i++)
        {
            printf("%lf\t",vk[i]);
        }
        printf("\n");
    }

    return ak;
}

double calcul_valeurProprePara(Matrice A, int num_th, float conv){

    double v[A.n],vprope;
    int i;
    v[0] = 1;
    for (i = 1; i < A.n; i++)
    {
        v[i]=0;
    }

    double start,end;
    start = omp_get_wtime();
    vprope = algo_puissanceIterePara(A,v,A.n,num_th,conv);
    end = omp_get_wtime();
    printf("\nValeur propre max : %lf\t",vprope);
    printf("\n");
    return end-start;
}
