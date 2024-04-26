#include <chrono>
#include <iostream>
#include <future>
#include <cstring>
#include <vector>
#include <algorithm>

constexpr unsigned int KB = 1 << 10;
constexpr unsigned int MB = 1 << 20;
constexpr unsigned int GB = 1 << 30;

constexpr unsigned int ARRAY_SIZE = 1*GB;
constexpr unsigned int ITERATIONS = 100;
constexpr unsigned int THREADS = 16;
typedef char test_size_t;

double calculate_speed(std::chrono::microseconds duration) {
    return ((double)ARRAY_SIZE / (double)GB) / ((double)duration.count() / (double)ITERATIONS / (double)1000000);
}

int main() {
    test_size_t* arr = (test_size_t*)calloc(ARRAY_SIZE, sizeof(test_size_t));

    std::vector<std::future<void>> futures;
    futures.reserve(THREADS * sizeof(std::future<void>));

    auto start = std::chrono::high_resolution_clock::now();

    for (unsigned int i = 0; i < THREADS; i++) {
        auto length = ARRAY_SIZE / THREADS;
        auto begin = arr + i * length;
        auto end = begin + length;
        futures.push_back(std::async([begin, end] {
            for (unsigned int j = 0; j < ITERATIONS; j++) {
                std::fill(begin, end, '6');
            }
        }));
    }

    for (auto &future: futures) {
        future.get();
    }

    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << calculate_speed(duration) << "GB/s" << std::endl;

    delete[] arr;

    return 0;
}