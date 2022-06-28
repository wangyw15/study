#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <algorithm>

#include "dto.h"
#include "rand/rand.h"
#include "score/score.h"
#include "sort/sort_string.h"

#include "sort/bubble_sort.h"
#include "sort/insert_sort.h"
#include "sort/merge_sort.h"
#include "sort/selection_sort.h"
#include "sort/quick_sort.h"

using namespace std;
using namespace chrono;

#define SORT_MAX_SIZE 65536
#define SORT_ALGORITHM bubble_sort, optimized_bubble_sort, insert_sort, optimized_insert_sort, selection_sort, merge_sort_iter, merge_sort_rec_with_counter, quick_sort_with_counter, optimized_quick_sort_with_counter
#define STR_SIZE 30

const char algo_name[][STR_SIZE] = {"冒泡排序", "冒泡排序（优化）", "插入排序", "插入排序（优化）", "选择排序", "归并排序（迭代）", "归并排序（递归）", "快速排序", "快速排序（优化）"};
const char data_type_name[][STR_SIZE] = {"降序", "升序", "均匀分布", "正态分布"};

template <typename T>
void init_data(T *data, int n, int flag)
{
    int i;
    switch (flag)
    {
    case 0:
        for (i = 0; i < n; i++)
        {
            data[i] = n - 1 - i;
        }
        break; // 逆序（从大到小）
    case 1:
        for (i = 0; i < n; i++)
        {
            data[i] = i;
        }
        break; // 顺序（从小到大）
    case 2:
        for (i = 0; i < n; i++)
        {
            data[i] = (T)uniform_rand(54, 90);
        }
        break; // [54,90]上的均匀分布
    case 3:
        for (i = 0; i < n; i++)
        {
            data[i] = (T)gauss_rand(72, 6 * 6);
        }
        break; // 正态分布，均值72，方差36（根方差6）
    }
}

template <typename T>
bool verify(T *data, int size)
{
    for (auto i = 1; i < size; i++)
    {
        if (data[i - 1] > data[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
test_result *test_sort(T *data, int size, sort_result *(*func)(T *, int))
{
    // 计时
    auto start_time = high_resolution_clock::now();
    auto sort_ret = func(data, size);
    auto end_time = high_resolution_clock::now();

    // 生成测试结果
    auto ret = new test_result;
    ret->assign = sort_ret->assign;
    ret->compare = sort_ret->compare;
    ret->time = duration_cast<microseconds>(end_time - start_time).count() / 1000.0;
    ret->correct = verify(data, size);
    delete sort_ret;
    return ret;
}

template <typename T>
void test(const T &x)
{
    sort_result *(*number_algorithm[])(T *, int) = {SORT_ALGORITHM};
    auto algo_count = sizeof(number_algorithm) / sizeof(*number_algorithm);

    for (auto i = 0; i < algo_count; i++)
    {
        for (auto size = 1024; size <= SORT_MAX_SIZE; size *= 2)
        {
            T *data = new T[size];
            for (auto data_type = 0; data_type < 4; data_type++)
            {
                init_data(data, size, data_type);
                auto result = test_sort(data, size, number_algorithm[i]);
                cout << algo_name[i] << ","
                     << typeid(T).name() << ","
                     << size << ","
                     << data_type_name[data_type] << ","
                     << (result->compare) << ","
                     << (result->assign) << ","
                     << (result->time) << ","
                     << (result->correct ? "true" : "false") << endl;
                delete result;
            }
            delete[] data;
        }
    }
}

void test_score()
{
    sort_result *(*number_algorithm[])(score *, int) = {SORT_ALGORITHM};
    auto algo_count = sizeof(number_algorithm) / sizeof(*number_algorithm);

    for (auto i = 0; i < algo_count; i++)
    {
        for (auto size = 1024; size <= SORT_MAX_SIZE; size *= 2)
        {
            auto *data = new score[size];
            init_score(data, size);
            auto result = test_sort(data, size, number_algorithm[i]);
            cout << algo_name[i] << ","
                 << "score,"
                 << size << ","
                 << "score,"
                 << (result->compare) << ","
                 << (result->assign) << ","
                 << (result->time) << ","
                 << (result->correct ? "true" : "false") << endl;
            delete result;
            delete[] data;
        }
    }
}

int main()
{
    // 设置随机数发生器的种子
    srand(time(NULL));
    // csv表头
    cout << "排序算法,数据类型,数据大小,数据分布,判断次数,赋值次数,用时 (ms),正确性" << endl;
    // 测试int类型数据
    test(int(0));
    // 测试double类型数据
    test(double(0));
    // 测试score类型数据
    test_score();
    // 测试string类型数据
    TestString();
    return 0;
}