#include <iostream>
#include <stdio.h>

using namespace std;

double f(double x)
{
    if (0 <= x && x < 5)
        return 0 - x + 2.5;
    else if (5 <= x && x < 10)
        return 2 - 1.5 * (x - 3) * (x - 3);
    else if (10 <= x && x < 20)
        return x / 2 - 1.5;
}

int main()
{
    double num;
    while (cin >> num)
        printf("%.3f\n", f(num));
    return 0;
}