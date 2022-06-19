#ifndef MERGESORT
#define MERGESORT

#include "../dto.h"

// 比较次数
static int merge_sort_compare = 0;
// 赋值次数
static int merge_sort_assign = 0;

template <typename T>
void Merge(T *arr, int size)
{
    T temp[size];
    int b = 0;
    int mid = size / 2;
    int i = 0, j = mid;

    while (i < mid && j < size)
    {
        merge_sort_compare += 2;
        if (arr[i] <= arr[j])
        {
            merge_sort_compare++;
            temp[b++] = arr[i++];
            merge_sort_assign++;
        }
        else
        {
            merge_sort_compare++;
            temp[b++] = arr[j++];
            merge_sort_assign++;
        }
    }
    merge_sort_compare++;
    while (i < mid)
    {
        merge_sort_compare++;
        temp[b++] = arr[i++];
        merge_sort_assign++;
    }
    merge_sort_compare++;
    while (j < size)
    {
        merge_sort_compare++;
        temp[b++] = arr[j++];
        merge_sort_assign++;
    }
    merge_sort_compare++;
    for (int i = 0; i < size; i++)
    {
        merge_sort_compare++;
        arr[i] = temp[i];
        merge_sort_assign++;
    }
    merge_sort_compare++;
}

template <typename T>
void MergeSort_rec(T *arr, int size) //归并排序（递归版）
{
    if (size <= 1)
    {
        merge_sort_compare++;
        return;
    }
    if (size > 1)
    {
        merge_sort_compare++;
        MergeSort_rec(arr, size / 2);
        MergeSort_rec(arr + size / 2, size - size / 2);
        Merge(arr, size);
    }
}

template <typename T>
sort_result *merge_sort_rec_with_counter(T *data, int size)
{
    auto ret = new sort_result;
    ret->assign = ret->compare = merge_sort_assign = merge_sort_compare = 0;

    MergeSort_rec(data, size);

    ret->assign = merge_sort_assign;
    ret->compare = merge_sort_compare;
    return ret;
}

template <typename T>
sort_result *merge_sort_iter(T *arr, int size) //归并排序（迭代）
{
    auto ret = new sort_result;
    ret->assign = 0;
    ret->compare = 0;

    T *a = arr;
    T *b = new T[size];
    for (int seg = 1; seg < size; seg += seg)
    {
        ret->compare++;
        for (int start = 0; start < size; start += seg + seg)
        {
            ret->compare++;
            int left = start, mid = min(start + seg, size), right = min(start + seg + seg, size);
            int k = left;
            int left1 = left, right1 = mid;
            int left2 = mid, right2 = right;
            while (left1 < right1 && left2 < right2)
            {
                ret->compare += 2;
                b[k++] = a[left1] < a[left2] ? a[left1++] : a[left2++];
                ret->assign++;
            }
            ret->compare++;
            while (left1 < right1)
            {
                ret->compare++;
                b[k++] = a[left1++];
                ret->assign++;
            }
            ret->compare++;
            while (left2 < right2)
            {
                ret->compare++;
                b[k++] = a[left2++];
                ret->assign++;
            }
            ret->compare++;
        }
        ret->compare++;
        T *temp = a;
        a = b;
        b = temp;
        ret->assign += 3;
    }
    if (a != arr)
    {
        ret->compare++;
        for (int i = 0; i < size; i++)
        {
            ret->compare++;
            b[i] = a[i];
            ret->assign++;
        }
        ret->compare++;
        b = a;
    }
    delete[] b;

    return ret;
}

#endif
