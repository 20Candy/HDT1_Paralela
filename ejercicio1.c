/*
Autor: Carol Arevalo
Para compilar: gcc -o ejercicio1 ejercicio1.c -lm
Fecha: viernes 11 de agosto de 2022
Version: 1.0

*/

// librerias
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

// Funciones
void hello_world(int thread_num, int total_threads);

// Funcion principal
int main(int argc, char* argv[]) {
    int thread_count = 10; // Numero de hilos por defecto

    // Si se ingresa un numero de hilos por parametro, se toma ese valor
    if (argc > 1) {
        thread_count = strtol(argv[1], NULL, 10);
    }

    // Se ejecuta la funcion hello_world con el numero de hilos ingresado
    #pragma omp parallel num_threads(thread_count) // Se define el numero de hilos
    hello_world(omp_get_thread_num(), omp_get_num_threads());

    return 0;
}

// Funcion hello world
void hello_world(int thread_num, int total_threads) {
    printf("Hello from thread %d of %d !\n", thread_num, total_threads);
}