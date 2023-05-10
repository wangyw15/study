#include "sorts.h"

sort_result straight_insert_sort(std::shared_ptr<int[]> array, size_t size)
{
    sort_result result;
    result.comparisons = 0;
    result.swaps = 0;

    for (int i = 1; i < size; i++)
    {
        int temp = array[i];
        int j;
        for (j = i - 1; j >= 0; j--)
        {
            result.comparisons++;
            if (array[j] > temp)
            {
                array[j + 1] = array[j];
                result.swaps++;
            }
        }
        array[j + 1] = temp;
    }

    return result;
}
