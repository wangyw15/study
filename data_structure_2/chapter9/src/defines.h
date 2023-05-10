#ifndef DEFINES
#define DEFINES

#include <functional>
#include <memory>

struct sort_result
{
    int comparisons;
    int swaps;
};

using sort = std::function<sort_result(std::shared_ptr<int[]>, int)>;

#endif
