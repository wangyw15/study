// Score.cpp

#include <iostream>
#include <cstdio>
#include <typeinfo>

#include "score.h"
#include "../rand/rand.h"
using namespace std;

void init_score(score *data, int n)
{
    double mean = 72, variance = 6 * 6;
    for (int i = 0; i < n; i++)
    {
        // 原始数据中，学号是完全顺序排列的！
        sprintf(data[i].id, "%08d", i + 1);
        // 加0.5后取整即小数部分"四舍五入"
        data[i].Total = data[i].Chinese = int(0.5 + gauss_rand(mean, variance));
        data[i].Total += data[i].Math = int(0.5 + gauss_rand(mean, variance));
        data[i].Total += data[i].English = int(0.5 + gauss_rand(mean, variance));
        data[i].Total += data[i].Physics = int(0.5 + gauss_rand(mean, variance));
        data[i].Total += data[i].Chemistry = int(0.5 + gauss_rand(mean, variance));
    }
}
