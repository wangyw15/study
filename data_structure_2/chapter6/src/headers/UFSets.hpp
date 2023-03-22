#ifndef UFSETS
#define UFSETS

#include <memory>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <ios>
#include <map>

template <typename T> struct Node
{
    T Data;
    int Parent;

    Node<T>() { Parent = -1; }
};

template <typename T> class UFSets
{
  protected:
    std::shared_ptr<Node<T>[]> _Sets;
    size_t _Size;
    
    int _Find()
    {
        return 0;
    }

    void _RecureForHeight(int n, std::vector<int> &heights, int &height) const
    {
        heights.push_back(height++);
        for (size_t i = 0; i < _Size; i++)
        {
            if (_Sets[i].Parent == n)
            {
                _RecureForHeight(i, heights, height);
            }
        }
        height--;
    }
  
  public:
    UFSets(T data[], size_t n)
    {
        _Size = n;
        _Sets = std::shared_ptr<Node<T>[]>(new Node<T>[n]);
        for (size_t i = 0; i < n; i++)
        {
            _Sets[i].Data = data[i];
            _Sets[i].Parent = -1;
        }
    }

    virtual ~UFSets()
    {
        _Sets.reset();
        _Size = 0;
    }

    int GetOrder(T item) const
    {
        int i = 0;
        while (i < _Size && _Sets[i].Data != item)
        {
            i++;
        }
        if (i == _Size)
        {
            return -1;
        }
        return i;
    }

    int FindRoot(T item) const
    {
        int i = GetOrder(item);
        if (i == -1)
        {
            return -1;
        }
        while (_Sets[i].Parent >= 0)
        {
            i = _Sets[i].Parent;
        }
        return i;
    }

    // improved weighted union
    void Union(T a, T b)
    {
        int root1 = FindRoot(a), root2 = FindRoot(b);
        if (root1 != root2 && root1 != -1 && root2 != -1)
        {
            int p1 = _Sets[root1].Parent;
            int p2 = _Sets[root2].Parent;
            if (p1 == -1 && p2 == -1) // both are individual
            {
                if (root1 < root2)
                {
                    _Sets[root1].Parent += _Sets[root2].Parent;
                    _Sets[root2].Parent = root1;
                }
                else
                {
                    _Sets[root2].Parent += _Sets[root1].Parent;
                    _Sets[root1].Parent = root2;
                }
            }
            else
            {
                if (p1 < p2)
                {
                    _Sets[root1].Parent += _Sets[root2].Parent;
                    _Sets[root2].Parent = root1;
                }
                else
                {
                    _Sets[root2].Parent += _Sets[root1].Parent;
                    _Sets[root1].Parent = root2;
                }
            }
        }
    }

    void HeightedUnion(T a, T b)
    {
        int root1 = FindRoot(a), root2 = FindRoot(b);
        if (root1 != root2 && root1 != -1 && root2 != -1)
        {
            int h1 = GetSetHeight(root1), h2 = GetSetHeight(root2);
            if (GetSetHeight(root1) < GetSetHeight(root2))
            {
                _Sets[root2].Parent += _Sets[root1].Parent;
                _Sets[root1].Parent = root2;
            }
            else
            {
                _Sets[root1].Parent += _Sets[root2].Parent;
                _Sets[root2].Parent = root1;
            }
        }
    }

    int GetSetHeight(int n) const
    {
        n = FindRoot(_Sets[n].Data);
        if (n == -1)
        {
            return 0;
        }

        std::vector<int> heights;
        int height = 1;
        _RecureForHeight(n, heights, height);

        int ret = 0;
        for (auto i = heights.begin(); i != heights.end(); i++)
        {
            if (*i > ret)
            {
                ret = *i;
            }
        }
        return ret;
    }

    T GetElement(int n) const { return _Sets[n]; }

    friend std::ostream& operator<<(std::ostream& out, const UFSets<T> &sets)
    {
        std::shared_ptr<int[]> newParent(new int[sets.Size()]);
        // get root parent
        for (size_t i = 0; i < sets._Size; i++)
        {
            newParent[i] = sets._Sets[i].Parent >= 0
                               ? sets.FindRoot(sets._Sets[i].Data)
                               : sets._Sets[i].Parent;
        }

        for (size_t i = 0; i < sets._Size; i++)
        {
            if (newParent[i] < 0)
            {
                out << "{ " << sets._Sets[i].Data;
                for (int j = 0; j < sets._Size; j++)
                {
                    if (newParent[j] == i)
                    {
                        out << " " << sets._Sets[j].Data;
                    }
                }
                out << " } ";
            }
        }
        return out;
    }

    void ShowRawData() const
    {
        for (size_t i = 0; i < _Size; i++)
        {
            std::cout << _Sets[i].Data << "\t";
        }
        std::cout << std::endl;
        for (size_t i = 0; i < _Size; i++)
        {
            std::cout << _Sets[i].Parent << "\t";
        }
        std::cout << std::endl;
    }

    size_t Size() const { return _Size; }
};

#endif
