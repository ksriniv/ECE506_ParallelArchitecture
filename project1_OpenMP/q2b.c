#include <stdio.h>   // printf()
#include <omp.h>     // OpenMP
#include <stdlib.h>  // rand()

#define SIZE 100

int main(int argc, char** argv) {
   int A[SIZE][SIZE];
   int B[SIZE][SIZE];
   int S[SIZE][SIZE];
   int P[SIZE][SIZE];
   int i, j, k, sum=0;

   if (argc > 1) {
        omp_set_num_threads( atoi(argv[1]) );
   }

   // Initialize
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         A[i][j] = rand() % 100;
         B[i][j] = rand() % 100;
      }
   }

   // Serial
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         for (k = 0; k < SIZE; k++) {
		sum = sum + A[i][k]*B[k][j];
         }
         S[i][j] = sum;
	 //printf("Sequential Sum :%d \n",sum);
         sum = 0;
      }
   }
   double start = omp_get_wtime();
   // Parallel
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
       #pragma omp parallel for private(k)
	  for (k = 0; k < SIZE; k++) {
 		#pragma omp atomic
		sum = sum + A[i][k]*B[k][j];
	}
	
         P[i][j] = sum;
	 sum = 0;
      }
   }
   double end = omp_get_wtime() - start;
   // Check
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         if(S[i][j] != P[i][j]) {
            printf("Mismatch!\n");
            return 1;
	    }
	/*  else
	    printf("Code Working properly \n");   
	*/
         }
      }

   printf("\nExecution time was: %lf\n",end);
  return 0;
}
