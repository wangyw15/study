/*
对于一个1000x1000的稀疏矩阵，其中1%的元素为非零元素，可以使用散列表作为存储结构。散列表是一种以键-值对(key-value)形式存储数据的数据结构，它通过哈希函数将键映射到表中的一个位置来访问记录，以加快查找速度。
对于给定的行值和列值，可以将它们组合成一个字符串，例如"row,column"，然后使用哈希函数将其映射到散列表中的一个位置。这样，就可以快速确定矩阵元素在散列表上的位置。
与在稀疏矩阵的三元组表存储结构上存取元素的算法相比，使用散列表存储结构的时间复杂度通常更低。在三元组表存储结构中，查找一个元素需要遍历整个表，时间复杂度为O(n)，其中n为非零元素个数。而在散列表中，查找一个元素只需要计算其哈希值并访问相应位置，时间复杂度接近O(1)。
当然，这只是理论上的时间复杂度比较。实际应用中，散列表的性能还受到许多因素影响，如哈希函数的选择、冲突解决方案等。
*/

#include <iostream>
#include <random>
#include "headers/HashMatrix.hpp"

using namespace std;

int main()
{
    const int CAPACITY = 1000 * 1000 / 100;
    
    // generate numbers
    random_device device;
    mt19937 engine(device());
    uniform_int_distribution<> dis(0, 10000);
    int nums[CAPACITY];
    HashMatrix hashMatrix(CAPACITY);
    for (int i = 0; i < CAPACITY; i++)
    {
        nums[i] = dis(engine);
        hashMatrix.Insert(i / 100, i % 100, nums[i]);
    }
    hashMatrix.Traverse([](MatrixNode node) -> void
        { 
            cout << node.X << ", " << node.Y << ": " << node.Data << endl;
        });
    return 0;
}