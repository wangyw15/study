#ifndef MINHEAP
#define MINHEAP

#include <vector>
#include <memory>
#include <ios>

template <typename T> class MinHeap
{
  private:
    std::vector<T> _Data;

  public:
    MinHeap() {}
    
    MinHeap(std::shared_ptr<T[]> data, size_t n)
    {
        for (size_t i = 0; i < n; i++)
        {
            Insert(data[i]);
        }
    }

    void FilterDown(const int start)
    {
        int i = start, j = 0;
        T tmp = _Data[i];
        j = 2 * i + 1;
        while (j <= _Data.size() - 1)
        {
            if (j < _Data.size() - 1 && _Data[j] > _Data[j + 1])
            {
                j++;
            }
            if (tmp <= _Data[j])
            {
                break;
            }
            else
            {
                _Data[i] = _Data[j];
                i = j;
                j = 2 * i + 1;
            }
        }
        _Data[i] = tmp;
    }

    void FilterUp(const int end)
    {
        int i, j = end;
        T tmp = _Data[j];
        i = (j - 1) / 2;
        while (j > 0)
        {
            if (_Data[i] < tmp)
            {
                break;
            }
            else
            {
                _Data[j] = _Data[i];
                j = i;
                i = (j - 1) / 2;
            }
        }
        _Data[j] = tmp;
    }

    void Insert(T &data)
    {
        _Data.push_back(data);
        // _Data[_Data.size()] = data;
        FilterUp(_Data.size() - 1);
    }

    size_t Size() const
    {
        return _Data.size();
    }

    friend std::ostream &operator<<(std::ostream &out, const MinHeap<T> &heap)
    {
        for (auto i = heap._Data.begin(); i != heap._Data.end(); i++)
        {
            out << *i << " ";
        }
        return out;
    }
};

#endif