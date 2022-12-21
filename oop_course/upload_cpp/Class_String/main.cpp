#include <bits/stdc++.h>

#include "String.h"

char lower(char c)
{
    if ('a' <= c && c <= 'z')
    {
        return c;
    }
    if ('A' <= c && c <= 'Z')
    {
        return c - 'A' + 'a';
    }
    else {
        return c;
    }
}

int main()
{
    String str1("SHU");
    String *inLeap = new String("welcome");
    String str2(str1);
    str2 = "上海大学";
    str2 += "Welcome You";
    for (auto i = 0; i < str2.Length(); i++)
    {
        str2[i] = lower(str2[i]);
    }
    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;
    return 0;
}