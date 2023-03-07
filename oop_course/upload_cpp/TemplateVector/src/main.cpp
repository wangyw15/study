#include<bits/stdc++.h>
#include <iostream>
#include "Vector_template.h"

using namespace std;

int main()
{
    Vector<double> v1(new double[3]{10, 20, 30}, 3), v2(new double[3]{2.5, 5, 7.5}, 3);
    auto v3 = new Vector<double>(new double[3]{1.5, 2.5, 4.5}, 3);
    Vector<char> v4("China", 6);
    cout << v1 << endl;
    cout << v2 << endl;
    cout << v3 <<endl;
    cout << v4 << endl;
    return 0;
}
