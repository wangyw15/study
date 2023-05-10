#ifndef DEFINES
#define DEFINES

#include <functional>
#include <memory>
#include <string>

struct sort_result
{
    int comparisons = 0;
    int swaps = 0;
    std::string name = "";
};

using sort_algorithm = std::function<sort_result(std::shared_ptr<int[]>, int)>;

#endif
