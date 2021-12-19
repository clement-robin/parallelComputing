#include "matrice.h"

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
            matrice->tabMatrice[i][j] = i+j;
        }
    }
}

void print_matrice(Matrice matrice)
{
    printf("\nMatrice\n");

    for (int i = 0; i < matrice.n; i++)
    {
        printf("[");
        for (int j = 0; j < matrice.n; j++)
        {
            printf(" %.3f ", matrice.tabMatrice[i][j]);
        }
        printf("]\n");
    }
}

double algo_puissanceItere(Matrice A, double *v, int n){
    
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
        for(i=1; i<n; i++)
        {   
            if(e[i]>emax)
            {
                emax=e[i];
            }  
        }

        // Calcul de ak
        ak=fabs(vk[0]);
        for(j=1; j<n; j++)
        {
            if((fabs(vk[j]))>ak)
            {
                ak=fabs(vk[j]);
            } 
        }
    }
    while (emax>0.001);
    /*printf("\n Emax : %f\t\n",emax);
    printf("\nValeur propre max : %f\t",ak);
    printf("\n");*/
    /*printf("\nVecteur propre max :\n");
    for(i=0; i<A.n; i++)
    {
        printf("%f\t",vk[i]);
    }
    printf("\n");*/

    return ak;
}

double calcul_valeurPropre(Matrice A){

    double v[A.n],vprope;
    int i;
    v[0] = 1;
    for (i = 1; i < A.n; i++)
    {
        v[i]=0;
    }

    double start,end;
    start = omp_get_wtime();
    vprope = algo_puissanceItere(A,v,A.n);
    end = omp_get_wtime();
    return end-start;
}

double algo_puissanceIterePara(Matrice A, double *v, int n, int num_th){

    int i,j,c = 0;
    double vk[n],ak,e[n],emax;

    //for (c = 0; c < 50; c++) { // JUSQU'A CONVERGENCE
    do {
        // Creation de vk
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
            
        #pragma omp parallel for schedule(static,n/num_th) num_threads(num_th)
        for(j=0; j<n; j++)
        {
            vk[j]=vk[j]*(1/ak); // Calcul du vecteur vk (vk = vk/ak)
            e[j] = fabs(fabs(vk[j])-fabs(v[j])); // Calcul du taux d'erreur
            v[j]=vk[j];
        }

        emax = e[0];
        #pragma omp parallel for schedule(static,n/num_th) num_threads(num_th)
        for(i=1; i<n; i++)
        {   
            #pragma omp critical
            {
                if(e[i]>emax)
                {
                    emax=e[i];
                }  
            }
        }

        ak=fabs(vk[0]);
        #pragma omp parallel for schedule(static,n/num_th) num_threads(num_th)
        for(j=1; j<n; j++)
        {
            #pragma omp critical
            {
                if((fabs(vk[j]))>ak)
                {
                    ak=fabs(vk[j]);
                }
           }
        }   
    }
    while (emax>0.001);
    /*printf("\n Emax : %f\t\n",emax);
    printf("\nValeur propre max : %f\t",ak);
    printf("\n");*/
    /*printf("\nVecteur propre max :\n");
    for(i=0; i<A.n; i++)
    {
        printf("%f\t",vk[i]);
    }
    printf("\n");*/

    return ak;
}

double calcul_valeurProprePara(Matrice A, int num_th){

    double v[A.n],vprope;
    int i;
    v[0] = 1;
    for (i = 1; i < A.n; i++)
    {
        v[i]=0;
    }

    double start,end;
    start = omp_get_wtime();
    vprope = algo_puissanceIterePara(A,v,A.n,num_th);
    end = omp_get_wtime();
    return end-start;
}
