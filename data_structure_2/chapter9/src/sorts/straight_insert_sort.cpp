#include "sorts.h"

sort_result straight_insert_sort(std::shared_ptr<int[]> array, int size)
{
    sort_result result;
    result.name = "straight insert sort";
    result.comparisons = 0;
    result.swaps = 0;

    for (int i = 1; i < size; i++)
    {
        int temp = array[i];
        int j = i - 1;
        for (; j >= 0; j--)
        {
            result.comparisons++;
            if (array[j] > temp)
            {
                result.swaps++;
                array[j + 1] = array[j];
            }
            else
            {
                break;
            }
        }
        array[j + 1] = temp;
    }

    return result;
}
