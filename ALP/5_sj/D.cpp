// ���ñ�Ҫ��ͷ�ļ�
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

// ���������ռ䣬����֮��ʹ��std::
using namespace std;

/// <summary>
/// �ж��ַ��Ƿ�ΪСд��ĸ
/// </summary>
/// <param name="c">Ҫ�жϵ��ַ�</param>
/// <returns>�����ͣ��Ƿ�ΪСд��ĸ</returns>
bool isLowerLetter(char c)
{
    return (c >= 'a' && c <= 'z');
}

/// <summary>
/// �ж��ַ��Ƿ�Ϊ����
/// </summary>
/// <param name="c">Ҫ�жϵ��ַ�</param>
/// <returns>�����ͣ��Ƿ�Ϊ����</returns>
bool isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

/// <summary>
/// ���ַ�ת��Ϊ��д��ĸ
/// </summary>
/// <param name="c">Ҫת�����ַ�</param>
/// <returns>ת����Ĵ�д�ַ�</returns>
char toUpper(char c)
{
    if (c >= 'A' && c <= 'Z') // ����Ѿ��Ǵ�д�ַ���ֱ�ӷ��ر���
        return c;
    return c - 'a' + 'A'; // ת��Ϊ��д�ַ�
}

/// <summary>
/// չ���ַ���
/// </summary>
/// <param name="p1">p1</param>
/// <param name="p2">p2</param>
/// <param name="p3">p3</param>
/// <param name="start">�ָ���ǰһ���ַ�</param>
/// <param name="end">�ָ�����һ���ַ�</param>
/// <returns>չ������ַ���</returns>
string expand(int p1, int p2, int p3, char start, char end)
{
    string ret = "-"; // չ������ַ���
    bool allLetter = isLowerLetter(start) && isLowerLetter(end); // �ж��Ƿ�Ϊ��ĸ
    bool allDigit = isDigit(start) && isDigit(end); // �ж��Ƿ�Ϊ����
    if ((allLetter || allDigit) && start < end)
    {
        ret = ""; // ��Ҫչ�����ַ����ÿ�
        for (char c = start + 1; c < end; c++) // һֱ�ӿ�ʼ�ַ��ĺ�һ��չ���������ַ���ǰһ��
        {
            for (int i = 0; i < p2; i++) // �ظ�����ַ�������p2
            {
                // p1Ϊ3ʱ��չ��Ϊ*
                if (p1 == 3)
                {
                    ret += '*';
                }
                else
                {
                    if (allLetter) // �����߶�Ϊ��ĸʱ
                    {
                        // p1 = 1ʱ���Сд��ĸ
                        if (p1 == 1)
                        {
                            ret += c;
                        }
                        // p1 = 2ʱ���Сд��ĸ
                        else if (p1 == 2)
                        {
                            ret += toUpper(c);
                        }
                    }
                    else  // �����߶�Ϊ����ʱ
                    {
                        ret += c;
                    }
                }
            }
        }
        if (p3 - 1) // ��if�ڲ�Ϊ0ʱ��Ϊtrue�����p3 = 2ʱ�ͷ�ת�ַ���
        {
            reverse(ret.begin(), ret.end());
        }
    }
    return ret;
}

/// <summary>
/// �����������
/// </summary>
/// <returns>����ķ���ֵ</returns>
int main()
{
    int p1, p2, p3;
    while (cin >> p1 >> p2 >> p3) // ʵ�ʵ�������2n����ֹ��ʾ���е�����
    {
        // �س��󻺳����ڻ�������\n������з�����Ҫ���Ե����ܶ���������һ������
        cin.ignore(1, '\n');

        // ��ȡһ���ַ���
        string line;
        getline(cin, line);

        for (int i = 0; i < line.length(); i++)
        {
            char current = line[i]; // ��ÿһ���ַ������ж�
            // ������Ƿָ��������������
            if (current != '-')
            {
                cout << current;
            }
            else
            {
                if ((i - 1) >= 0 && (i + 1) < line.length()) // �жϷָ����Ƿ����ַ����Ŀ�ͷ�ͽ�β
                    cout << expand(p1, p2, p3, line[i - 1], line[i + 1]); // չ���ַ���
                else
                    cout << '-'; // �ڿ�ͷ�ͽ�β������ָ�������
            }
        }
        cout << endl;
    }
}