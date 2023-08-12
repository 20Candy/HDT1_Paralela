#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

void birthday_greetings(int thread_id, int total_threads, int age);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <age>\n", argv[0]);
        return 1;
    }

    int age = strtol(argv[1], NULL, 10);

    #pragma omp parallel
    birthday_greetings(omp_get_thread_num(), omp_get_num_threads(), age);

    return 0;
}

void birthday_greetings(int thread_id, int total_threads, int age) {
    if (thread_id % 2 == 0) {
        printf("Saludos del hilo %d\n", thread_id);
    } else {
        printf("Feliz cumpleaños número %d!\n", age);
    }
}