#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
/* Quantidade de threads */
#define NUM_THREADS 2

/* Região crítica */
int primeNumber = 0;
pthread_mutex_t mutexPrimeNumber;

/* CABEÇALHOS */
int isPrime(long n);
void *countPrimes(void *threadid);


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

/* Procedimento a ser realizado pelas threads */
void *countPrimes(void *threadid){
    //todo
    int i;
    for(i=1;i<11;i++){
    	if( isPrime(i) ){
        	pthread_mutex_lock(&mutexPrimeNumber);
        	primeNumber++;
        	pthread_mutex_unlock(&mutexPrimeNumber);
    	}
    }
    return threadid;
}