#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

/* Configurações da matriz */
#define LI 10000
#define COL 10000
#define RANDOM_MIN 0
#define RANDOM_MAX 29999
typedef int KIND;
/* -- */

/* Configurações do multiThread */
#define NUM_THREADS 2
#define MACROB_LI 2000
#define MACROB_COL 2000
typedef struct{
	int liStart, liEnd, colStart, colEnd;
} macroBloco;
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
KIND** matrix;
int primeNumber; //região crítica
pthread_mutex_t mutexPrimeNumber;
int subAvailable; //região crítica
pthread_mutex_t mutexSubAval;
/* -- */



int main(int argc, char const *argv[])
{
	srand(10); //Seed fixado para formar sempre a mesma sequência randômica

	matrix = createMatrix(LI, COL);//Alocação da matriz
	fillMatrix(matrix, LI, COL);
	time_t beginSerial, endSerial, beginParalelo, endParalelo;

	/* IMPLEMENTAÇÃO SERIAL */
	time(&beginSerial);
	primeNumber = 0;
	countPrimesSerial(matrix, LI, COL);
	time(&endSerial);
	printf("--------Serial--------\nNúmeros primos contados:%d\nTempo: %.1fs\n", primeNumber, difftime(endSerial,beginSerial));
	/* FIM DA IMPLEMENTAÇÃO SERIAL */


	/* IMPLEMENTAÇÃO PARALELA */
	time(&beginParalelo);
	// Divisão das submatrizes
	subAvailable = (LI*COL)/(MACROB_LI*MACROB_COL);
	macroBloco subMatrices[subAvailable];
	int ml=0, mc=0, i=0;
	for(ml=0;ml<LI;ml+=MACROB_LI)
		for(mc=0;mc<COL;mc+=MACROB_COL){
			subMatrices[i].liStart = ml;
			subMatrices[i].liEnd = ml+MACROB_LI;
			subMatrices[i].colStart = mc;
			subMatrices[i].colEnd = mc+MACROB_COL;
			i++;
		}

	primeNumber = 0;
	pthread_t threads[NUM_THREADS];
	int t, rc;
	//Iniciando threads
	for(t=0; t<NUM_THREADS; t++){

		rc = pthread_create(&threads[t], NULL, countPrimesThread, (void*)&subMatrices); //INICIA A THREAD PASSANDO PARÂMETRO "subMatrices" (referência)
		if (rc){
			printf("ERROR code is %d\n", rc);
			exit(-1);
		}
	}

	//Join threads
	for(t=0; t< NUM_THREADS; t++){
	    pthread_join(threads[t],NULL);
	}
	time(&endParalelo);
	printf("--------Paralelo--------\nNúmeros primos contados:%d\nTempo: %.1fs\n", primeNumber, difftime(endParalelo,beginParalelo));
	/* FIM DA IMPLEMENTAÇÃO PARALELA */

	//Free da matriz
	freeMatrix(matrix, LI, COL);
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

/**
*	Função a ser executada em cada thread.
*	Analisa a variável global "subAvailable" para saber se há macrobloco disponível
*	caso haja essa mesma variável será decrementada sinalizando que a thread atual
*	está analisando o macrobloco na posição que subAvailable havia anteriormente.
*	O vetor de macroblocos a qual essa variável global sinaliza deve ser passado
*	como parâmetro.
*	@param void* threadid (cast of macroBloco*)
*/
void *countPrimesThread(void *threadid)
{
	macroBloco m;
	int i, j, endThread=0;
	while(1)
	{
		//Entrando na região crítica
		pthread_mutex_lock(&mutexSubAval);
		//Caso haja macrobloco disponível ele irá para variável "m"
		if(subAvailable>-1){
			m = ((macroBloco*)threadid)[subAvailable--];
		}else{
			endThread=1;
		}
		pthread_mutex_unlock(&mutexSubAval);
		//Saindo da região crítica

		if(endThread)break; //Se não houver macrobloco disponível encerra o while e finaliza a thread
		
		//Verificando o macrobloco disponível
		for(i=m.liStart;i<m.liEnd;i++)
			for(j=m.colStart;j<m.colEnd;j++){

				//Se o elemento atual for primo incrementa a variável global "primeNumber"
				if( isPrime(matrix[i][j]) ){
					//Entrando na região crítica
					pthread_mutex_lock(&mutexPrimeNumber);
					primeNumber++;
					pthread_mutex_unlock(&mutexPrimeNumber);
					//Saindo da região crítica
				}

			}

	}
	pthread_exit(NULL);
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