#include <stdio.h>
#include <omp.h>
int main(int argc, char*argv[]) {

  int numPartitions = 1200;
  int circleCount = 0;
  int i, j = 0;	
  double interval = 1.0/(double)numPartitions;
  double start = omp_get_wtime(); 
 #pragma omp parallel for default(shared)
    for (i = 0; i < numPartitions; i++) {
     double a = (i + .5)*interval;
	#pragma omp parallel for private(j)
     for ( j = 0; j < numPartitions; j++) {
        double b = (j + .5)*interval;
        
	if ((a*a + b*b) <= 1)
        #pragma omp atomic
	   circleCount++;
     }
  }
  double end = omp_get_wtime()-start;

  double pi = (double)(4*circleCount)/(numPartitions * numPartitions);
  printf("Estimate of pi is: %10.8lf\n", pi);
  printf("Time of execution in seconds:%lf",end);
  return 0;
}
