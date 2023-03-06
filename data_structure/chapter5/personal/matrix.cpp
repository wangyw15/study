#include <algorithm>
#include <string>
#include <iostream>

#include "headers/Matrix.hpp"

using namespace std;

int main()
{
    int shape = 3;
    TriSparseMatrix<int> matrix1(shape, shape), matrix2(shape, shape);
    for (auto row = 0; row < shape; row++)
    {
        for (auto col = 0; col < shape; col++)
        {
            matrix1.Set(row, col, row * shape + col);
            // matrix2.Set(row, col, (row * shape + col) * (row * shape + col));
        }
        matrix2.Set(row, 0, (row * shape + 0) * (row * shape + 0));
    }
    cout << "matrix1" << endl << matrix1 << endl << endl;
    cout << "matrix2" << endl << matrix2 << endl << endl;
    matrix1.Transpose();
    matrix2.Transpose();
    cout << "transposed matrix1" << endl << matrix1 << endl << endl;
    cout << "transposed matrix2" << endl << matrix2 << endl << endl;
    cout << "transposed matrix1 + transposed matrix2" << endl << matrix1 + matrix2 << endl << endl;
    return 0;
}