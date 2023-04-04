#ifndef BREAK_CIRCLE
#define BREAK_CIRCLE

#include <memory>
#include <queue>
#include <vector>
#include <iostream>
#include <string>

#include "headers/AdjMatrixUndirGraph.hpp"
#include "WeightedEdge.hpp"

template <typename TVertex, typename TWeight>
extern void MiniSpanningTreeBreakCircle(AdjMatrixUndirGraph<TVertex, TWeight> &graph)
{
    std::string circle = "";
    graph.DFSTraverse(0, [&circle](const TVertex item) { circle += item; });
    std::cout << graph._vertexes[0].first << std::endl;
}

#endif
