#ifndef KRUSKAL
#define KRUSKAL

#include <memory>
#include <queue>
#include <vector>
#include <iostream>

#include "../../../chapter6/src/headers/UFSets.hpp"
#include "AdjMatrixUndirGraph.hpp"
#include "WeightedEdge.hpp"

template <typename TVertex, typename TWeight>
void MiniSpanningTreeKruskal(const AdjMatrixUndirGraph<TVertex, TWeight> &graph)
{
    int vexCount = graph.VertexCount();

    // copy vertexes to UFSets
    std::shared_ptr<TVertex[]> kVex =
        std::shared_ptr<TVertex[]>(new TVertex[vexCount]);
    for (size_t i = 0; i < vexCount; i++)
    {
        kVex[i] = graph.GetVertex(i);
    }
    UFSets<TVertex> f(kVex, vexCount);

    // store edges in minheap
    std::priority_queue<WeightedEdge<TVertex, TWeight>,
                        std::vector<WeightedEdge<TVertex, TWeight>>,
                        std::greater<WeightedEdge<TVertex, TWeight>>> edgeMinHeap;
    WeightedEdge<TVertex, TWeight> edge;
    for (int v = 0; v < vexCount; v++)
    {
        for (int u = graph.FirstAdjVex(v); u >= 0; u = graph.NextAdjVex(v, u))
        {
            if (v < u)
            {
                edge.Vertex1 = graph.GetVertex(v);
                edge.Vertex2 = graph.GetVertex(u);
                edge.Weight = graph.GetWeight(v, u);
                edgeMinHeap.push(edge);
            }
        }
    }

    // find minimum spanning tree through Kruskal algorithm
    int count = 0;
    TVertex v1, v2;
    while (count < vexCount - 1)
    {
        edge = edgeMinHeap.top();
        edgeMinHeap.pop();
        v1 = edge.Vertex1;
        v2 = edge.Vertex2;
        if (f.FindRoot(v1) != f.FindRoot(v2))
        {
            f.Union(v1, v2);
            std::cout << "(" << v1 << ", " << v2 << ") " << edge.Weight
                      << std::endl;
            count++;
        }
    }
}

#endif
