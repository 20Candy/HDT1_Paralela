/*
Autor: Carol Arevalo
Para compilar: gcc -o riemann riemann.c -lm -fopenmp
Fecha: viernes 11 de agosto de 2022
Version: 1.1
*/

// librerias
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h> // Agregamos la librería para OpenMP

// Variable global para almacenar el resultado de la integral
double global_result = 0.0;

// Funciones
double f1(double x) {
    return x * x; // Se define la funcion x^2
}

double f2(double x) {
    return 2 * x * x * x; // Se define la funcion 2x^3
}

double f3(double x) {
    return sin(x); // Se define la funcion sin(x)
}

// Funcion trapecios
double trapezoides(double a, double b, int n, double (*func)(double)) {
    double h = (b - a) / n;
    double sum = 0.5 * (func(a) + func(b));

    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += func(x);
    }

    return h * sum;
}

// Funcion principal
int main(int argc, char* argv[]) {

    // Parametros por defecto
    double a = 2.0; 
    double b = 10.0; 
    int threads = 4;
    int n = 10000000; // Valor por defecto para n 

    // Si se ingresan parametros, se toman esos valores
    if (argc > 3) {
        a = atof(argv[1]);
        b = atof(argv[2]);
        threads = atoi(argv[3]); 
    }

    // Realizar los cálculos necesarios para distribuir el trabajo entre los threads
    double h = (b - a) / n;
    int n_local = n / threads;

    #pragma omp parallel num_threads(threads)
    {
        int thread_id = omp_get_thread_num();
        double a_local = a + (thread_id * n_local * h);
        double b_local = a_local + (n_local * h);

        // Cálculo local de la integral usando la función trapezoides
        double local_result = trapezoides(a_local, b_local, n_local, f1);

        // Agregar el resultado local a la variable global de manera segura
        #pragma omp critical
        global_result += local_result;
    }

    printf("Con n = %d trapezoides, utilizando %d threads, nuestra aproximacion de la integral de %.6lf a %.6lf:\n", n, threads, a, b);
    printf("Resultado total: %.10lf\n", global_result);

    return 0;
}
