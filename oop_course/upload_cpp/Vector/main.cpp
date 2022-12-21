#include<bits/stdc++.h>
#include"vector.h"
using namespace std;

int main()
{
    auto arr1 = new double[7]{5,6,7,8,9,10,11};
    auto arr2 = new double[5]{15,16,17,18,19};
    Vector v1(arr1, 7), v2(arr2, 5), v3 = v1;

    v1.Remove(6);
    v1.Remove(5);

    auto arr4 = new double[5];
    for (auto i = 0; i < 5; i++)
    {
        arr4[i] = 2 * v1[i] + 3 * v2[i];
    }
    Vector v4 = v1 + v1 + v2 + v2 + v2;
    Vector v5(new double[4]{2,4,6,8}, 4);
    v1.Show();
    v2.Show();
    v3.Show();
    v4.Show();
    v5.Show();
    return 0;
}
