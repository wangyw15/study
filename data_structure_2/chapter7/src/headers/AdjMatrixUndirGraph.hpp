#ifndef ADJ_MATRIX_UNDIR_GRAPH
#define ADJ_MATRIX_UNDIR_GRAPH

#include <functional>
#include <ios>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <vector>

#define VISISTED 1
#define UNVISISTED 0

template <typename T> class AdjMatrixUndirGraph
{
  protected:
    std::vector<std::pair<int, int>> _arcs;
    std::vector<std::pair<T, int>> _vertexes;
    size_t _arcCount;

    void _DFS(int n, std::function<void(const T &)> func)
    {
        SetTag(n, VISISTED);
        func(GetVertex(n));
        for (int i = FirstAdjVex(n); i != -1; i = NextAdjVex(n, i))
        {
            if (GetTag(i) == UNVISISTED)
            {
                _DFS(i, func);
            }
        }
    }

    void _DFS(T item, std::function<void(const T &)> func)
    {
        _DFS(GetVertexOrder(item), func);
    }

  public:
    AdjMatrixUndirGraph(const T vertexes[], size_t n)
        : _arcs(n * n), _vertexes(n), _arcCount(0)
    {
        for (size_t i = 0; i < n; i++)
        {
            _vertexes[i].first = vertexes[i];
        }
    }

    AdjMatrixUndirGraph(const std::vector<T> &vertexes)
        : _arcs(vertexes.size() * vertexes.size()), _arcCount(0)
    {
        for (size_t i = 0; i < n; i++)
        {
            _vertexes[i].first = vertexes[i];
        }
    }

    ~AdjMatrixUndirGraph()
    {
        ClearArcs();
        ClearTags();
    }

    friend std::ostream &operator<<(std::ostream &out,
                                    const AdjMatrixUndirGraph<T> &graph)
    {
        size_t col = 0;
        for (std::pair<int, int> v : graph._arcs)
        {
            out << v.first << " ";
            if (++col % 4 == 0)
            {
                out << std::endl;
            }
        }
        return out;
    }

    void ClearArcs()
    {
        for (std::pair<int, int> a : _arcs)
        {
            a.first = 0;
            a.second = 0;
        }
        _arcCount = 0;
    }

    void ClearTags()
    {
        for (std::pair<T, int> v : _vertexes)
        {
            v.second = 0;
        }
    }

    bool IsEmpty() const { return _arcCount == 0; }

    int GetVertexOrder(const T &item) const
    {
        int ret = 0;
        for (std::pair<T, int> v : _vertexes)
        {
            if (v.first == item)
            {
                return ret;
            }
            ret++;
        }
        return -1;
    }

    T GetVertex(int n) const
    {
        if (n < 0 || n >= _vertexes.size())
        {
            throw std::overflow_error("Index out of range");
        }
        return _vertexes[n].first;
    }

    void SetVertex(int n, const T &item)
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

    int FirstAdjVex(const T &item) const
    {
        return FirstAdjVex(GetVertexOrder(item));
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

    int NextAdjVex(T item1, T item2) const
    {
        return NextAdjVex(GetVertexOrder(item1), GetVertexOrder(item2));
    }

    void InsertArc(int n1, int n2, int weight = 0)
    {
        if (n1 < 0 || n2 < 0 || n1 >= _vertexes.size() ||
            n2 >= _vertexes.size())
        {
            throw std::overflow_error("Index out of range");
        }
        _arcs[n1 * _vertexes.size() + n2].first++;
        _arcs[n1 * _vertexes.size() + n2].second = weight;
        _arcs[n2 * _vertexes.size() + n1].first++;
        _arcs[n2 * _vertexes.size() + n1].second = weight;
        _arcCount++;
    }

    void InsertArc(T item1, T item2)
    {
        InsertArc(GetVertexOrder(item1), GetVertexOrder(item2));
    }

    int GetTag(int n) const { return _vertexes[n].second; }

    int GetTag(T item) const { return _vertexes[GetVertexOrder(item)].second; }

    void SetTag(int n, int tag) { _vertexes[n].second = tag; }

    void SetTag(T item, int tag)
    {
        _vertexes[GetVertexOrder(item)].second = tag;
    }

    void DFSTraverse(int n, std::function<void(const T&)> func)
    {
        ClearTags();
        _DFS(n, func);
    }

    void DFSTraverse(T item, std::function<void(const T &)> func)
    {
        ClearTags();
        _DFS(GetVertexOrder(item), func);
    }

    bool ExistRoute(T item1, T item2)
    {
        ClearTags();
        bool ret = false;
        DFS(item1,
            [&](T item) -> void
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
};

#endif
