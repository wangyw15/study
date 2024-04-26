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
constexpr unsigned int MAX_THREADS = 16;
typedef char test_size_t;

double calculate_speed(std::chrono::microseconds duration) {
    return ((double)ARRAY_SIZE / (double)GB) / ((double)duration.count() / (double)ITERATIONS / (double)1000000);
}

void write_test(test_size_t *arr, unsigned int thread_count) {
    std::vector<std::future<void>> futures;
    futures.reserve(thread_count * sizeof(std::future<void>));

    auto start = std::chrono::high_resolution_clock::now();

    for (unsigned int i = 0; i < thread_count; i++) {
        auto length = ARRAY_SIZE / thread_count;
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
    std::cout << "write, "
              << thread_count << ", "
              << duration.count() << ", "
              << calculate_speed(duration)
              << std::endl;
}

void read_test(test_size_t *arr, unsigned int thread_count) {
    std::vector<std::future<void>> futures;
    futures.reserve(thread_count * sizeof(std::future<void>));

    auto start = std::chrono::high_resolution_clock::now();

    for (unsigned int i = 0; i < thread_count; i++) {
        auto length = ARRAY_SIZE / thread_count;
        auto begin = arr + i * length;
        auto end = begin + length;
        futures.push_back(std::async([begin, end] {
            for (unsigned int j = 0; j < ITERATIONS; j++) {
                for (auto it = begin; it != end; it++) {
                    volatile auto val = *it;
                }
            }
        }));
    }

    for (auto &future: futures) {
        future.get();
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "read, "
              << thread_count << ", "
              << duration.count() << ", "
              << calculate_speed(duration)
              << std::endl;
}

int main() {
    std::cout << "type, threads (n), duration (microseconds), speed (GB/s)" << std::endl;
    auto arr = (test_size_t*)calloc(ARRAY_SIZE, sizeof(test_size_t));

    for (unsigned int threads = 1; threads <= MAX_THREADS; threads++) {
        write_test(arr, threads);
    }

    for (unsigned int threads = 1; threads <= MAX_THREADS; threads++) {
        read_test(arr, threads);
    }

    delete[] arr;
    return 0;
}
