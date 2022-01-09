#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


/**
 * Définition du type Matrice
 * Une Matrice a deux données
 * n : qui représente la taille de la Matrice
 * tabMatrice : qui représente un tableau de double de double dimension
 */
typedef struct Matrice Matrice;

struct Matrice
{
    int n;
    double **tabMatrice;
};

/** Prototypes de fonctions **/

void init_matrice(Matrice *matrice, int parN);

void suppr_matrice(Matrice *matrice);

void init_val(Matrice *matrice, int rand);

void print_matrice(Matrice matrice);

double algo_puissanceItere(Matrice A, double *v, int n, float conv);

double calcul_valeurPropre(Matrice A, float conv);

double algo_puissanceIterePara(Matrice A, double *v, int n, int num_th, float conv);

double calcul_valeurProprePara(Matrice A, int num_th, float conv);

/**
 * fonction main du programme
 */
int main()
{   
    int n;
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
       
        suppr_matrice(&A);
        printf("Tapez la taille de la matrice carré souhaitez (-1 si vous voulez arreter)\n");
        scanf("%d",&n);
        init_matrice(&A, n);
    }
    while (n != -1);

    return 0;
}



/**
 * La fonction init_matrice permet d'initialiser une matrice carre de taille n donnee en parametre
 * La fonction alloue la memoire dynamiquement en fonction de la taille souhaiter
 * 
 * @param matrice matrice que l'on souhaite initialiser
 * @param n taille de la matrice que l'on souhaite initialiser
 */
void init_matrice(Matrice *matrice, int n)
{
    int i;

    matrice->n = n;
    matrice->tabMatrice = (double**)malloc(n*sizeof(double *));;

    for (i = 0; i < n; i++)
    {   
        matrice->tabMatrice[i] = (double *)calloc(n,sizeof(double));
    }
}

/**
 * La fonction init_val permet d'initialiser une matrice carre de taille n donnee en parametre
 * La fonction affecte des valeurs double dans la matrice
 * 
 * @param matrice matrice que l'on souhaite initialiser
 * @param rand parametre afin de choisir ou non les valeurs, 
 * si égal à 1 la matrice aura i+j dans chaque case
 * sinon demande a l'utilisateur d'entré les valeurs
 */
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
 * La fonction suppr_matrice permet de liberer l'espace memoire allouer pour la matrice
 * 
 * @param matrice matrice que l'on souhaite liberer
 */
void suppr_matrice(Matrice *matrice){

    int i;

    for (i = 0; i < matrice->n; i++)
    {   
        free(matrice->tabMatrice[i]);
    }
    free(matrice->tabMatrice);
    matrice->n = 0;
}

/**
 * La fonction print_matrice permet d'afficher la matrice si la taille de la matrice est inferieur a 10
 *  Affiche de la maniere suivante :
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

/**
 * Algorithme de puissance itérée fait en sequentielle pour calculer la valeur propre d'un matrice et rretourne la valeur propre
 * @param A Matrice dont l'on souhaite calculer la valeur propre
 * @param v Vecteur initialiser (1 a l'indice 0,puis que des 0) afin de le faire converger vers le vecteurs propre associé a la matrice
 * @param n Taille de la matrice
 * @param conv Convergence donnée en parametre par l'utilisateur ex: si taux voulu est de 0.1% alors donnée en parametre la valeur 0.01
 */
double algo_puissanceItere(Matrice A, double *v, int n, float conv){
    
    int i,j,c = 0;
    double vk[n],ak,e[n],emax;

    do { 

        // Creation de Avk-1
        for(i=0; i< n; i++)
        {
            vk[i]=0;
            for (j = 0; j < n; j++)
            {
                vk[i] = vk[i] + A.tabMatrice[i][j]*v[j];
            }   
        }

        // Initialisation de ak pour la premiere itération du programme
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
        
        // Calcul de vk le vecteur propre, e qui represente la convergence entre le ve  v
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

    emax=vk[0];
    for (i = 0; i < n; i++)
    {
        if (fabs(emax)<fabs(vk[i]))
        {
            emax = vk[i];
        }
    }
    for (i = 0; i < n; i++)
    {
        vk[i]=vk[i]/emax;
    }
    
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

/**
 * Fonction auxilaire pour lancer l'Algorithme de puissance itérée fait en sequentielle
 * Cette fonction initialise toutes les variables et chronometre le temps d'execution
 * @param A Matrice dont l'on souhaite calculer la valeur propre
 * @param conv Convergence donnée en parametre par l'utilisateur ex: si taux voulu est de 0.1% alors donnée en parametre la valeur 0.01
 */
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

/**
 * Algorithme de puissance itérée fait en parallele pour calculer la valeur propre d'un matrice et rretourne la valeur propre
 * @param A Matrice dont l'on souhaite calculer la valeur propre
 * @param v Vecteur initialiser (1 a l'indice 0,puis que des 0) afin de le faire converger vers le vecteurs propre associé a la matrice
 * @param n Taille de la matrice
 * @param num_th Nombre de thread utiliser dans l'algorithme
 * @param conv Convergence donnée en parametre par l'utilisateur ex: si taux voulu est de 0.1% alors donnée en parametre la valeur 0.01
 */
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

/**
 * Fonction auxilaire pour lancer l'Algorithme de puissance itérée fait en parallele
 * Cette fonction initialise toutes les variables et chronometre le temps d'execution
 * @param A Matrice dont l'on souhaite calculer la valeur propre
 * @param num_th Nombre de thread utiliser dans l'algorithme
 * @param conv Convergence donnée en parametre par l'utilisateur ex: si taux voulu est de 0.1% alors donnée en parametre la valeur 0.01
 */
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