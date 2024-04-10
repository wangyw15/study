#include <iostream>
#include <chrono>
#include <random>

#include "cuda_runtime.h"

#define ARRAY_SIZE 10000

__global__ void ArrayComputeCUDA(int n, const int a[], const int b[], int c[]) {
    for (int i = 0; i < n; i++) {
        c[i] = a[i] - b[i] * (i % 2 - 1);
    }
}

void ArrayComputeCPU(int n, const int a[], const int b[], int c[]) {
    for (int i = 0; i < n; i++) {
        // c[i] = a[i] - b[i] * (i % 2 - 1);
        if (i % 2 == 0) {
            c[i] = a[i] + b[i];
        }
        else {
            c[i] = a[i];
        }
    }
}

int main() {
    int device = 1;
    cudaGetDevice(&device);
    // Check GPU
    auto status = cudaSetDevice(device);
    if (status != cudaSuccess) {
        std::cerr << "cudaSetDevice failed! Any CUDA-capable GPU installed?" << std::endl;
        return 1;
    }

    // Define arrays
    int *a, *b, cpu[ARRAY_SIZE], *gpu;
    cudaMallocManaged(&a, ARRAY_SIZE * sizeof(int));
    cudaMallocManaged(&b, ARRAY_SIZE * sizeof(int));
    cudaMallocManaged(&gpu, ARRAY_SIZE * sizeof(int));

    // Initialize a and b
    std::random_device seed;
    std::mt19937_64 engine(seed());
    std::uniform_int_distribution<int> distribution(0, 100);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        a[i] = distribution(engine);
        b[i] = distribution(engine);
    }

    // Calculate by CPU
    auto start = std::chrono::high_resolution_clock::now();
    ArrayComputeCPU(ARRAY_SIZE, a, b, cpu);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "CPU time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << "ms" << std::endl;

    // Calculate by GPU
    dim3 dimGrid(16, 32);   // grid's dimension
    dim3 dimBlock(32, 32);  // block's dimension

    start = std::chrono::high_resolution_clock::now();
    cudaMemPrefetchAsync(a, ARRAY_SIZE * sizeof(int), device);
    cudaMemPrefetchAsync(b, ARRAY_SIZE * sizeof(int), device);
    ArrayComputeCUDA<<<dimGrid, dimBlock>>>(ARRAY_SIZE, a, b, gpu);
    cudaDeviceSynchronize();
    end = std::chrono::high_resolution_clock::now();

    std::cout << "GPU time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << "ms" << std::endl;

    // Check the result
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (cpu[i] != gpu[i]) {
            std::cerr << "Error at " << i << ": " << cpu[i] << " != " << gpu[i] << std::endl;
            return 1;
        }
    }
    std::cout << "All results are correct!" << std::endl;

    return 0;
}
