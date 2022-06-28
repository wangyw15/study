#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>
#include <chrono>
#include <thread>

/*
Box-Muller是产生随机数的一种方法。Box-Muller 算法隐含的原理非常深奥，但结果却是相当简单。
如果在(0,1]值域内有两个一致的随机数字u1和u2，则
可以使用以下两个式子中的任一个算出一个正态分布的随机数字z
z = r * cos(θ) 或 z = r * sin(θ)
其中 r = sqrt(-2 * ln(u2)), θ= 2 * π * u1
则z服从N(0, 1)，最后通过线性变换
x = m + (z * σ)服从N(m, σ^2)。
参见https://baike.baidu.com/item/box-muller/4023794?fr=aladdin
*/
double gauss_rand(double mean, double variance) // mena:均值、数学期望，variance方差
{
    static double u, v;
    static int phase = 0;
    double z;

    if (phase == 0)
    {
        u = (rand() + 1.0) / (RAND_MAX + 1.0); // 避免u或v为0时参与对数log计算
        v = (rand() + 1.0) / (RAND_MAX + 1.0);
        z = sqrt(-2.0 * log(u)) * sin(2.0 * M_PI * v);
    }
    else
    {
        z = sqrt(-2.0 * log(u)) * cos(2.0 * M_PI * v);
    }
    phase = 1 - phase;
    return mean + z * sqrt(variance);
}

// 利用rand()产生0~RAND_MAX之间的"均匀"分布的随机整数，进行简单的线性变换
double uniform_rand(double a, double b) // 区间[a, b]上的均匀分布
{
    return a + rand() * (b - a) / RAND_MAX; // 经过两点(0,a)和(RAND_MAX,b)的直线方程
}

// 生成数据
void init_data(int *data, int size, int flag)
{
    int i;
    switch (flag)
    {
    case 0:
        for (i = 0; i < size; i++)
        {
            data[i] = size - 1 - i;
        }
        break; // 逆序（从大到小）
    case 1:
        for (i = 0; i < size; i++)
        {
            data[i] = i;
        }
        break; // 顺序（从小到大）
    case 2:
        for (i = 0; i < size; i++)
        {
            data[i] = uniform_rand(54, 90);
        }
        break; // [54,90]上的均匀分布
    case 3:
        for (i = 0; i < size; i++)
        {
            data[i] = gauss_rand(72, 6 * 6);
        }
        break; // 正态分布，均值72，方差36（根方差6）
    }
}

// 等待一段时间（毫秒）
void wait(long ms)
{
    std::chrono::milliseconds sleep_time(ms);
    std::this_thread::sleep_for(sleep_time);
}

void clear_console()
{
    #ifdef __linux__
    system("clear");
    #else
    system("cls");
    #endif
}