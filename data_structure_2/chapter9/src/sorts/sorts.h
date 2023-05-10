#ifndef SORTS
#define SORTS

#include "../defines.h"

sort_result straight_insert_sort(std::shared_ptr<int[]> array, size_t size);
sort_result shell_sort(std::shared_ptr<int[]> array, size_t size);
sort_result bubble_sort(std::shared_ptr<int[]> array, size_t size);
sort_result quick_sort(std::shared_ptr<int[]> array, size_t size);
sort_result simple_selection_sort(std::shared_ptr<int[]> array, size_t size);
sort_result heap_sort(std::shared_ptr<int[]> array, size_t size);
sort_result merge_sort(std::shared_ptr<int[]> array, size_t size);
sort_result radix_sort(std::shared_ptr<int[]> array, size_t size);

#endif
