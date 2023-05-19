#include <string>
#include <memory>
#include "../defines.h"

search_result interpolation_search(int target, std::shared_ptr<int[]> data, int n)
{
    search_result result;
    result.name = "Interpolation search";

    int low = 0, high = n - 1, mid;
    while (low < high)
    {
        mid = low + (target - data[low]) / (data[high] - data[low]) * (high - low);
        result.comparisions++;
        if (target < data[mid])
        {
            high = mid - 1;
        }
        else if (target > data[mid])
        {
            low = mid + 1;
        }
        else
        {
            result.position = mid;
            break;
        }
    }

    return result;
}
