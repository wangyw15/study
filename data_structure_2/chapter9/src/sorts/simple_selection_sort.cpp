#include "sorts.h"

sort_result simple_selection_sort(std::shared_ptr<int[]> array, int size)
{
    sort_result result;
    result.name = "simple selection sort";
    result.swaps = 0;
    result.comparisons = 0;
    
    for (int i = 0; i < size - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            result.comparisons++;
            if (array[j] < array[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            result.swaps++;
            std::swap(array[i], array[min]);
        }
    }
    return result;
}
