#include <string>
#include <memory>

#include "../defines.h"

search_result binary_search(int target, std::shared_ptr<int[]> data, int n)
{
    search_result result;
    result.name = "Binary search";

    int low = 0, high = n, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
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
