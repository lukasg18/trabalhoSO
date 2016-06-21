#include <stdio.h>
#include <stdlib.h>

/* Tamanho da matriz (ordem) */
#define LI 50
#define COL 50
#define RANDOM_MIN 0
#define RANDOM_MAX 29999
typedef int KIND;


/* CABEÇALHOS */
KIND randomInt(KIND min, KIND max);
KIND** createMatrix(int l, int c);
void fillMatrix(KIND** matrix, int l, int c);
void printMatrix(KIND **matrix, int l, int c);
void freeMatrix(KIND** matrix, int l, int c);
int isPrime(long n);
/* FIM CABEÇALHOS */

/* Região crítica */
int primeNumber = 0;

/**
*	Retorna um número randomico entre o mínimo
*	e o máximo informados
*	@param int min
*	@param int max
*	@return int random
**/
KIND randomInt(KIND min, KIND max){
	return ((rand()%(int)(((max) + 1)-(min)))+ (min));
}

/**
*	Dado o tamanho das linhas e colunas retorna uma matriz alocada na heap
*	@param int l
*	@param int c
*	@return int** matrix
*/
KIND** createMatrix(int l, int c){
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
void fillMatrix(KIND** matrix, int l, int c){
	int i,j;
	for(i=0;i<l;i++)
		for(j=0;j<c;j++){
			matrix[i][j] = randomInt(RANDOM_MIN,RANDOM_MAX);
		}
}

/**
*	Imprime uma matriz (apenas para testes)
*	@param int** matrix
*	@param int l
*	@param int c
*/
void printMatrix(KIND **matrix, int l, int c){
	int i,j;
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			printf("%d   ", matrix[i][j]);
		}
		printf("\n");
	}
}

/**
*	Dado a referência de uma matriz alocada na heap, libera.
*	@param int** matrix
*	@param int l
*	@param int c
*/
void freeMatrix(KIND** matrix, int l, int c){
	int i;
	for(i=0;i<l;i++)
		free(matrix[i]);
	free(matrix);
}

int isPrime(long n){
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

void countPrimesSerial(KIND** mat, int li, int col){
	int i, j;
	for(i=0;i<li;i++)
		for(j=0; j < col; j++){
			if(isPrime(mat[i][j])){
				primeNumber++;
			}
		}
}


int main(){
	srand(10);
	KIND** matriz = createMatrix(LI, COL);
	fillMatrix(matriz, LI, COL);
	countPrimesSerial(matriz, LI, COL);
	printMatrix(matriz,LI,COL);//remove
	printf("\n\nNumeros primos: %d\n", primeNumber);
	freeMatrix(matriz, LI, COL);
}