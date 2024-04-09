#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MATRIX_SIZE 200

void compute(int n, const float a[], const float b[], float c[])
{
    int x, y, k;
#pragma omp parallel for collapse(3) shared(n, a, b, c) private(y, x, k)
    for (y = 0; y < n; y++)
        for (x = 0; x < n; x++)
            for (k = 0; k < n; k++)
                c[n * y + x] += a[n * y + k] * b[n * k + x];
}

float random_float()
{
    return (float)rand() / RAND_MAX;
}

float A[MATRIX_SIZE * MATRIX_SIZE];
float B[MATRIX_SIZE * MATRIX_SIZE];
float C[MATRIX_SIZE * MATRIX_SIZE];

int main()
{
    // Initialize random seed
    srand(0xffb7c5);

    printf("Initializing matrices\n");
    // Initialize A and B
    for (int i = 0; i < MATRIX_SIZE * MATRIX_SIZE; i++)
    {
        A[i] = random_float();
        B[i] = random_float();
    }

    printf("Matrix size: %dx%d\n", MATRIX_SIZE, MATRIX_SIZE);

    double duration;
    int matrix_size = MATRIX_SIZE * MATRIX_SIZE, n;
    clock_t start, end;

    // parallel 16
    start = clock();
#pragma omp parallel for num_threads(16) shared(A, B, C) private(n)
    for (n = 0; n < matrix_size; n++)
        compute(MATRIX_SIZE, A, B, C);
    end = clock();

    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Parallel 16: %f\n", duration);

    return 0;
}
