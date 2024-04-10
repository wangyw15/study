//本程序用GPGPU计算矩阵乘：A[M,K] * B[K,N] = C[M,N]
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 1024
#define N 512
#define K 1024

//kernel函数，这个函数是运行在CUDA核心上的，负责计算 结果矩阵的一个元素
__global__ void multiplyKernel(const int *dev_A, const int *dev_B, int *dev_C) {
    int Row = blockIdx.y * blockDim.y + threadIdx.y; //行
    int Col = blockIdx.x * blockDim.x + threadIdx.x; //列
    int sum = 0;
    for (int k = 0; k < K; k++) sum += dev_A[Row * K + k] * dev_B[k * N + Col];
    dev_C[Row * N + Col] = sum; //C[M,N]
}

//检查C[x,y]计算是否正确
void check_matrix(int x, int y, int *A, int *B, int *C) {
    int sum = 0;
    for (int i = 0; i < K; i++) sum += A[x * K + i] * B[i * N + y];
    if (sum == C[x * N + y])
        printf("C[%d,%d] is right\n", x, y);
    else
        printf("C[%d,%d]=%d, sum=%d\n", x, y, C[x * N + y], sum);
}

// Helper function for using CUDA to multiply matrices in parallel.
cudaError_t multiplyWithCuda(int *C, const int *A, const int *B) {
    int *dev_A = 0;
    int *dev_B = 0;
    int *dev_C = 0;
    cudaError_t cudaStatus;
    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed! Any CUDA-capable GPU installed?");
        goto Error;
    }
    // Allocate GPU buffers(global memory) for three matrices A B C.
    cudaStatus = cudaMalloc((void **) &dev_A, M * K * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }
    cudaStatus = cudaMalloc((void **) &dev_B, K * N * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }
    cudaStatus = cudaMalloc((void **) &dev_C, M * N * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }
    // Copy input matrices from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(dev_A, A, M * K * sizeof(int), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }
    cudaStatus = cudaMemcpy(dev_B, B, K * N * sizeof(int), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    dim3 dimGrid(16, 32);   //grid的维度
    dim3 dimBlock(32, 32);  //block维度
    // Launch a kernel on the GPU with one thread for each element of C matrix.
    multiplyKernel<<<dimGrid, dimBlock >>>(dev_A, dev_B, dev_C);
    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "multiplyKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    // cudaDeviceSynchronize waits for the kernel to finish, and returns any errors.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d!\n", cudaStatus);
        goto Error;
    }
    // Copy output matrix from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(C, dev_C, M * N * sizeof(int), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }
    Error:
    cudaFree(dev_C);
    cudaFree(dev_A);
    cudaFree(dev_B);
    return cudaStatus;
}

//初始化矩阵
void init(int rowNum, int colNum, int *matrix) {
    srand((unsigned int) time(0));
    for (int i = 0; i < rowNum * colNum; i++) matrix[i] = rand() % 200;
}

int main() {
    int *A = (int *) malloc(M * K * sizeof(int));  //A[M,K]
    int *B = (int *) malloc(K * N * sizeof(int));  //B[K,N]
    int *C = (int *) malloc(M * N * sizeof(int));  //C[M,N] 结果矩阵
    //initialize matrix A and B
    init(M, K, A);
    init(K, N, B);
    clock_t start_clock, finish_clock; //for timing
    double duration_seconds;
    start_clock = clock();
    cudaError_t cudaStatus = multiplyWithCuda(C, A, B);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "multiplyWithCuda failed!");
        return 1;
    }
    finish_clock = clock();
    duration_seconds = (double) (finish_clock - start_clock) / CLOCKS_PER_SEC;
    printf("CUDA use time (s): %f\n", duration_seconds);
    printf("================================================\n");
    // cudaDeviceReset must be called before exiting in order for profiling and
    // tracing tools such as Nsight and Visual Profiler to show complete traces.
    cudaStatus = cudaDeviceReset();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceReset failed!");
        return 1;
    }
    check_matrix(1023, 511, A, B, C);//检查C[1023,511]是否计算正确
    free(A);
    free(B);
    free(C);
    return 0;
}
