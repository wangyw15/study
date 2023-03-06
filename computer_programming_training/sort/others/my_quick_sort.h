#ifndef QUICK_SORT
#define QUICK_SORT

#include <iostream>
#include "../dto.h"

// 比较次数
static unsigned long long quick_sort_compare = 0;
// 赋值次数
static unsigned long long quick_sort_assign = 0;

// 快速排序
template <typename T>
void quick_sort(T *a, int size)
{
    T pivot, temp;
    int left = 0, right = size - 1;

    if (size <= 1)
    {
        return;
    }

    pivot = a[right]; // 选择最后一个值为分界值
    while (left < right)
    {
        while (left < right && a[left] <= pivot)
        {
            left++; // 此处 "<=" 是让与分界值相等的元素暂时留在原地
            quick_sort_compare += 2;
        }
        while (left < right && a[right] >= pivot)
        {
            right--; // 此处 ">=" 是让与分界值相等的元素暂时留在原地
            quick_sort_compare += 2;
        }
        if (left < right)
        {
            quick_sort_assign += 3;
            swap(a[left], a[right]);
            /*temp = a[left];
            a[left] = a[right];
            a[right] = temp;*/
        }
        quick_sort_compare++;
    }
    a[size - 1] = a[left];
    quick_sort_assign++;
    a[left] = pivot;                           // 找到分界点 left
    quick_sort(a, left);                       // 递归调用(左侧部分)
    quick_sort(a + left + 1, size - left - 1); // 递归调用(右侧部分)
}

template <typename T>
sort_result *quick_sort_with_counter(T *data, int size)
{
    auto ret = new sort_result;
    ret->assign = ret->compare = quick_sort_assign = quick_sort_compare = 0;

    quick_sort(data, size);

    ret->assign = quick_sort_assign;
    ret->compare = quick_sort_compare;
    return ret;
}

#endif