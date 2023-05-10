#include <iostream>

#include "defines.h"
#include "sorts/sorts.h"

using namespace std;

int main()
{
    shared_ptr<int[]> data(new int[10] {10, 9, 8, 7, 6, 5, 4, 3, 2, 1});
    auto r = shell_sort(data, 10);
    for (size_t i = 0; i < 10; i++)
    {
        cout << data[i] << " ";
    }
    cout << endl;
    cout << r.comparisons << endl << r.swaps << endl;
    return 0;
}
