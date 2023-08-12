#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

void hello_world(int thread_num, int total_threads);

int main(int argc, char* argv[]) {
    int thread_count = 10;

    if (argc > 1) {
        thread_count = strtol(argv[1], NULL, 10);
    }

    #pragma omp parallel num_threads(thread_count)
    hello_world(omp_get_thread_num(), omp_get_num_threads());

    return 0;
}

void hello_world(int thread_num, int total_threads) {
    printf("Hello from thread %d of %d !\n", thread_num, total_threads);
}