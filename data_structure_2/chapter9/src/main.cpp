#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <fstream>

#include "defines.h"
#include "sorts/sorts.h"

using namespace std;
using array_generator = function<string(shared_ptr<int[]>, int)>;

string generate_ordered_array(shared_ptr<int[]> array, int n)
{
    for (int i = 0; i < n; i++)
    {
        array[i] = i;
    }
    return "ordered";
}

string generate_reversed_array(shared_ptr<int[]> array, int n)
{
    for (int i = 0; i < n; i++)
    {
        array[i] = n - 1 - i;
    }
    return "reversed";
}

string generate_random_array(shared_ptr<int[]> array, int n)
{
    static default_random_engine engine;
    uniform_int_distribution<int> dis(0, n - 1);
    for (int i = 0; i < n; i++)
    {
        array[i] = dis(engine);
    }
    return "random";
}

string generate_partially_ordered_array(shared_ptr<int[]> array, int n)
{
    generate_ordered_array(array, n);

    static default_random_engine engine;
    uniform_int_distribution<int> dis(0, n - 1);

    static vector<int> swap_location;
    while (swap_location.size() < n / 5)
    {
        swap_location.push_back(dis(engine));
    }

    for (int i = 0; i < n / 10; i++)
    {
        swap(array[swap_location[i]], array[swap_location[i + 1]]);
    }
    return "partially ordered";
}

bool validate_ordered(shared_ptr<int[]> array, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    // init algorithms
    vector<sort_algorithm> algorithms;
    algorithms.push_back(straight_insert_sort);
    algorithms.push_back(shell_sort);
    algorithms.push_back(bubble_sort);
    algorithms.push_back(quick_sort);
    algorithms.push_back(simple_selection_sort);
    algorithms.push_back(heap_sort);
    algorithms.push_back(merge_sort);
    algorithms.push_back(radix_sort);

    // data orders
    vector<array_generator> generators;
    generators.push_back(generate_ordered_array);
    generators.push_back(generate_reversed_array);
    generators.push_back(generate_random_array);
    generators.push_back(generate_partially_ordered_array);

    // data scale
    vector<int> scales;
    scales.push_back(10);
    scales.push_back(100);
    scales.push_back(1000);
    // scales.push_back(1000000);
    // scales.push_back(100000000);

    // file writer
    ofstream writer("result.csv");

    // csv header
    writer << "algorithm, data scale, data type, duration, comparisons, swaps, "
           << "valid" << endl;
    cout << "algorithm, data scale, data type, duration, comparisons, swaps, "
           << "valid" << endl;

    for (sort_algorithm& func : algorithms)
    {
        for (int scale : scales)
        {
            for (array_generator& generator : generators)
            {
                // generate data
                shared_ptr<int[]> data(new int[scale]);
                string data_type = generator(data, scale);

                // run
                auto start = chrono::high_resolution_clock::now();
                sort_result result = func(data, scale);
                auto duration = chrono::duration_cast<chrono::microseconds>(
                    chrono::high_resolution_clock::now() - start);

                // print data
                writer << result.name << ", " << scale << ", " << data_type
                       << ", " << duration.count() << ", " << result.comparisons
                       << ", " << result.swaps << ", "
                       << (validate_ordered(data, scale) ? "true" : "false")
                       << endl;
                cout << result.name << ", " << scale << ", " << data_type
                       << ", " << duration.count() << ", " << result.comparisons
                       << ", " << result.swaps << ", "
                       << (validate_ordered(data, scale) ? "true" : "false")
                       << endl;
            }
        }
    }
    writer.close();
    return 0;
}
