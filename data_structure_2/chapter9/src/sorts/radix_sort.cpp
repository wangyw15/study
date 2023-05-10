#include "sorts.h"

sort_result radix_sort(std::shared_ptr<int[]> array, int size)
{
    sort_result result;
    result.name = "radix sort";
    result.swaps = 0;
    result.comparisons = 0;

    std::shared_ptr<int[]> output(new int[size]);
    // find max element
    int max_element = array[0];
    for (int i = 1; i < size; i++)
    {
        result.comparisons++;
        if (array[i] > max_element)
        {
            max_element = array[i];
        }
    }
    
    for (int exp = 1; max_element / exp > 0; exp *= 10)
    {
        int count[10] = {0};
        // count
        for (int i = 0; i < size; i++)
        {
            count[(array[i] / exp) % 10]++;
        }
        // calculate position
        for (int i = 1; i < 10; i++)
        {
            count[i] += count[i - 1];
        }
        // put elements
        for (int i = size - 1; i >= 0; i--)
        {
            output[--count[(array[i] / exp) % 10]] = array[i];
        }
        for (int i = 0; i < size; i++)
        {
            array[i] = output[i];
            result.swaps++;
        }
    }
    return result;
}
