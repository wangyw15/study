#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

const string CHARS[] = {"□", "■"}; // 要输出的字符

int main()
{
    int index = 1;
    int num, i = 0;
    while (cin >> hex >> num)
    {
        if (i == 0)
            cout << "Case " << index++ << ":" << endl; // 只在点阵字输出之前输出这一行

        vector<int> numMatrix; // 存放十六进制转换之后的二进制数

        // 短除法转二进制
        int a = num;
        while (a > 0)
        {
            numMatrix.push_back(a % 2);
            a /= 2;
        }
        reverse(numMatrix.begin(), numMatrix.end());

        // 补全空位
        for (int j = 0; j < 8 - numMatrix.size(); j++)
            cout << CHARS[0];

        // 输出点阵字
        for(int j = 0; j < numMatrix.size(); j++)
            cout << CHARS[numMatrix[j]];

        // 每16个字符换行
        if (i % 2 == 1)
            cout << endl;

        // 计数器
        if (i++ == 31)
            i = 0;
    }
    return 0;
}