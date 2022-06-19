#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int n, index = 1;
    while (cin >> n)
    {
        cout << "Case " << index++ << ":" << endl;
        if (n == 1)
        {
            cout << 1 << endl;
            continue;
        }
        vector<vector<int>> matrix(n, vector<int>(n));
        for (int i = 0; i < n / 2; i++)
        {
            for (int j = i; j < n - i; j++)
            {
                for (int k = i; k < n - i; k++)
                {
                    if (j == i || k == i || j == n - 1 - i || k == n - 1 - i)
                        matrix[j][k] = i + 1;
                }
            }
        }
        if (n % 2 == 1)
            matrix[n / 2][n / 2] = n / 2 + 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << matrix[i][j];
                if (j != n - 1)
                    cout << " ";
            }
            cout << endl;
        }
    }
    return 0;
}