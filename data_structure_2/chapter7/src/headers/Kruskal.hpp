#ifndef KRUSKAL
#define KRUSKAL

#include <memory>
#include <queue>
#include <vector>

#include "AdjMatrixUndirGraph.hpp"
#include "../../../chapter6/src/headers/UFSets.hpp"

template <typename TVertex, typename TWeight> class KruskalEdge
{
  public:
    TVertex Vertex1, Vertex2;
    TWeight Weight;

    KruskalEdge() {}

    KruskalEdge(TVertex vertex1, TVertex vertex2, TWeight weight)
    {
        Vertex1 = vertex1;
        Vertex2 = vertex2;
        Weight = weight;
    }

    bool operator<(const KruskalEdge<TVertex, TWeight> &edge) const
    {
        return Weight < edge.Weight;
    }

    bool operator>(const KruskalEdge<TVertex, TWeight> &edge) const
    {
        return Weight > edge.Weight;
    }

    bool operator==(const KruskalEdge<TVertex, TWeight> &edge) const
    {
        return Weight == edge.Weight;
    }

    bool operator!=(const KruskalEdge<TVertex, TWeight> &edge) const
    {
        return Weight != edge.Weight;
    }

    bool operator<=(const KruskalEdge<TVertex, TWeight> &edge) const
    {
        return Weight <= edge.Weight;
    }

    bool operator>=(const KruskalEdge<TVertex, TWeight> &edge) const
    {
        return Weight >= edge.Weight;
    }

    KruskalEdge<TVertex, TWeight> &
    operator=(const KruskalEdge<TVertex, TWeight> &edge)
    {
        if (&edge != this)
        {
            Vertex1 = edge.Vertex1;
            Vertex2 = edge.Vertex2;
            Weight = edge.Weight;
        }
        return *this;
    }
};

template <typename TVertex, typename TWeight>
void MiniSpanningTreeKruskal(const AdjMatrixUndirGraph<TVertex, TWeight>& graph)
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
    std::priority_queue<KruskalEdge<TVertex, TWeight>,
                        std::vector<KruskalEdge<TVertex, TWeight>>,
                        std::greater<KruskalEdge<TVertex, TWeight>>> ha;
    KruskalEdge<TVertex, TWeight> edge;
    for (int v = 0; v < vexCount; v++)
    {
        for (int u = graph.FirstAdjVex(v); u >= 0; u = graph.NextAdjVex(v, u))
        {
            if (v < u)
            {
                edge.Vertex1 = graph.GetVertex(v);
                edge.Vertex2 = graph.GetVertex(u);
                edge.Weight = graph.GetWeight(v, u);
                ha.push(edge);
            }
        }
    }
    
    // find minimum spanning tree throught Kruskal algorithm
    int count = 0;
    TVertex v1, v2;
    while (count < vexCount - 1)
    {
        edge = ha.top();
        ha.pop();
        v1 = edge.Vertex1;
        v2 = edge.Vertex2;
        if (f.FindRoot(v1) != f.FindRoot(v2))
        {
            f.Union(v1, v2);
            std::cout << "(" << v1 << ", " << v2 << ") " << edge.Weight << std::endl;
            count++;
        }
    }
}

#endif
