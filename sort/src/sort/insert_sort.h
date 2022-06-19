#ifndef INSERT_SORT
#define INSERT_SORT

#include <iostream>

#include "../dto.h"

using namespace std;

auto compare_count = 0;

template <typename T>
int my_find(T target, int left, int right, T *nums)
{
    compare_count += 2;
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

template <typename T>
sort_result* optimized_insert_sort(T *data, int size)
{
    compare_count = 0;
    auto ret = new sort_result;
    ret->assign = 0;

    auto index = 0;
    for (int i = 1; i < size; i++)
    {
        index = my_find(data[i], 0, i, data);
        for (int j = i; j > index; j--)
        {
            swap(data[j], data[j - 1]);
            ret->assign += 3;
        }
    }
    
    ret->compare = compare_count;
    return ret;
}

template <typename T>
sort_result* insert_sort(T *data, int size)
{
    auto ret = new sort_result;
    ret->assign = 0;
    ret->compare = 0;

    auto index = 0;
    for (auto i = 1; i < size; i++)
    {
        for (auto j = i; j > 0; j--)
        {
            ret->compare++;
            if (data[j] < data[j - 1])
            {
                swap(data[j], data[j - 1]);
                ret->assign += 3;
            }
            else
            {
                break;
            }
        }
    }
    return ret;
}

#endif
