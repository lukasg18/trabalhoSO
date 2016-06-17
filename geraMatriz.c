#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* Tamanho da matriz (ordem) */
#define ORDEM 1000

/**
*	Retorna um número randomico entre o mínimo
*	e o máximo informados
*	@param int min
*	@param int max
*	@return int random
**/
int randomInt(int min, int max){
	srand(time(NULL)*rand());
	return ((rand()%(int)(((max) + 1)-(min)))+ (min));
}

/**
*	Dado a ordem retorna uma matriz alocada na heap
*	@param int ordem
*	@return int** matrix
*/
int** cria_matriz(int ordem){
	int **matrix;
	int j;
	matrix = (int**)malloc( ordem * sizeof(int*) );
	for(j=0;j<ordem;j++)
		matrix[j] = (int*)malloc( ordem * sizeof(int) );
	return matrix;
}

/**
*	Dado a referência de uma matriz e sua ordem ela será
*	preenchida com números aleatórios de RANDOM_MIN até RANDOM_MAX
*	@param int** matrix
*	@param int ordem
*/
void preenche_matriz(int** matrix, int ordem){
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
void printMatrix(int **matrix, int ordem){
	int i,j;
	for(i=0;i<ordem;i++){
		for(j=0;j<ordem;j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

/**
*	Dado a referência de uma matriz alocada na heap, libera.
*	@param int** matrix
*	@param int ordem
*/
void freeMatrix(int** matrix, int ordem){
	int i;
	for(i=0;i<ordem;i++)
		free(matrix[i]);
	free(matrix);
}