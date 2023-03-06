#ifndef BUBBLE_SORT
#define BUBBLE_SORT

#include <iostream>
#include "../dto.h"

using namespace std;

template <typename T>
sort_result* bubble_sort(T *data, int size)
{
    auto ret = new sort_result;
    ret->assign = 0;
    ret->compare = 0;
    for (auto i = 0; i < size - 1; i++)
    {
        for (auto j = 0; j < size - 1 - i; j++)
        {
            ret->compare++;
            if (data[j] > data[j + 1])
            {
                swap(data[j], data[j + 1]);
                ret->assign += 3;
            }
        }
    }
    return ret;
}

template <typename T>
sort_result* optimized_bubble_sort(T *data, int size)
{
    auto ret = new sort_result;
    ret->assign = 0;
    ret->compare = 0;
    
    auto flag = true;
    for (auto i = 0; i < size - 1 && flag; i++)
    {
        flag = false;
        for (auto j = 0; j < size - 1 - i; j++)
        {
            ret->compare++;
            if (data[j] > data[j + 1])
            {
                swap(data[j], data[j + 1]);
                ret->assign += 3;
                flag = true;
            }
        }
    }
    return ret;
}

#endif