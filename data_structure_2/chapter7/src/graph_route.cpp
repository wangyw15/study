#include <iostream>
#include "headers/AdjMatrixUndirGraph.hpp"

using namespace std;

int main()
{
    char vertexes[] = {'A', 'B', 'C', 'D'};
    auto matrix = AdjMatrixUndirGraph<char, int>(vertexes, 4);
    matrix.InsertArc('A', 'C');
    matrix.InsertArc('A', 'D');
    matrix.InsertArc('B', 'C');
    matrix.InsertArc('B', 'D');
    matrix.DFSTraverse('A', [](char c) -> void { cout << c << endl; });
    return 0;
}