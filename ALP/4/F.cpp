#include <iostream>
#include <vector>

using namespace std;

int getLocation(int n, int location)
{
    if (0 <= location && location < n)
        return location;
    else if (location >= n)
        return location - n;
    else
        return n + location;
}

int main()
{
    int index = 1, n;

    while (cin >> n)
    {
        vector<vector<int>> matrix(n, vector<int>(n));
        int x = 0, y = n / 2;
        matrix[x][y] = 1;
        for (int i = 2; i <= n * n; i++)
        {
            if (i % n == 1)
            {
                x = getLocation(n, x + 1);
            }
            else
            {
                x = getLocation(n, x - 1);
                y = getLocation(n, y + 1);
            }
            matrix[x][y] = i;
        }

        cout << "Case " << index++ << ":" << endl;
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