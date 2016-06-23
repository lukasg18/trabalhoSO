#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[]) {
   time_t start, stop;
   clock_t ticks; long count;
   // Do stuff
   int i=0,j=0;

   for(j=0;j<2;j++){
   	time(&start);
   	while(i<20000000)
   {
	
        i++;
        ticks = clock();

   }

   time(&stop);
   
   printf("Used %0.2f seconds of CPU time. \n", (double)ticks/CLOCKS_PER_SEC);
   printf("Finished in about %.0f seconds. \n", difftime(stop, start));
   }
   return 0;
}