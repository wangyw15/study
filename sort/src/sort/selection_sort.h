#ifndef SELECTION_SORT
#define SELECTION_SORT

#include <iostream>
#include "../dto.h"

using namespace std;

template <typename T>
sort_result* selection_sort(T *data, int size)
{
    auto ret = new sort_result;
    auto min = 0;
    ret->assign = 0;
    ret->compare = 0;
    for (auto i = 0; i < size; i++)
    {
        min = i;
        for (auto j = i; j < size; j++)
        {
            ret->compare++;
            if (data[j] < data[min])
            {
                min = j;
            }
        }
        swap(data[i], data[min]);
        ret->assign += 3;
    }
    return ret;
}

#endif