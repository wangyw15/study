#include <chrono>
#include <iostream>
#include <algorithm>

constexpr unsigned int KB = 1 << 10;
constexpr unsigned int MB = 1 << 20;
constexpr unsigned int GB = 1 << 30;

constexpr unsigned int ARRAY_SIZE = 16*MB;
constexpr unsigned int STEP = 64*KB;
typedef char test_size_t;

double calculate_speed(std::chrono::microseconds duration) {
    return ((double)ARRAY_SIZE / (double)GB) / ((double)duration.count() / (double)1000000);
}

void write_test(test_size_t *array_data) {
    for (unsigned int i = STEP; i <= ARRAY_SIZE; i += STEP) {
        auto start = std::chrono::high_resolution_clock::now();
        std::fill(array_data, array_data + i, '6');
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "write, "
                  << i << ", "
                  << duration.count() << ", "
                  << calculate_speed(duration)
                  << std::endl;
    }
}

void read_test(const test_size_t *array_data) {
    for (unsigned int i = STEP; i <= ARRAY_SIZE; i += STEP) {
        auto start = std::chrono::high_resolution_clock::now();
        for (unsigned int j = 0; j < i; j++) {
            auto volatile x = array_data[j];
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "read, "
                  << i << ", "
                  << duration.count() << ", "
                  << calculate_speed(duration)
                  << std::endl;
    }
}

int main() {
    std::cout << "type, size (byte), duration (microseconds), speed (GB/s)" << std::endl;
    auto arr = (test_size_t*)calloc(ARRAY_SIZE, sizeof(test_size_t));

    write_test(arr);
    read_test(arr);

    delete[] arr;
    return 0;
}
