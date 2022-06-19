#include <iostream>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int char2int(char c)
{
    return c == '*' ? 1 : 0;
}

bool inRange(int num, int upper)
{
    return num < upper && num >= 0;
}

int main()
{
    int m, n;
    cin >> m >> n;

    char matrix[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> matrix[i][j];
        }
    }

    char result[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            char current = matrix[i][j];
            if (current == '*')
            {
                cout << '*';
            }
            else
            {
                int total = 0;
                for (int a = -1; a <= 1; a++)
                {
                    for (int b = -1; b <= 1; b++)
                    {
                        if (a != 0 || b != 0)
                        {
                            if (inRange(i + a, m) && inRange(j + b, n))
                                total += char2int(matrix[i + a][j + b]);
                        }
                    }
                }
                cout << total;
            }
        }
        cout << endl;
    }

    return 0;
}