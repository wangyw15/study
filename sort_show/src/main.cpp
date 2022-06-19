#include <iostream>
#include "sort/sort.h"
#include "util/util.h"
#include "visualizer/visualizer.h"

using namespace std;

int main()
{
    // auto algorithms = {optimized_bubble_sort};
    // p_sort_algorithm p = optimized_bubble_sort;
    visualizer *vis= new visualizer();
    optimized_insert_sort(vis);
    return 0;
}