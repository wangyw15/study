// Sorts.h		三种（冒泡、选择、快速）基本排序算法（升序）
#ifndef SORTS_H
#define SORTS_H
#include <iostream>
using namespace std;

double gettime(int restart=0);

template <typename T> void GetMemory(T *&data, T *&data0, int n)	// 分配堆内存空间，通过参数"返回"首地址
{																	// 隐含约定：指针非空就表示指针"拥有"堆空间资源
    if(data0!=NULL) delete [] data0;								// 先释放原先所"拥有"的堆空间资源
    if(data !=NULL) delete [] data;
    data0 = new T[n];												// 重新申请新的（容量符合要求的）堆空间资源
    data = new T[n];
}

template <typename T> void FreeMemory(T *&data, T *&data0)			// 释放指针所"拥有"的堆空间资源
{
    if(data0!=NULL) delete [] data0;
    if(data !=NULL) delete [] data;
    data0 = data = NULL;											// 这一条赋值语句非常重要！保持"隐含约定"
}

template <typename T> void ReSet(T *data, const T *data0, int n)	// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
{
    for(int i=0; i<n; i++)
        data[i] = data0[i];
}

template <typename T> bool Check(const T *a, int size)				// 仅检验数组元素是否满足升序（并未进行严格的正确性检查）
{
    for(int i=1; i<size; i++)
        if(a[i-1] > a[i])
            return false;
    return true;
}

// 三种基本的（没有优化的）排序算法
template <typename T> void Bubble(T *a, int size)	// 冒泡排序
{
    T temp;		
    int times1=0,times2=0;									// 定义一个局部变量，数据类型与形式数据类型相同
    int i, j;
    for(i=1; i<size; i++)							// 共进行 size-1 轮比较和交换
    {
        for(j=0; j<size-i; j++)
        {
            times1++;
            if(a[j] > a[j+1])						// 相邻元素之间比较，必要时
            {
                times2+=3;
                temp = a[j];						// 交换 a[j] 与 a[j+1]
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
    /*cout << "冒泡排序一共循环了（数据间比较了）" << times1 << "次" << endl;
    cout << "一共交换了" << times2 << "次" << endl; */
}

template <typename T> void Select(T *a, int size)	// 选择排序
{
    T temp;
    int i, j, k=0;
    int times1=0,times2=0,times3=0;
    for(i=1; i<size; i++)							// 循环size-1次
    {
        for(j=i; j<size; j++)
        {
            times1++;
            if(a[j] < a[k])
            {
                times2++;
                k = j;	
            }
        }							// 找出当前范围内"最小"元素的下标
        if(k!=i-1)									// 若"最小"元素不是a[i-1]，则交换之
        {
            times3+=3;
            temp = a[k];
            a[k] = a[i-1];
            a[i-1] = temp;
        }
        k = i;
    }
    /*cout << "冒泡排序一共循环了（数据间比较了）" << times1 << "次" << endl;
    cout << "一共交换下标了" << times2 << "次" << endl; 
    cout << "一共交换数据了" << times3 << "次" << endl; */
}

template <typename T> void Qsort(T *a, int size)	// 快速排序
{
    T pivot, temp;
    int left=0, right=size-1;	
    int times1=0,times2=0;				// 下标（整数）

    if(size<=1)
    {
        return;
    }

    pivot = a[right];								// 选择最后一个值为分界值
    while(left < right)
    {
        while(left<right && a[left]<=pivot)
        {
            left++;	// 此处 "<=" 是让与分界值相等的元素暂时留在原地
            times1++;
        }
        while(left<right && a[right]>=pivot)
        {
            right--;// 此处 ">=" 是让与分界值相等的元素暂时留在原地
            times1++;
        }
        if(left < right)
        {
            times2+=3;
            temp=a[left];
            a[left]=a[right];
            a[right]=temp;
        }
    }
    a[size-1] = a[left]; 
    a[left] = pivot;			// 找到分界点 left
    Qsort(a, left);									// 递归调用(左侧部分)
    Qsort(a+left+1, size-left-1);					// 递归调用(右侧部分)
    /*cout << "快速排序共比较" << times1 << "次" << endl;
    cout << "共交换了" << times2;*/
}

#endif
