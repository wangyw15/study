#ifndef QUICK_SORT
#define QUICK_SORT

#include "../dto.h"

// 比较次数
static unsigned long long quick_sort_compare = 0;
// 赋值次数
static unsigned long long quick_sort_assign = 0;

// n计赋值
// m计比较

template <typename T>
int parttion(T *a, int start, int end)
{
    T tmp = a[start];
    quick_sort_assign++;
    while (start < end)
    {
        while (start < end && a[end] >= tmp)
        {
            quick_sort_compare++;
            end--;
        }
        quick_sort_compare++;
        if (start >= end)
        {
            break;
        }
        else
        {
            a[start] = a[end];
            quick_sort_assign++;
        }
        while (start < end && a[start] <= tmp)
        {
            quick_sort_compare++;
            start++;
        }

        quick_sort_compare++;
        if (start > end)
        {

            break;
        }
        else
        {
            a[end] = a[start];
            quick_sort_assign++;
        }
    }
    a[start] = tmp;
    quick_sort_assign++;
    return start;
}

template <typename T>
void swap(T *a, int low, int high)
{
    T tmp = a[low];
    a[low] = a[high];
    a[high] = tmp;
    quick_sort_assign += 3;
}

template <typename T>
void mid(T *a, int low, int high)
{
    quick_sort_compare += 3;
    int mid = (low + high) / 2;
    if (a[low] >= a[high])
    {
        swap(a, low, high);
    }
    if (a[low] <= a[mid])
    {
        swap(a, low, mid);
    }
    if (a[mid] >= a[high])
    {
        swap(a, low, mid);
    }
}

template <typename T>
void insertsort2(T *a, int low, int high)
{
    for (int i = low + 1; i <= high; i++)
    {
        T tmp = a[i];
        quick_sort_assign++;
        int j = i - 1;
        for (; j >= low; j--)
        {
            quick_sort_compare++;
            if (a[j] > tmp)
            {
                a[j + 1] = a[j];
                quick_sort_assign++;
            }
            else
            {
                break;
            }
        }
        a[j + 1] = tmp;
        quick_sort_assign++;
    }
}

template <typename T>
void quick(T *a, int low, int high)
{
    if (low > high)
    {
        return;
    }
    quick_sort_compare++;
    //第一个优化：当low,high之间的数据个数少于某一个范围，可以调用直接插入排序
    if (high - low + 1 < 100)
    {
        insertsort2(a, low, high);
        return;
    }
    quick_sort_compare++;
    //第二次优化，取三个数中位数,这样的基准就不会出现极端情况
    mid(a, low, high);
    int par = parttion(a, low, high);
    quick(a, low, par - 1);
    quick(a, par + 1, high);
}

// 快速排序
template <typename T>
void optimized_quick_sort(T *a, int size)
{
    quick(a, 0, size - 1);
}

template <typename T>
sort_result *optimized_quick_sort_with_counter(T *data, int size)
{
    auto ret = new sort_result;
    ret->assign = ret->compare = quick_sort_assign = quick_sort_compare = 0;

    optimized_quick_sort(data, size);

    ret->assign = quick_sort_assign;
    ret->compare = quick_sort_compare;
    return ret;
}

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