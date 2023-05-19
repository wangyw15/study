#include <iostream>
#include <random>
#include <memory>

#include "defines.h"
#include "searches/searches.h"

using namespace std;

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
    shared_ptr<int[]> ordered(new int[1000]);
    generate_ordered_array(ordered, 1000);
    search_result result = interpolation_search(235, ordered, 1000);
    cout << result.name << ", " << result.position << ", " << result.comparisions << endl;
    return 0;
}