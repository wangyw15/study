#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>
#include <random>
#include <limits>
#include <future>

constexpr unsigned KB = 1 << 10;
constexpr unsigned MB = 1 << 20;
constexpr unsigned GB = 1 << 30;
constexpr unsigned MAX_THREADS = 16;


char random_number() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, std::numeric_limits<char>::max());
    return dis(gen);
}


void test_bandwidth() {
    std::vector<char> nums;
    for (unsigned i = 0; i < GB; i++) {
        nums.push_back(random_number());
    }

    for (unsigned thread_count = 1; thread_count <= MAX_THREADS; thread_count++) {
        std::vector<std::future<int>> futures;
        auto slice_len = nums.size() / thread_count;

        for (size_t thread = 0; thread < thread_count; thread++) {
            auto begin = nums.begin() + thread * slice_len;
            auto end = (thread == thread_count - 1) ? nums.end() : begin + slice_len;

            futures.push_back(std::async([begin, end] {
                int sum = 0;
                for (auto it = begin; it != end; it++) {
                    sum += *it;
                }
                return sum;
            }));
        }

        auto start = std::chrono::high_resolution_clock::now();
        int sum;
        for (auto& future : futures) {
            sum += future.get();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        auto speed = nums.size() / duration;
        std::cout << thread_count << ", " << duration << ", " << speed << std::endl;
    }
}


int main() {
    std::cout << "thread_count (n), duration (microseconds), speed (KB/microseconds)" << std::endl;
    test_bandwidth();
    return 0;
}
