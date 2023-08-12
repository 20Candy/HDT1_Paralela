#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
        printf("Usage: %s a b n\n", argv[0]);
        return 1;
    }

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int n = atoi(argv[3]);

    double result1 = trapezoides(a, b, n, f1);
    double result2 = trapezoides(a, b, n, f2);
    double result3 = trapezoides(a, b, n, f3);

    printf("Con n = %d trapezoides, nuestra aproximacion de la integral de %.6lf a %.6lf:\n", n, a, b);
    printf("Para x^2: %.10lf\n", result1);
    printf("Para 2x^3: %.10lf\n", result2);
    printf("Para sin(x): %.10lf\n", result3);

    return 0;
}