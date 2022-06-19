#include <iostream>
#include "../visualizer/visualizer.h"

using namespace std;

void optimized_bubble_sort(visualizer *vis)
{
    // auto flag = true;
    // for (auto i = 0; i < vis->data_size - 1 && flag; i++)
    for (auto i = 0; i < vis->data_size - 1; i++)
    {
        // flag = false;
        for (auto j = 0; j < vis->data_size - 1 - i; j++)
        {
            if (vis->data[j] > vis->data[j + 1])
            {
                // swap(data[j], data[j + 1]);
                vis->visualize_swap(j, j + 1);
                // flag = true;
            }
        }
    }
}

int my_find(int target, int left, int right, int *nums)
{
    if (right - left <= 1)
    {
        if(nums[left] < target)
        {
            return right;
        }
        else
        {
            return left;
        }
    }
    else
    {
        int mid = (left + right) / 2;
        if (nums[mid] > target)
        {
            return my_find(target, left, mid, nums);
        }
        else
        {
            return my_find(target, mid, right, nums);
        }
    }
}

void optimized_insert_sort(visualizer *vis)
{
    auto index = 0;
    for (int i = 1; i < vis->data_size; i++)
    {
        index = my_find(vis->data[i], 0, i, vis->data);
        for (int j = i; j > index; j--)
        {
            vis->visualize_swap(j, j - 1);
        }
    }
}