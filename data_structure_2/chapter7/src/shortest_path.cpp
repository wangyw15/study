#include <iostream>
#include <string>

#include "headers/AdjMatrixUndirGraph.hpp"
#include "headers/ShortestPath.hpp"

using namespace std;

int main()
{
    string vertexes[] = {"A", "B", "C", "D", "E", "F", "G"};
    AdjMatrixUndirGraph<string, int> graph(vertexes, 7);
    graph.InsertArc("A", "B", 50);
    graph.InsertArc("B", "E", 90);
    graph.InsertArc("E", "G", 40);
    graph.InsertArc("G", "F", 140);
    graph.InsertArc("F", "C", 50);
    graph.InsertArc("C", "A", 60);
    graph.InsertArc("D", "B", 120);
    graph.InsertArc("D", "G", 70);
    graph.InsertArc("D", "F", 80);
    
    vector<string> path = DijkstraForMinimumWeight<string, int>(graph, "A", "G");
    int minimumNoise = graph.GetWeight(path[0], path[1]);
    cout << path[0];
    for (auto i = 1; i < path.size(); i++)
    {
        cout << " -" << graph.GetWeight(path[i - 1], path[i]) << "-> " << path[i];
    }
    cout << endl << "Minimum noise: " << minimumNoise << endl;
    return 0;
}