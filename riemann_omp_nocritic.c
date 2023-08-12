#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"

double f1(double x) {
    return x * x;
}

double f2(double x) {
    return 2 * x * x * x;
}

double f3(double x) {
    return sin(x);
}

double trapezoides(double a, double b, int n, double (*func)(double)) {
    double h = (b - a) / n;
    double sum = 0.5 * (func(a) + func(b));
    
    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += func(x);
    }

    return h * sum;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s a b num_threads\n", argv[0]);
        return 1;
    }

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int num_threads = atoi(argv[3]);

    int n = 10000000; // Asumimos un valor fijo para n
    double h = (b - a) / n;

    double* local_sums = (double*)malloc(num_threads * sizeof(double));
    if (local_sums == NULL) {
        printf("Error allocating memory for local_sums.\n");
        return 1;
    }

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        int n_local = n / num_threads;
        double a_local = a + thread_id * n_local * h;
        double b_local = a_local + n_local * h;

        double local_sum = trapezoides(a_local, b_local, n_local, f1); // Puedes cambiar la función aquí

        local_sums[thread_id] = local_sum;
    }

    double total_sum = 0.0;
    for (int i = 0; i < num_threads; ++i) {
        total_sum += local_sums[i];
    }

    printf("Con n = %d trapezoides, nuestra aproximacion de la integral de %.6lf a %.6lf es %.10lf\n", n, a, b, total_sum);

    free(local_sums);

    return 0;
}