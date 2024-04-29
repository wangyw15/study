#include <array>
#include <chrono>
#include <iostream>
#include <iterator>
#include <limits>
#include <random>

constexpr unsigned int KB = 1 << 10;
constexpr unsigned int MB = 1 << 20;

constexpr unsigned int ITERATIONS = 1000;
constexpr unsigned int STEP = 16 * KB;
constexpr unsigned int MAX_DATA_SIZE = 1 * MB;

constexpr char CHAR_MAX = std::numeric_limits<char>::max();

typedef char test_type;

int random_number(int max = CHAR_MAX) {

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, CHAR_MAX);
    return dis(gen);
}

double test_latency(int physical_size) {
    // initialize data
    auto array_size = physical_size / sizeof(test_type);
    char data[array_size];
    for (auto &i : data) {
        i = random_number();
    }

    // initialize access array
    std::array<unsigned int, ITERATIONS> access;
    for (auto &i : data) {
        i = random_number(array_size);
    }
    
    // start
    auto start = std::chrono::high_resolution_clock::now();
    for (auto &i : data) {
        auto volatile tmp = data[i];
    }
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    std::cout << "size (byte), latency (microseconds)" << std::endl;
    for (auto size = STEP; size <= MAX_DATA_SIZE; size += STEP) {
        std:: cout << size << ", " << test_latency(size) << std::endl;
    }
    return 0;
}
