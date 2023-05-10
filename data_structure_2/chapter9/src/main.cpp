#include <iostream>

#include "defines.h"
#include "sorts/sorts.h"

using namespace std;

int main()
{
    shared_ptr<int[]> data(new int[5] {5, 4, 3, 2, 1});
    auto r = straight_insert_sort(data, 5);
    cout << r.comparisons << endl << r.swaps << endl;
    return 0;
}
