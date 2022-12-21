#include <iostream>

#include "Time/Time.h"
#include "Complex/Complex.h"

using namespace std;

int main()
{
    auto t = new Time(16, 59);
    // cin >> *t;
    cout << *t << endl;
    auto c = new Complex<int>(1, 2);
    cout << *c << endl;
    return 0;
}