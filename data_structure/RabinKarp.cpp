#include <string>
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;

/**
 * @brief string字符串的位置i元素对应的散列值（数字表不包含0）
 * @param str 字符串
 * @param i   要转换的位置
 * @param R   range
 * @return 位置i元素对应的散列值
 **/
int Digit(string str, int i, int R)
{
    // return 256;
    if (R == 10)
    {
        return str[i] - '0';  // 十进制数
    }
    else if (R == 26)
    {
        if (str[i] >= 65 && str[i] <= 90)
        {
            return str[i] - 'A';  // 26位字母大写
        }
        else
        {
            return str[i] - 'a';  // 26位字母小写
        }
    }
    throw range_error("Invalid R value");
}

/**
 * @brief RabinKarp查找算法
 * @param pattern 模式串
 * @param source 原串
 * @param R range
 * @return 模式串在原串中的位置（-1为未找到）
 **/
int RabinKarp(string pattern, string source, int R)
{
    // 以下情况不可能匹配：模式串长度比原串长、两串长度相同但是第一个字符就不同，提前判断一部分情况以提高效率
    if (pattern.size() > source.size() || (pattern.size() == source.size() && pattern[0] != source[0]))
    {
        return -1;
    }

    long long pHash = 0, sHash = 0;
    for (int i = 0; i < pattern.size(); i++)
    {
        pHash = pHash * R + Digit(pattern, i, R);
        sHash = sHash * R + Digit(source, i, R);
    }

    for (int i = 0; i <= source.size() - pattern.size(); i++)
    {
        if (pHash == sHash)
        {
            return i;
        }
        else
        {
            sHash = sHash % (long long)(pow(R, pattern.size() - 1)) * R + Digit(source, i + pattern.size(), R);
        }
    }
    return -1;
}

typedef long long numeric;
#define BASE 256
#define MODULUS 101

/**
 * @brief 修改过的RabinKarp查找算法，参考 https://zhuanlan.zhihu.com/p/563551141
 * @param pattern 模式串
 * @param source 原串
 * @return 模式串在原串中的位置（-1为未找到）
 **/
int RefinedRabinKarp(string pattern, string source)
{
    // 以下情况不可能匹配：模式串长度比原串长、两串长度相同但是第一个字符就不同，提前判断一部分情况以提高效率
    if (pattern.size() > source.size() || (pattern.size() == source.size() && pattern[0] != source[0]))
    {
        return -1;
    }

    int h = 1;
    for (int i = 0; i < pattern.length() - 1; i++)
    {
        h = (h * BASE) % MODULUS;
    }

    int pHash = 0, sHash = 0;
    for (int i = 0; i < pattern.length(); i++)
    {
        sHash = (BASE * sHash + source[i]) % MODULUS;
        pHash = (BASE * pHash + pattern[i]) % MODULUS;
    }

    int i = 0;
    while (i <= source.length() - pattern.length())
    {
        if (sHash == pHash)
        {
            return i;
        }
        sHash = (BASE * (sHash - source[i] * h) + source[i + pattern.length()]) % MODULUS;
        if (sHash < 0)
        {
            sHash += MODULUS;
        }
        i++;
    }
    return -1;
}

int main()
{
    string T1 = "AKJKDJKASJDKK";
    string P1 = "JKA";
    cout << RabinKarp(P1, T1, 26) << endl;
    cout << RefinedRabinKarp(P1, T1) << endl;

    string T2 = "asjdhjkahdjk";
    string P2 = "hjk";
    cout << RabinKarp(P2, T2, 26) << endl;
    cout << RefinedRabinKarp(P2, T2) << endl;

    string T3 = "10829238740230";
    string P3 = "023";
    cout << RabinKarp(P3, T3, 10) << endl;
    cout << RefinedRabinKarp(P3, T3) << endl;

    string T4 = "10829238740230";
    string P4 = "021";
    cout << RabinKarp(P4, T4, 10) << endl;
    cout << RefinedRabinKarp(P4, T4) << endl;

    string T5 = "qw378hf6nADIOU45t";
    string P5 = "6nA";
    cout << RefinedRabinKarp(P5, T5) << endl;

    return 0;
}
