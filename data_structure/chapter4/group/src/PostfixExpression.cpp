// test data
// 3 4 + 5 * 6 -
// 3 5 2 - * 7 +

#include <iostream>
#include <stack>
#include <string>

using namespace std;

long long postfix_expression_cal(string str)
{
    stack<long long> s;
    int i = 0, num = 0;
    bool pushed = true;
    while (i <= str.size() - 1)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            num = num * 10 + str[i] - '0';
            pushed = false;
        }
        else
        {
            if (!pushed)
            {
                s.push(num);
                num = 0;
                pushed = true;
            }

            if (str[i] == '+')
            {
                long long a = s.top();
                s.pop();
                long long b = s.top();
                s.pop();
                s.push(a + b);
            }
            else if (str[i] == '-')
            {
                long long a = s.top();
                s.pop();
                long long b = s.top();
                s.pop();
                s.push(b - a);
            }
            else if (str[i] == '*')
            {
                long long a = s.top();
                s.pop();
                long long b = s.top();
                s.pop();
                s.push(a * b);
            }
            else if (str[i] == '/')
            {
                long long a = s.top();
                s.pop();
                long long b = s.top();
                s.pop();
                s.push(b / a);
            }
        }
        i++;
    }
    return s.top();
}

int main()
{
    string str;
    while (true)
    {
        cout << "输入后缀表达式（空行退出）: ";
        getline(cin, str);
        if (str != "")
        {
            cout << "计算结果: " << postfix_expression_cal(str) << endl << endl;
        }
        else
        {
            break;
        }
    }
    return 0;
}
