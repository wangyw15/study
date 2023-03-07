#include <iostream>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

/*unsigned long long combination(long m, long n)
{
    unsigned long long result = 1;
    if (n < m - n)
    {
        n = m - n;
    }
    for (long i = n + 1; i <= m; i++)
        result *= i;
    for (long i = 2; i <= m - n; i++)
        result /= i;
    return result;
}*/

unsigned long long combination(long m, long n)
{
    if (n > m)
        return 0;
    else if (n == m || n == 0)
        return 1;
    else
        return combination(m - 1, n) + combination(m - 1, n - 1);
}

int main()
{
    int n, m, index = 1;
    while (cin >> m >> n)
    {
        unsigned long long result = 0;
        if (n == m)
            result = 1;
        else if (m > n)
        {
            result = combination(m, n);
        }
        cout << "Case " << index++ << ":" << endl << result << endl;
    }
    return 0;
}