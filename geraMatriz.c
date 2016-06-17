#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* Tamanho da matriz (ordem) */
#define LI 5
#define COL 3
#define RANDOM_MIN 0
#define RANDOM_MAX 29999
typedef int KIND;

/**
*	Retorna um número randomico entre o mínimo
*	e o máximo informados
*	@param int min
*	@param int max
*	@return int random
**/
KIND randomInt(KIND min, KIND max){
	srand(time(NULL)*rand());
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


int main(){
    //aloca matriz
    KIND** matriz = createMatrix(LI, COL);
    //preenche com números randômicos
    fillMatrix(matriz, LI, COL);
    //imprime
    printMatrix(matriz, LI, COL);
    //libera
    freeMatrix(matriz, LI, COL);
    return 0;
}
