#include <iostream>

#include "Vector/Vector.h"

using namespace std;

int main()
{
    int *arr = new int[3]{1, 2, 3};
    Vector<int> v(arr, 3);
    delete [] arr;
    for (int i = 0; i < v.Size(); i++)
    {
        cout << v[i] << endl;
    }
}