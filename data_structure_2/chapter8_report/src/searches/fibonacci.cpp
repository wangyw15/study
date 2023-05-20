#include <string>
#include <memory>

#include "../defines.h"

std::shared_ptr<int[]> _fibonacci_array(new int[25]{
    1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025
});

search_result fibonacci_search(int target, std::shared_ptr<int[]> data, int n)
{
    search_result result;
    result.name = "Fibonacci search";

    int low = 0, high = n - 1, mid, k = 0;

    // filled the array
    while (_fibonacci_array[k] < high)
    {
        k++;
    }
    std::shared_ptr<int[]> filled(new int[_fibonacci_array[k]]);
    for (int i = 0; i < _fibonacci_array[k]; i++)
    {
        if (i < n)
        {
            filled[i] = data[i];
        }
        else
        {
            filled[i] = data[n - 1];
        }
    }

    // search
    while (low <= high)
    {
        // in case of overflow
        if (k < 2)
        {
            mid = low;
        }
        else
        {
            mid = low + _fibonacci_array[k - 1] - 1;
        }

        result.comparisons++;
        if (target < filled[mid])
        {
            high = mid - 1;
            k -= 1;
        }
        else if (target > filled[mid])
        {
            low = mid + 1;
            k -= 2;
        }
        else
        {
            result.position = mid;
            break;
        }
    }

    return result;
}