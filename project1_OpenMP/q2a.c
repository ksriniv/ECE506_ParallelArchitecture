#include <stdio.h>   
#include <omp.h>     
#include <stdlib.h> 

#define SIZE 100

int main(int argc, char** argv) {
   int A[SIZE][SIZE];
   int B[SIZE][SIZE];
   int S[SIZE][SIZE];
   int P[SIZE][SIZE];
   int i, j, k, sum=0;
   omp_lock_t writelock;
//   omp_lock_t writelock1;
   omp_init_lock(&writelock);
//   omp_init_lock(&writelock1);
   if (argc > 1) {
        omp_set_num_threads( atoi(argv[1]) );
   }

   
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         A[i][j] = rand() % 100;
         B[i][j] = rand() % 100;
      }
   }

   /* Serial*/
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         for (k = 0; k < SIZE; k++) {
		sum = sum + A[i][k]*B[k][j];
         }
         S[i][j] = sum;
         sum = 0;
      }
   }
  double start = omp_get_wtime();
   /* Parallel */
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
       #pragma omp parallel for default(shared)
	  for (k = 0; k < SIZE; k++) {
	       	omp_set_lock(&writelock);
 		sum = sum + A[i][k]*B[k][j];
		omp_unset_lock(&writelock);
	}

//	omp_set_lock(&writelock1);
         P[i][j] = sum;
//	omp_unset_lock(&writelock1);
         sum = 0;
      }
   }
  double end = omp_get_wtime()-start;

   /* Check */
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

  omp_destroy_lock(&writelock);
 // omp_destroy_lock(&writelock1);
 printf("\nExecution time was: %lf\n",end);
  return 0;
}
