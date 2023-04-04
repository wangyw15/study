#ifndef ADJ_MATRIX_UNDIR_GRAPH
#define ADJ_MATRIX_UNDIR_GRAPH

#include <functional>
#include <ios>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <vector>
#include <limits>
#include <string>
#include <stack>

#define VISITED 2
#define UNVISITED 0

template <typename TVertex, typename TWeight> class AdjMatrixUndirGraph
{
  protected:
    std::vector<std::pair<int, TWeight>> _arcs;
    std::vector<std::pair<TVertex, int>> _vertexes;
    size_t _arcCount;

    void _DFS(int n, std::function<void(const TVertex &)> func)
    {
        SetTag(n, VISITED);
        func(GetVertex(n));
        for (int i = FirstAdjVex(n); i != -1; i = NextAdjVex(n, i))
        {
            if (GetTag(i) == UNVISITED)
            {
                _DFS(i, func);
            }
        }
    }

    void _DFS(TVertex item, std::function<void(const TVertex &)> func)
    {
        _DFS(GetVertexOrder(item), func);
    }

    constexpr TWeight Infinity() { return std::numeric_limits<TWeight>::max(); }

  public:
    AdjMatrixUndirGraph(const TVertex vertexes[], size_t n)
        : _arcs(n * n), _vertexes(n), _arcCount(0)
    {
        for (size_t i = 0; i < n; i++)
        {
            _vertexes[i].first = vertexes[i];
        }
        ClearArcs();
    }

    AdjMatrixUndirGraph(const std::vector<TVertex> &vertexes)
        : _arcs(vertexes.size() * vertexes.size()), _arcCount(0)
    {
        for (size_t i = 0; i < n; i++)
        {
            _vertexes[i].first = vertexes[i];
        }
        ClearArcs();
    }

    ~AdjMatrixUndirGraph()
    {
        ClearArcs();
        ClearTags();
    }

    friend std::ostream &
    operator<<(std::ostream &out,
               const AdjMatrixUndirGraph<TVertex, TWeight> &graph)
    {
        size_t col = 0;
        for (std::pair<int, TWeight> v : graph._arcs)
        {
            out << (v.second == NULL ? v.first : v.second) << " ";
            if (++col % graph.VertexCount() == 0)
            {
                out << std::endl;
            }
        }
        return out;
    }

    void ClearArcs()
    {
        for (size_t i = 0; i < _arcs.size(); i++)
        {
            _arcs[i].first = 0;
            _arcs[i].second = Infinity();
        }
        _arcCount = 0;
    }

    void ClearTags()
    {
        for (size_t i = 0; i < _vertexes.size(); i++)
        {
            _vertexes[i].second = 0;
        }
    }

    bool IsEmpty() const { return _arcCount == 0; }

    int GetVertexOrder(const TVertex &item) const
    {
        int ret = 0;
        for (std::pair<TVertex, int> v : _vertexes)
        {
            if (v.first == item)
            {
                return ret;
            }
            ret++;
        }
        return -1;
    }

    TVertex GetVertex(int n) const
    {
        if (n < 0 || n >= _vertexes.size())
        {
            throw std::overflow_error("Index out of range");
        }
        return _vertexes[n].first;
    }

    void SetVertex(int n, const TVertex &item)
    {
        if (n < 0 || n >= _vertexes.size())
        {
            throw std::overflow_error("Index out of range");
        }
        _vertexes[n].first = item;
    }

    size_t VertexCount() const { return _vertexes.size(); }

    size_t ArcCount() const { return _arcCount; }

    int FirstAdjVex(int n) const
    {
        if (n < 0 || n >= _vertexes.size())
        {
            throw std::overflow_error("Index out of range");
        }

        size_t start = n * _vertexes.size();
        for (size_t i = 0; i < _vertexes.size(); i++)
        {
            if (_arcs[start + i].first != 0)
            {
                return i;
            }
        }
        return -1;
    }

    int FirstAdjVex(const TVertex &item) const
    {
        return FirstAdjVex(GetVertexOrder(item));
    }

    TWeight GetWeight(int n1, int n2) const
    {
        if (n1 < 0 || n2 < 0 || n1 >= _vertexes.size() ||
            n2 >= _vertexes.size())
        {
            throw std::overflow_error("Index out of range");
        }
        return _arcs[n1 * _vertexes.size() + n2].second;
    }

    TWeight GetWeight(TVertex item1, TVertex item2)
    {
        return GetWeight(GetVertexOrder(item1), GetVertexOrder(item2));
    }

    int NextAdjVex(int n1, int n2) const
    {
        if (n1 < 0 || n2 < 0 || n1 >= _vertexes.size() ||
            n2 >= _vertexes.size())
        {
            throw std::overflow_error("Index out of range");
        }
        if (n1 == n2)
        {
            throw std::logic_error("Two vertexes cannot be same");
        }

        size_t start = n1 * _vertexes.size();
        for (size_t i = n2 + 1; i < _vertexes.size(); i++)
        {
            if (_arcs[start + i].first != 0)
            {
                return i;
            }
        }
        return -1;
    }

    int NextAdjVex(TVertex item1, TVertex item2) const
    {
        return NextAdjVex(GetVertexOrder(item1), GetVertexOrder(item2));
    }

    void InsertArc(int n1, int n2, TWeight weight = NULL)
    {
        if (n1 < 0 || n2 < 0 || n1 >= _vertexes.size() ||
            n2 >= _vertexes.size())
        {
            throw std::overflow_error("Index out of range");
        }
        _arcs[n1 * _vertexes.size() + n2].first = 1;
        _arcs[n1 * _vertexes.size() + n2].second = weight;
        _arcs[n2 * _vertexes.size() + n1].first = 1;
        _arcs[n2 * _vertexes.size() + n1].second = weight;
        _arcCount++;
    }

    void InsertArc(TVertex item1, TVertex item2, TWeight weight = 1)
    {
        InsertArc(GetVertexOrder(item1), GetVertexOrder(item2), weight);
    }

    void RemoveArc(int n1, int n2)
    {
        if (n1 < 0 || n2 < 0 || n1 >= _vertexes.size() ||
            n2 >= _vertexes.size())
        {
            throw std::overflow_error("Index out of range");
        }
        _arcs[n1 * _vertexes.size() + n2].first = 0;
        _arcs[n1 * _vertexes.size() + n2].second = Infinity;
        _arcs[n2 * _vertexes.size() + n1].first = 0;
        _arcs[n2 * _vertexes.size() + n1].second = Infinity;
        _arcCount--;
    }

    void RemoveArc(TVertex item1, TVertex item2)
    {
        RemoveArc(GetVertexOrder(item1), GetVertexOrder(item2));
    }

    int GetTag(int n) const { return _vertexes[n].second; }

    int GetTag(TVertex item) const
    {
        return _vertexes[GetVertexOrder(item)].second;
    }

    void SetTag(int n, int tag) { _vertexes[n].second = tag; }

    void SetTag(TVertex item, int tag)
    {
        _vertexes[GetVertexOrder(item)].second = tag;
    }

    void DFSTraverse(int n, std::function<void(const TVertex &)> func)
    {
        ClearTags();
        _DFS(n, func);
    }

    void DFSTraverse(TVertex item, std::function<void(const TVertex &)> func)
    {
        ClearTags();
        _DFS(GetVertexOrder(item), func);
    }

    bool ExistRoute(TVertex item1, TVertex item2)
    {
        ClearTags();
        bool ret = false;
        _DFS(item1,
            [&](TVertex item) -> void
            {
                if (item == item2)
                {
                    ret = true;
                }
            });
        return ret;
    }

    bool ExistRoute(int n1, int n2)
    {
        return ExistRoute(GetVertex(n1), GetVertex(n2));
    }

    std::string GetAllRoutes(int n1, int n2)
    {
        ClearTags();
        
        std::string ret = "";
        
        std::vector<bool> edgeVisited(VertexCount() * VertexCount(), false);
        std::stack<int> s;
        s.push(n1);
        _vertexes[n1].second = VISITED;
        
        int current = n1;
        std::string currentRoute = "";
        ret += GetVertex(n1);
        while (!s.empty())
        {
            int v = -1;
            for (int i = FirstAdjVex(current); i != -1;
                 i = NextAdjVex(current, i))
            {
                if (!edgeVisited[current * VertexCount() + i] &&
                    GetTag(i) != VISITED)
                {
                    v = i;
                    break;
                }
            }
            if (v != -1)
            {
                s.push(v);
                edgeVisited[current * VertexCount() + v] = true;
                edgeVisited[v * VertexCount() + current] = true;
                SetTag(v, VISITED);
                currentRoute += _vertexes[v].first;
                current = v;
            }
            else
            {
                SetTag(s.top(), UNVISITED);
                s.pop();
                current = s.empty() ? -1 : s.top();
                currentRoute = "";
                currentRoute += GetVertex(n1);
            }
            if (v == n2)
            {
                SetTag(s.top(), UNVISITED);
                s.pop();
                current = s.empty() ? -1 : s.top();
                ret += currentRoute + ";";
                currentRoute = "";
                currentRoute += GetVertex(n1);
            }
        }
        return ret;
    }

    std::string GetAllRoutes(TVertex item1, TVertex item2)
    {
        return GetAllRoutes(GetVertexOrder(item1), GetVertexOrder(item2));
    }
};

#endif
