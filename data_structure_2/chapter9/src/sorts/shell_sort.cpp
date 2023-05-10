#include "sorts.h"

sort_result shell_sort(std::shared_ptr<int[]> array, int size)
{
    sort_result result;
    result.name = "shell sort";
    result.comparisons = 0;
    result.swaps = 0;

    for (int step = size / 2; step > 0; step /= 2)
    {
        for (int i = step; i < size; i++)
        {
            int temp = array[i];
            int j = i - step;
            for (; j >= 0; j -= step)
            {
                result.comparisons++;
                if (array[j] > temp)
                {
                    array[j + step] = array[j];
                    result.swaps++;
                }
                else
                {
                    break;
                }
            }
            array[j + step] = temp;
        }
    }

    return result;
}
