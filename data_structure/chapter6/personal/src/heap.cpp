#include <iostream>
#include <memory>

#include "headers/MinHeap.hpp"

using namespace std;

int main()
{
    shared_ptr<int[]> arr(new int[10]{80, 57, 99, 35, 23, 11, 74, 29, 62, 16});
    MinHeap<int> min(arr, 10);
    cout << min << endl;
    
    return 0;
}