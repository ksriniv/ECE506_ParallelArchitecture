#include <stdio.h>
#include <omp.h>
int main(int argc, char*argv[]) {

  int numPartitions = 1200;
  int circleCount = 0;
  int i, j = 0;
  double a = 0;
  double interval = 1.0/(double)numPartitions;

  double start =  omp_get_wtime();

  #pragma omp parallel for private(a) private(i) private(j)
  for (i = 0; i < numPartitions; i++) {
      a = (i + .5)*interval;

     for ( j = 0; j < numPartitions; j++) {
        double b = (j + .5)*interval;
	
	if ((a*a + b*b) <= 1)
        #pragma omp atomic
	 circleCount =   circleCount+1;

     }
  }
  double end =  omp_get_wtime()-start;
  double pi = (double)(4*circleCount)/(numPartitions * numPartitions);
  printf("Estimate of pi is : %10.8lf\n", pi);
  printf("Execution time was: %lf",end);
  return 0;
}
