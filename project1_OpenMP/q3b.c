#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {

    omp_set_num_threads(4);
	int x=1;
	int i = 0;
    #pragma omp parallel private(x)
    for (i = 0; i < 3; i++){
		x = x + i;
        printf ("Thread ID: %d\n", omp_get_thread_num());
    }
    #pragma omp barrier

	printf ("Value of x after private: %i\n", x);
	x = 11;
	#pragma omp parallel firstprivate(x)
    for (i = 0; i < 3; i++){
		x = x + i;
        printf ("Thread ID: %d\n", omp_get_thread_num());
    }
    #pragma omp barrier
	printf ("Value of x after firstprivate: %i\n", x);
	x = 1;
	#pragma omp parallel for lastprivate(x)
    for (i = 0; i < 3; i++){
		x = x + i;
        printf ("Thread ID: %d\n", omp_get_thread_num());
    }
    #pragma omp barrier
	printf ("Value of x after lastprivate: %i\n", x);
    return 0;
}
