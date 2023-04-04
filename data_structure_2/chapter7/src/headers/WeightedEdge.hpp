#ifndef WEIGHTED_EDGE
#define WEIGHTED_EDGE

template <typename TVertex, typename TWeight> class WeightedEdge
{
  public:
    TVertex Vertex1, Vertex2;
    TWeight Weight;

    WeightedEdge() {}

    WeightedEdge(TVertex vertex1, TVertex vertex2, TWeight weight)
    {
        Vertex1 = vertex1;
        Vertex2 = vertex2;
        Weight = weight;
    }

    bool operator<(const WeightedEdge<TVertex, TWeight> &edge) const
    {
        return Weight < edge.Weight;
    }

    bool operator>(const WeightedEdge<TVertex, TWeight> &edge) const
    {
        return Weight > edge.Weight;
    }

    bool operator==(const WeightedEdge<TVertex, TWeight> &edge) const
    {
        return Weight == edge.Weight;
    }

    bool operator!=(const WeightedEdge<TVertex, TWeight> &edge) const
    {
        return Weight != edge.Weight;
    }

    bool operator<=(const WeightedEdge<TVertex, TWeight> &edge) const
    {
        return Weight <= edge.Weight;
    }

    bool operator>=(const WeightedEdge<TVertex, TWeight> &edge) const
    {
        return Weight >= edge.Weight;
    }

    WeightedEdge<TVertex, TWeight> &
    operator=(const WeightedEdge<TVertex, TWeight> &edge)
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

#endif