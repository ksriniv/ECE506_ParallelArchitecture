#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {

    omp_set_num_threads(4);
    int i = 0;
    #pragma omp parallel for
    for (i = 0; i < 3; i++){

		#pragma omp task
		printf("With Task: %d \t", omp_get_thread_num());

		#pragma omp taskwait
		printf("TaskWait!! \n");
	}

    #pragma omp barrier

    return 0;
}
