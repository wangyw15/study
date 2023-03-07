// 引用必要的头文件
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

// 引用命名空间，避免之后使用std::
using namespace std;

/// <summary>
/// 判断字符是否为小写字母
/// </summary>
/// <param name="c">要判断的字符</param>
/// <returns>布尔型，是否为小写字母</returns>
bool isLowerLetter(char c)
{
    return (c >= 'a' && c <= 'z');
}

/// <summary>
/// 判断字符是否为数字
/// </summary>
/// <param name="c">要判断的字符</param>
/// <returns>布尔型，是否为数字</returns>
bool isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

/// <summary>
/// 将字符转换为大写字母
/// </summary>
/// <param name="c">要转换的字符</param>
/// <returns>转换后的大写字符</returns>
char toUpper(char c)
{
    if (c >= 'A' && c <= 'Z') // 如果已经是大写字符则直接返回本身
        return c;
    return c - 'a' + 'A'; // 转换为大写字符
}

/// <summary>
/// 展开字符串
/// </summary>
/// <param name="p1">p1</param>
/// <param name="p2">p2</param>
/// <param name="p3">p3</param>
/// <param name="start">分隔符前一个字符</param>
/// <param name="end">分隔符后一个字符</param>
/// <returns>展开后的字符串</returns>
string expand(int p1, int p2, int p3, char start, char end)
{
    string ret = "-"; // 展开后的字符串
    bool allLetter = isLowerLetter(start) && isLowerLetter(end); // 判断是否都为字母
    bool allDigit = isDigit(start) && isDigit(end); // 判断是否都为数字
    if ((allLetter || allDigit) && start < end)
    {
        ret = ""; // 需要展开则将字符串置空
        for (char c = start + 1; c < end; c++) // 一直从开始字符的后一个展开到结束字符的前一个
        {
            for (int i = 0; i < p2; i++) // 重复输出字符以满足p2
            {
                // p1为3时则展开为*
                if (p1 == 3)
                {
                    ret += '*';
                }
                else
                {
                    if (allLetter) // 当两边都为字母时
                    {
                        // p1 = 1时填充小写字母
                        if (p1 == 1)
                        {
                            ret += c;
                        }
                        // p1 = 2时填充小写字母
                        else if (p1 == 2)
                        {
                            ret += toUpper(c);
                        }
                    }
                    else  // 当两边都为数字时
                    {
                        ret += c;
                    }
                }
            }
        }
        if (p3 - 1) // 当if内不为0时则都为true，因此p3 = 2时就反转字符串
        {
            reverse(ret.begin(), ret.end());
        }
    }
    return ret;
}

/// <summary>
/// 程序的主函数
/// </summary>
/// <returns>程序的返回值</returns>
int main()
{
    int p1, p2, p3;
    while (cin >> p1 >> p2 >> p3) // 实际的输入是2n，不止是示例中的两行
    {
        // 回车后缓冲区内还存在着\n这个换行符，需要忽略掉才能读到真正的一行输入
        cin.ignore(1, '\n');

        // 读取一行字符串
        string line;
        getline(cin, line);

        for (int i = 0; i < line.length(); i++)
        {
            char current = line[i]; // 对每一个字符进行判断
            // 如果不是分隔符，则输出本身
            if (current != '-')
            {
                cout << current;
            }
            else
            {
                if ((i - 1) >= 0 && (i + 1) < line.length()) // 判断分隔符是否在字符串的开头和结尾
                    cout << expand(p1, p2, p3, line[i - 1], line[i + 1]); // 展开字符串
                else
                    cout << '-'; // 在开头和结尾则输出分隔符本身
            }
        }
        cout << endl;
    }
}