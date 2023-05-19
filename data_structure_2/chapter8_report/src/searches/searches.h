#ifndef SEARCH_ALGORITHMS
#define SEARCH_ALGORITHMS

#include <memory>
#include "../defines.h"

search_result binary_search(int target, std::shared_ptr<int[]> data, int n);

#endif
