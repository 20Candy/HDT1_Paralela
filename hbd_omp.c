/*
Autor: Carol Arevalo
Para compilar: gcc -o hbd_omp hbd_omp.c -lm
Fecha: viernes 11 de agosto de 2022
Version: 1.0

*/

// librerias
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

// Funciones
void hello_world(int thread_id, int total_threads, int age);

// Funcion principal
int main(int argc, char* argv[]) {
    // Edad por defecto
    int age = 20;

    if (argc > 1) {
        age = strtol(argv[1], NULL, 10);
    }

    // Se ejecuta la funcion hello_world con el numero de hilos ingresado
    int age = strtol(argv[1], NULL, 10);

    // Se define el numero de hilos
    #pragma omp parallel
    hello_world(omp_get_thread_num(), omp_get_num_threads(), age);

    return 0;
}

// Funcion birthday greetings
void hello_world(int thread_id, int total_threads, int age) {
    if (thread_id % 2 == 0) {
        printf("Saludos del hilo %d\n", thread_id);
    } else {
        printf("Feliz cumpleaños número %d!\n", age);
    }
}