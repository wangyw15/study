#ifndef KMP
#define KMP

#include <algorithm>
#include <iostream>
#include <string>

/**
 * @brief 修改过的KMP失效函数计算，参考 https://www.cnblogs.com/cherryljr/p/6519748.html
 * @param pat 模式串
 * @param f 返回的失效函数
 **/
void GetFailure(const std::string &pat, int f[])
{
    int j = 0, k = -1;
    f[0] = -1;
    while (j < pat.length() - 1)
    {
        if (k == -1 || pat[k] == pat[j])
        {
            j++;
            k++;
            if (pat[j] == pat[k])
            {
                f[j] = f[k];
            }
            else
            {
                f[j] = k;
            }
        }
        else
        {
            k = f[k];
        }
    }
}

/**
 * @brief KMP查找
 * @param str 原串
 * @param pat 模式串
 * @param compare 返回算法中的查找次数
 * @param p 查找的起始位置
 * @return 模式串在原串中的位置
 **/
int KMPFind(const std::string &pat, const std::string &str, int &compare, int p = 0)
{
    compare = 0;

    int *f = new int[pat.length()];
    GetFailure(pat, f);
    int i = p, j = 0;
    while (i < str.length() && j < (long)pat.length() && pat.length() - j <= str.length() - i)
    {
        if (j == -1 || pat[j] == str[i])
        {
            i++;
            j++;
        }
        else
        {
            j = f[j];
        }
        compare++;
    }
    delete[] f;
    if (j < pat.length())
    {
        return -1;
    }
    else
    {
        return i - j;
    }
}

#endif
