/**
*	Dado um número retorna se ele é primo
*	@param long n
*	@return int n is prime
*/
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