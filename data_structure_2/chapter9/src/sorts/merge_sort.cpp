#include "sorts.h"

void merge(std::shared_ptr<int[]> array, int low, int mid, int high, sort_result& result)
{
    std::shared_ptr<int[]> temp_arr(new int[high + 1]);
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high)
    {
        temp_arr[k++] =
            array[i] <= array[j] ? array[i++] : array[j++];
        result.comparisons++;
    }
    while (i <= mid)
    {
        temp_arr[k++] = array[i++];
    }
    while (j <= high)
    {
        temp_arr[k++] = array[j++];
    }
    for (i = low; i <= high; i++)
    {
        array[i] = temp_arr[i];
    }
    result.swaps = high - low + 1;
    temp_arr.reset();
    temp_arr = nullptr;
}

void merge_sort_impl(std::shared_ptr<int[]> array, int low, int high, sort_result& result)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        merge_sort_impl(array, low, mid, result);
        merge_sort_impl(array, mid + 1, high, result);
        merge(array, low, mid, high, result);
    }
}

sort_result merge_sort(std::shared_ptr<int[]> array, int size)
{
    sort_result result;
    result.name = "merge sort";
    result.swaps = 0;
    result.comparisons = 0;

    merge_sort_impl(array, 0, size - 1, result);

    return result;
}
