#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {

    omp_set_num_threads(4);

    #pragma omp parallel
    for (i = 0; i < 3; i++){
        printf ("Thread ID: %d\n", omp_get_thread_num());
    }
    #pragma omp barrier

    return 0;
}
