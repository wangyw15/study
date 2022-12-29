#ifndef KMP
#define KMP

#include <algorithm>
#include <iostream>
#include <string>

/**
 * @brief �޸Ĺ���KMPʧЧ�������㣬�ο� https://www.cnblogs.com/cherryljr/p/6519748.html
 * @param pat ģʽ��
 * @param f ���ص�ʧЧ����
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
 * @brief KMP����
 * @param str ԭ��
 * @param pat ģʽ��
 * @param compare �����㷨�еĲ��Ҵ���
 * @param p ���ҵ���ʼλ��
 * @return ģʽ����ԭ���е�λ��
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
