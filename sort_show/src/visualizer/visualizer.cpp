#include <iostream>
#include "visualizer.h"
#include "../util/util.h"

using namespace std;

/// <summary>
/// 默认构造函数
/// </summary>
visualizer::visualizer()
{
    data_size = 15;
    data = new int[data_size];
    init_data(data, data_size, 0);
}

/// <summary>
/// 构造函数
/// </summary>
/// <param name="size">数据大小</param>
visualizer::visualizer(int size)
{
    data_size = size;
    data = new int[data_size];
    init_data(data, data_size, 0);
}

/// <summary>
/// 交换数据
/// </summary>
/// <param name="index1">第一个索引</param>
/// <param name="index2">第二个索引</param>
void visualizer::visualize_swap(int index1, int index2)
{
    swap(data[index1], data[index2]);
    // 重绘画面
    clear_console();
    for (auto i = 0; i < data_size; i++)
    {
        if (data[i] < 10)
        {
            cout << 0;
        }
        cout << data[i] << " ";

        for (auto j = 0; j < data[i]; j++)
        {
            cout << "=";
        }
        cout << endl;
    }
    wait(1000); // 玄学
}

/// <summary>
/// 释放内存
/// </summary>
void visualizer::dispose()
{
    delete []data;
}