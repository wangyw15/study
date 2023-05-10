#include "sorts.h"

sort_result bubble_sort(std::shared_ptr<int[]> array, int size)
{
    sort_result result;
    result.name = "bubble sort";
    result.swaps = 0;
    result.comparisons = 0;

    for (int i = 0; i < size - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < size - 1 - i; j++)
        {
            result.comparisons++;
            if (array[j] > array[j + 1])
            {
                result.swaps++;
                std::swap(array[j], array[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }

    return result;
}
