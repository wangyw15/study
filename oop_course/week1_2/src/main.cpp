#include <iostream>

#include "my_swap/my_swap.h"
#include "solve/solve.h"

using namespace std;

void test_solve()
{
    double a[][3] = { { 1, 2, -3 }, { 1, 2, 1 }, { 1, 2, 3 } };
    int size = sizeof(a) / sizeof(*a);
    for (int i = 0; i < size; i++)
    {
        double x1, x2;
        solve(a[i][0], a[i][1], a[i][2], x1, x2);
        cout << a[i][0] << "x^2+" << a[i][1] << "x+" << a[i][2] << "=0" << endl;
        cout << "x1=" << x1 << " x2=" << x2 << endl;
    }
}

void test_swap()
{
    int x = 3, y = 5;
    cout << x << " " << y << endl;
    my_swap(x, y);
    cout << x << " " << y << endl;

    char array1[20] = "Tom", array2[20] = "Jerry";
    cout << array1 << " " << array2 << endl;
    my_swap(array1, array2);
    cout << array1 << " " << array2 << endl;

    char *pa1 = &(array1[0]), *pa2 = &(array2[0]);
    cout << pa1 << " " << pa2 << endl;
    my_swap(pa1, pa2);
    cout << pa1 << " " << pa2 << endl;

    const char *p1 = "Snoopy", *p2 = "Winnie";
    cout << p1 << " " << p2 << endl;
    my_swap(p1, p2);
    cout << p1 << " " << p2 << endl;
}

int main()
{
    test_solve();
    test_swap();
    return 0;
}