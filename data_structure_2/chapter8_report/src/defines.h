#ifndef SEARCH_DEFINES
#define SEARCH_DEFINES

#include <functional>
#include <string>
#include <memory>

struct search_result
{
    std::string name = "";
    long comparisons = 0;
    int position = -1;
};

using search_algorithm = std::function<search_result(int, std::shared_ptr<int[]>, int)>;

#endif
