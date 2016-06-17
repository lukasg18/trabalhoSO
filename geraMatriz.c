#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* Tamanho da matriz (ordem) */
#define ORDEM 10
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
*	Dado a ordem retorna uma matriz alocada na heap
*	@param int ordem
*	@return int** matrix
*/
KIND** createMatrix(int ordem){
	KIND **matrix;
	int j;
	matrix = (KIND**)malloc( ordem * sizeof(KIND*) );
	for(j=0;j<ordem;j++)
		matrix[j] = (KIND*)malloc( ordem * sizeof(KIND) );
	return matrix;
}

/**
*	Dado a referência de uma matriz e sua ordem ela será
*	preenchida com números aleatórios de RANDOM_MIN até RANDOM_MAX
*	@param int** matrix
*	@param int ordem
*/
void fillMatrix(KIND** matrix, int ordem){
	int i,j;
	for(i=0;i<ordem;i++)
		for(j=0;j<ordem;j++){
			matrix[i][j] = randomInt(RANDOM_MIN,RANDOM_MAX);
		}
}

/**
*	Imprime uma matriz (apenas para testes)
*	@param int** matrix
*	@param int ordem
*/
void printMatrix(KIND **matrix, int ordem){
	int i,j;
	for(i=0;i<ordem;i++){
		for(j=0;j<ordem;j++){
			printf("%d   ", matrix[i][j]);
		}
		printf("\n");
	}
}

/**
*	Dado a referência de uma matriz alocada na heap, libera.
*	@param int** matrix
*	@param int ordem
*/
void freeMatrix(KIND** matrix, int ordem){
	int i;
	for(i=0;i<ordem;i++)
		free(matrix[i]);
	free(matrix);
}


int main(){
    //aloca matriz
    KIND** matriz = createMatrix(ORDEM);
    //preenche com números randômicos
    fillMatrix(matriz, ORDEM);
    //imprime
    printMatrix(matriz, ORDEM);
    //libera
    freeMatrix(matriz, ORDEM);
    return 0;
}
