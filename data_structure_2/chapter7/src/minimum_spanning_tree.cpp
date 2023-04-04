#include <iostream>
#include <string>

#include "headers/AdjMatrixUndirGraph.hpp"
#include "headers/Kruskal.hpp"
#include "headers/Prim.hpp"
#include "headers/BreakCircle.hpp"

using namespace std;

int main()
{
    string vertexes[] = {"A", "B", "C", "D", "E", "F"};
    auto matrix = AdjMatrixUndirGraph<string, int>(vertexes, 6);
    matrix.InsertArc("A", "B", 34);
    matrix.InsertArc("B", "E", 12);
    matrix.InsertArc("A", "F", 19);
    matrix.InsertArc("F", "E", 26);
    matrix.InsertArc("A", "C", 46);
    matrix.InsertArc("F", "D", 25);
    matrix.InsertArc("D", "E", 38);
    matrix.InsertArc("C", "D", 17);

    // kruskal
    cout << "Kruskal" << endl;
    MiniSpanningTreeKruskal<string, int>(matrix);
    cout << endl;

    // prim
    matrix.InsertArc("C", "F", 25);
    cout << "Prim" << endl;
    MiniSpanningTreePrim<string, int>(matrix, 0);
    cout << endl;
    
    // break_circle
    cout << "Break circle" << endl;
    std::cout << matrix << std::endl;
    matrix.BreakCircle();
    std::cout << matrix << std::endl;
    cout << endl;
    
    return 0;
}