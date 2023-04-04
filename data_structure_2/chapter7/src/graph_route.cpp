#include <iostream>
#include <string>

#include "headers/AdjMatrixUndirGraph.hpp"

using namespace std;

int main()
{
    string vertexes[] = {"A", "B", "C", "D"};
    AdjMatrixUndirGraph<string, int> matrix(vertexes, 4);
    matrix.InsertArc("A", "C");
    matrix.InsertArc("A", "D");
    matrix.InsertArc("B", "C");
    matrix.InsertArc("B", "D");
    
    cout << (matrix.ExistRoute("C", "D") ? "true" : "false") << endl;
    
    string routes = matrix.GetAllRoutes("A", "D");
    for (char c : routes)
    {
        if (c == ';')
        {
            cout << endl;
            continue;
        }
        cout << c;
    }
    return 0;
}