#ifndef PRIM
#define PRIM

#include <iostream>
#include <memory>
#include <queue>
#include <vector>
#include <limits>

// #include "../../../chapter6/src/headers/UFSets.hpp"
#include "AdjMatrixUndirGraph.hpp"

template <typename TVertex, typename TWeight> struct CloseArc
{
    TWeight LowWeight;
    int NearVertex;
};

template <typename TVertex, typename TWeight>
void MiniSpanningTreePrim(const AdjMatrixUndirGraph<TVertex, TWeight> &graph,
                          int u0)
{
    int vexCount = graph.VertexCount();
    if (u0 < 0 || u0 >= vexCount)
    {
        throw std::overflow_error("Index out of range");
    }

    TWeight minWeight;
    std::shared_ptr<CloseArc<TVertex, TWeight>[]> closeArcs(
        new CloseArc<TVertex, TWeight>[vexCount]);

    // initialize closeArcs
    // LowWeight: -1 for the root, 0 indicates that the vertex is in U
    for (int v = 0; v < vexCount; v++)
    {
        closeArcs[v].NearVertex = u0;
        closeArcs[v].LowWeight = graph.GetWeight(u0, v);
    }
    closeArcs[u0].NearVertex = -1;
    closeArcs[u0].LowWeight = 0;

    // find minimum spanning tree through Prim algorithm
    for (int k = 1; k < vexCount; k++)
    {
        minWeight = std::numeric_limits<int>::max();
        int v = u0;
        for (int u = 0; u < vexCount; u++)
        {
            if (closeArcs[u].LowWeight != 0 &&
                closeArcs[u].LowWeight < minWeight)
            {
                v = u;
                minWeight = closeArcs[u].LowWeight;
            }
        }
        
        if (v != u0)
        {
            std::cout << "(" << graph.GetVertex(closeArcs[v].NearVertex) << ", "
                      << graph.GetVertex(v) << ") " << minWeight << std::endl;
            closeArcs[v].LowWeight = 0;
            for (int u = graph.FirstAdjVex(v); u != -1; u = graph.NextAdjVex(v, u))
            {
                if (closeArcs[u].LowWeight != 0 &&
                    (graph.GetWeight(v, u) < closeArcs[u].LowWeight))
                {
                    closeArcs[u].LowWeight = graph.GetWeight(v, u);
                    closeArcs[u].NearVertex = v;
                }
            }
        }
    }
}

#endif
