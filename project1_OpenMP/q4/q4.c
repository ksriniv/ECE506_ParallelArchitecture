#include <stdio.h>

int main(int argc, char*argv[]) {

  int numPartitions = 1200;
  int circleCount = 0;

  double interval = 1.0/(double)numPartitions;

  for (int i = 0; i < numPartitions; i++) {
     double a = (i + .5)*interval;
     for (int j = 0; j < numPartitions; j++) {
        double b = (j + .5)*interval;
        if ((a*a + b*b) <= 1)
           circleCount++;
     }
  }

  double pi = (double)(4*circleCount)/(numPartitions * numPartitions);
  printf("Estimate of pi is: %10.8lf\n", pi);

  return 0;
}
