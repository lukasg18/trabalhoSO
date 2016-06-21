#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* Configurações da matriz */
#define LI 50
#define COL 50
#define RANDOM_MIN 0
#define RANDOM_MAX 29999
typedef int KIND;
/* -- */

/* Configurações do multiThread */
#define NUM_THREADS 2
typedef struct{
	int liStart, liEnd, colStart, colEnd;
} threadParam;
/* -- */

/* CABEÇALHO DE FUNÇÕES */
void countPrimesSerial(KIND** mat, int li, int col);
void *countPrimesThread(void *threadid);
KIND** createMatrix(int l, int c);
void fillMatrix(KIND** matrix, int l, int c);
void freeMatrix(KIND** matrix, int l, int c);
int isPrime(long n);
KIND randomInt(KIND min, KIND max);
/* -- */


/* VARIÁVEIS GLOBAIS */
KIND** matriz;
int primeNumber; //região crítica
pthread_mutex_t mutexPrimeNumber;
/* -- */



int main(int argc, char const *argv[])
{
	srand(10); //Seed fixado para formar sempre a mesma sequência randômica

	matriz = createMatrix(LI, COL);//Alocação da matriz
	fillMatrix(matriz, LI, COL);

	/* IMPLEMENTAÇÃO SERIAL */
	primeNumber = 0;
	countPrimesSerial(matriz, LI, COL);
	printf("Serial: %d\n", primeNumber);
	/* FIM DA IMPLEMENTAÇÃO SERIAL */


	/* IMPLEMENTAÇÃO PARALELA */
	primeNumber = 0;
	pthread_t threads[NUM_THREADS];
	threadParam params[NUM_THREADS];
	int t, rc;
	//Iniciando threads
	for(t=0; t<NUM_THREADS; t++){

		params[t].liStart = t+1;
		params[t].liEnd = 1;
		params[t].colStart = 1;
		params[t].colEnd = 1;

		rc = pthread_create(&threads[t], NULL, countPrimesThread, (void*)&params[t]);
		if (rc){
			printf("ERROR code is %d\n", rc);
			exit(-1);
		}
	}

	//Join threads
	for(t=0; t< NUM_THREADS; t++){
	    pthread_join(threads[t],NULL);
	}
	/* FIM DA IMPLEMENTAÇÃO PARALELA */

	//Free da matriz
	freeMatrix(matriz, LI, COL);
	return 0;
}






/**
*	Dado uma matriz e sua dimensão incrementa a variável global "primeNumber"
*	com a quantidade de números primos dessa matriz de modo serial
*	@param KIND** mat
*	@param int li
*	@param int col
*/
void countPrimesSerial(KIND** mat, int li, int col)
{
	int i, j;
	for(i=0;i<li;i++)
		for(j=0; j < col; j++){
			if(isPrime(mat[i][j])){
				primeNumber++;
			}
		}
}

void *countPrimesThread(void *threadid)
{
	printf("\nThread:%d\n", ((threadParam*)threadid)->liStart);
}

/**
*	Dado o tamanho das linhas e colunas retorna uma matriz alocada na heap
*	@param int l
*	@param int c
*	@return int** matrix
*/
KIND** createMatrix(int l, int c)
{
	KIND **matrix;
	int j;
	matrix = (KIND**)malloc( l * sizeof(KIND*) );
	for(j=0;j<l;j++)
		matrix[j] = (KIND*)malloc( c * sizeof(KIND) );
	return matrix;
}

/**
*	Dado a referência de uma matriz e sua dimensão ela será
*	preenchida com números aleatórios de RANDOM_MIN até RANDOM_MAX
*	@param int** matrix
*	@param int l
*   @param int c
*/
void fillMatrix(KIND** matrix, int l, int c)
{
	int i,j;
	for(i=0;i<l;i++)
		for(j=0;j<c;j++){
			matrix[i][j] = randomInt(RANDOM_MIN,RANDOM_MAX);
		}
}

/**
*	Dado a referência de uma matriz alocada na heap, libera.
*	@param int** matrix
*	@param int l
*	@param int c
*/
void freeMatrix(KIND** matrix, int l, int c)
{
	int i;
	for(i=0;i<l;i++)
		free(matrix[i]);
	free(matrix);
}

/**
*	Dado um número retorna se ele é primo
*	@param long n
*	@return int n is prime
*/
int isPrime(long n)
{
	if(n==2 || n==3)return 1;
	if( (n==1 || n%2==0)|| (n%3)==0 )return 0;
	int i=5;
	int w = 2;
	while( i*i <= n ){
		if( n % i == 0)return 0;
		i+=w;
		w = 6 - w;
	}
	return 1;
}

/**
*	Retorna um número randomico entre o mínimo
*	e o máximo informados utilizando o rand
*	!(É necessário o uso correto do srand antes da chamada)!
*	@param int min
*	@param int max
*	@return int random
**/
KIND randomInt(KIND min, KIND max)
{
	return ((rand()%(int)(((max) + 1)-(min)))+ (min));
}