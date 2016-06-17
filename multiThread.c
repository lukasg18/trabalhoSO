#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
/* Quantidade de threads */
#define NUM_THREADS 4

/* Região crítica */
int primeNumber = 0;
pthread_mutex_t mutexPrimeNumber;


/* Procedimento a ser realizado pelas threads */
void *countPrimes(void *threadid){
    //todo
    int i;
    for(i=0;i<10000000;i++){
        pthread_mutex_lock(&mutexPrimeNumber);
        primeNumber++;
        pthread_mutex_unlock(&mutexPrimeNumber);
    }
    return threadid;
}


int main (int argc, char *argv[]){

    //todo struct with matrix for primes count

	pthread_t threads[NUM_THREADS];
	int t, rc;
	/* Start threads */
	for(t=0; t<NUM_THREADS; t++){
		rc = pthread_create(&threads[t], NULL, countPrimes, NULL);
		if (rc){
			printf("ERROR code is %d\n", rc);
			exit(-1);
		}
	}
	/* Join threads */
	for(t=0; t< NUM_THREADS; t++){
	    pthread_join(threads[t],NULL);
	}
	printf("%d\n", primeNumber);
	pthread_exit(NULL);
}