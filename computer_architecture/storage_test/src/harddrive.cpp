#include <chrono>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <random>

constexpr unsigned int KB = 1 << 10;
constexpr unsigned int MB = 1 << 20;
constexpr unsigned int GB = 1 << 30;

constexpr unsigned int FILE_SIZE = 2 * GB;
constexpr unsigned int WRITE_SIZE = 1 * MB;
constexpr double FILE_SIZE_MB = (double)FILE_SIZE / (double)MB;
typedef char test_size_t;

double calculate_speed(std::chrono::microseconds duration) {
    return FILE_SIZE_MB / ((double)duration.count() / (double)1000000);
}

std::string random_name(unsigned int length) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 25);

    std::string name;
    name.reserve(length);
    for (unsigned int i = 0; i < length; i++)
        name += 'a' + dis(gen);

    return name;
}

void write_test(const std::string& filename) {
    std::ofstream file;
    file.rdbuf()->pubsetbuf(nullptr, 0);
    file.open(filename);

    std::string text;
    text.reserve(WRITE_SIZE);
    auto start = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < FILE_SIZE; i++) {
        if (i % WRITE_SIZE == 0) {
            file << text << "\n";
            text = "";
        }
        text += "a";
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "write, "
              << FILE_SIZE_MB << ", "
              << duration.count() << ", "
              << calculate_speed(duration)
              << std::endl;
}

void read_test(const std::string& filename) {
    std::ifstream file;
    file.rdbuf()->pubsetbuf(nullptr, 0);
    file.open(filename);
    file.clear();

    std::string text;
    text.reserve(WRITE_SIZE);
    auto start = std::chrono::high_resolution_clock::now();
    while (file)  file.read(text.data(), WRITE_SIZE);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "read, "
              << FILE_SIZE_MB << ", "
              << duration.count() << ", "
              << calculate_speed(duration)
              << std::endl;
}

int main() {
    std::cout << "type, size (MB), duration (microseconds), speed (MB/s)" << std::endl;
    auto filename = random_name(10);

    write_test(filename);
    read_test(filename);

    std::filesystem::remove(filename);

    return 0;
}
