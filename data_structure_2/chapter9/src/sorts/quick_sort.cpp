#include "sorts.h"

void quick_sort_impl(std::shared_ptr<int[]> array, int low, int high, sort_result& result)
{
    int pivot = array[low];
    int i = low, j = high;
    while (i < j)
    {
        while (i < j && array[j] >= pivot)
        {
            result.comparisons++;
            j--;
        }
        
        result.comparisons++;
        if (i < j)
        {
            array[i++] = array[j];
            result.swaps++;
        }
        
        while (i < j && array[i] <= pivot)
        {
            result.comparisons++;
            i++;
        }
        
        result.comparisons++;
        if (i < j)
        {
            array[j--] = array[i];
            result.swaps++;
        }
        
        array[i] = pivot;
        if (low < i - 1)
        {
            quick_sort_impl(array, low, i - 1, result);
        }
        if (i + 1 < high)
        {
            quick_sort_impl(array, i + 1, high, result);
        }
    }
}

sort_result quick_sort(std::shared_ptr<int[]> array, int size)
{
    sort_result result;
    result.name = "quick sort";
    result.comparisons = 0;
    result.swaps = 0;
    quick_sort_impl(array, 0, size - 1, result);
    return result;
}
