#include "sorts.h"

void filter_down(std::shared_ptr<int[]> array, int low, int high, sort_result& result)
{
    int f = low, i = 2 * low + 1;
    int e = array[low];
    while (i <= high)
    {
        result.comparisons++;
        if (i < high && array[i] < array[i + 1])
        {
            i++;
        }
        result.comparisons++;
        if (e < array[i])
        {
            array[f] = array[i];
            f = i;
            i = 2 * f + 1;
        }
        else
        {
            break;
        }
    }
    array[f] = e;
}

sort_result heap_sort(std::shared_ptr<int[]> array, int size)
{
    sort_result result;
    result.name = "heap sort";
    result.swaps = 0;
    result.comparisons = 0;

    for (int i = (size - 2) / 2; i >= 0; i--)
    {
        filter_down(array, i, size - 1, result);
    }
    for (int i = size - 1; i > 0; i--)
    {
        result.swaps++;
        std::swap(array[0], array[i]);
        filter_down(array, 0, i - 1, result);
    }

    return result;
}
