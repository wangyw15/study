#include <iostream>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

unsigned long long factorial(int n)
{
    unsigned long long result = 1;
    for(int i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

unsigned long long combination(int n, int m)
{
    return factorial(n) / factorial(m) / factorial(n - m);
}

int main()
{
    int n, index = 1;
    while(cin >> n)
    {
        cout << "Case " << index++ << ":\n";
        cout << "1" << endl;
        for(int i = 1; i <= n; i++)
        {
            for(int j = 0; j <= i; j++)
            {
                cout << combination(i, j);
                if(j != i) cout << " ";
            }
            cout << endl;
        }
    }
    return 0;
}