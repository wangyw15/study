#include <array>
#include <chrono>
#include <iostream>
#include <random>

constexpr unsigned int KB = 1 << 10;
constexpr unsigned int MB = 1 << 20;

constexpr unsigned int ITERATIONS = 1000;
constexpr unsigned int STEP = 64 * KB;
constexpr unsigned int MAX_DATA_SIZE = 36 * MB;

typedef char test_type;

int random_number(int max = CHAR_MAX) {

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, max);
    return dis(gen);
}

long long test_latency(unsigned int physical_size) {
    // initialize data
    auto array_size = physical_size / sizeof(test_type);
    char *data = new char[array_size];
    for (auto i = 0; i < array_size; i++) {
        data[i] = random_number();
    }

    // initialize access array
    std::array<unsigned int, ITERATIONS> access{};
    for (auto &i : access) {
        i = random_number(array_size);
    }
    
    // start
    auto start = std::chrono::high_resolution_clock::now();
    for (auto &i : access) {
        auto volatile tmp = data[i];
    }
    auto end = std::chrono::high_resolution_clock::now();

    delete[] data;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

int main() {
    std::cout << "size (byte), latency (nanoseconds)" << std::endl;
    for (auto size = STEP; size <= MAX_DATA_SIZE; size += STEP) {
        std:: cout << size << ", " << test_latency(size) << std::endl;
    }
    return 0;
}
