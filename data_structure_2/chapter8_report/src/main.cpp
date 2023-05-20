#include <iostream>
#include <random>
#include <memory>
#include <vector>
#include <fstream>
#include <chrono>

#include "defines.h"
#include "searches/searches.h"

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

int main()
{
    // search algorithms
    vector<search_algorithm> algorithms;
    algorithms.push_back(binary_search);
    algorithms.push_back(interpolation_search);
    algorithms.push_back(fibonacci_search);

    // array generators
    vector<array_generator> generators;
    generators.push_back(generate_ordered_array);
    // generators.push_back(generate_reversed_array);
    // generators.push_back(generate_random_array);
    // generators.push_back(generate_partially_ordered_array);

    // data scale
    vector<int> scales;
    scales.push_back(10);
    scales.push_back(100);
    scales.push_back(1000);

    // file writer
    ofstream writer("result.csv");

    // csv header
    writer << "algorithm, data scale, data type, duration, comparisons, position" << endl;
    cout << "algorithm, data scale, data type, duration, comparisons, position" << endl;
    
    for (search_algorithm& func : algorithms)
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
                search_result result = func(0, data, scale);
                auto duration = chrono::duration_cast<chrono::microseconds>(
                    chrono::high_resolution_clock::now() - start);

                // print data
                writer << result.name << ", " << scale << ", " << data_type
                       << ", " << duration.count() << ", " << result.comparisons
                       << ", " << result.position << endl;
                cout << result.name << ", " << scale << ", " << data_type
                       << ", " << duration.count() << ", " << result.comparisons
                       << ", " << result.position << endl;
            }
        }
    }

    shared_ptr<int[]> ordered(new int[1000]);
    generate_ordered_array(ordered, 1000);
    search_result result = fibonacci_search(235, ordered, 1000);
    cout << result.name << ", " << result.position << ", " << result.comparisons << endl;
    return 0;
}