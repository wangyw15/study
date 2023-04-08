#ifndef SHORTEST_PATH
#define SHORTEST_PATH

#include <string>
#include <algorithm>

#include "AdjMatrixUndirGraph.hpp"

template <typename TVertex, typename TWeight>
std::vector<int> Dijkstra(AdjMatrixUndirGraph<TVertex, TWeight> &graph, int start, int destination)
{
    std::vector<int> dist(graph.VertexCount(), 0), path(graph.VertexCount(), 0);
    TWeight shortest = 0, infinity = graph.Infinity();
    
    // initialize data
    graph.ClearTags();
    for (int v = 0; v < graph.VertexCount(); v++)
    {
        dist[v] = graph.GetWeight(start, v);
        if (dist[v] == infinity || v == start)
        {
            path[v] = -1;
        }
        else
        {
            path[v] = start;
        }
        graph.SetTag(v, UNVISITED);
    }
    graph.SetTag(start, VISITED); // U={start}

    for (int i = 0; i < graph.VertexCount(); i++)
    {
        shortest = infinity;
        int u = start;
        // unvisited nearest vertex
        for (int v = 0; v < graph.VertexCount(); v++)
        {
            if (graph.GetTag(v) == UNVISITED && dist[v] < shortest)
            {
                u = v;
                shortest = dist[v];
            }
        }
        graph.SetTag(u, VISITED);
        // find shortest path
        for (int v = graph.FirstAdjVex(u); v != -1; v = graph.NextAdjVex(u, v))
        {
            if (graph.GetTag(v) == UNVISITED &&
                shortest + graph.GetWeight(u, v) < dist[v])
            {
                dist[v] = shortest + graph.GetWeight(u, v);
                path[v] = u;
            }
        }
    }

    std::vector<int> ret;
    int v = destination;
    while (v != -1)
    {
        ret.emplace(ret.begin(), v);
        v = path[v];
    }
    
    return ret;
}

template <typename TVertex, typename TWeight>
std::vector<TVertex> Dijkstra(AdjMatrixUndirGraph<TVertex, TWeight>& graph,
                              TVertex start, TVertex destination)
{
    std::vector<int> path = Dijkstra(graph, graph.GetVertexOrder(start),
                    graph.GetVertexOrder(destination));
    std::vector<TVertex> ret;
    for (auto& v : path)
    {
        ret.push_back(graph.GetVertex(v));
    }
    return ret;
}

template <typename TVertex, typename TWeight>
std::vector<int> DijkstraForMinimumWeight(AdjMatrixUndirGraph<TVertex, TWeight> &graph,
                          int start, int destination)
{
    std::vector<int> dist(graph.VertexCount(), 0), path(graph.VertexCount(), 0);
    TWeight shortest = 0, infinity = graph.Infinity();

    // initialize data
    graph.ClearTags();
    for (int v = 0; v < graph.VertexCount(); v++)
    {
        dist[v] = graph.GetWeight(start, v);
        if (dist[v] == infinity || v == start)
        {
            path[v] = -1;
        }
        else
        {
            path[v] = start;
        }
        graph.SetTag(v, UNVISITED);
    }
    graph.SetTag(start, VISITED); // U={start}

    for (int i = 0; i < graph.VertexCount(); i++)
    {
        shortest = infinity;
        int u = start;
        // unvisited nearest vertex
        for (int v = 0; v < graph.VertexCount(); v++)
        {
            if (graph.GetTag(v) == UNVISITED && dist[v] < shortest)
            {
                u = v;
                shortest = dist[v];
            }
        }
        graph.SetTag(u, VISITED);
        // minimum noise
        for (int v = graph.FirstAdjVex(u); v != -1; v = graph.NextAdjVex(u, v))
        {
            if (graph.GetTag(v) == UNVISITED && graph.GetWeight(u, v) < dist[v])
            {
                dist[v] = graph.GetWeight(u, v);
                path[v] = u;
            }
        }
    }

    std::vector<int> ret;
    int v = destination;
    while (v != -1)
    {
        ret.emplace(ret.begin(), v);
        v = path[v];
    }

    return ret;
}

template <typename TVertex, typename TWeight>
std::vector<TVertex>
DijkstraForMinimumWeight(AdjMatrixUndirGraph<TVertex, TWeight> &graph,
                         TVertex start, TVertex destination)
{
    std::vector<int> path = DijkstraForMinimumWeight(
        graph, graph.GetVertexOrder(start), graph.GetVertexOrder(destination));
    std::vector<TVertex> ret;
    for (auto &v : path)
    {
        ret.push_back(graph.GetVertex(v));
    }
    return ret;
}

#endif
