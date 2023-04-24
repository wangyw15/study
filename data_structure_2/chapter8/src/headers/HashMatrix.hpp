#ifndef HASH_MATRIX
#define HASH_MATRIX

#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>

#define DELETE -1
#define EMPTY 0
#define USE 1

struct MatrixNode
{
    int X, Y;
    double Data;

    MatrixNode()
    {
        X = Y = 0;
        Data = 0;
    }

    MatrixNode(int x, int y, double data)
    {
        X = x;
        Y = y;
        Data = data;
    }
};

class HashMatrix
{
  protected:
    std::shared_ptr<MatrixNode[]> _data = nullptr;
    std::shared_ptr<int[]> _tag = nullptr;
    std::size_t _capacity = -1;
    std::size_t _count = 0;

    int _Hash(int x, int y) const
    {
        // 1% has data, see the matrix as 100x100
        return x * 100 + y;
    }

    int _Collision(int x, int y, int i) const
    {
        return (_Hash(x, y) + i) % _capacity;
    }

  public:
    HashMatrix()
    {
        _capacity = 0;
        _count = 0;
        _data = nullptr;
        _tag = nullptr;
    }

    HashMatrix(int capacity = 1000 * 1000 * 0.01)
    {
        _capacity = capacity;
        _count = 0;
        _data = std::shared_ptr<MatrixNode[]>(new MatrixNode[capacity]);
        _tag = std::shared_ptr<int[]>(new int[capacity]{0});
    }

    ~HashMatrix()
    {
        _data.reset();
        _data = nullptr;
        _tag.reset();
        _tag = nullptr;
    }

    void Traverse(std::function<void(const MatrixNode &)> func) const
    {
        for (std::size_t i = 0; i < _capacity; i++)
        {
            if (_tag[i] == USE)
            {
                func(_data[i]);
            }
        }
    }

    int Search(int x, int y) const
    {
        int collision = 0;      // collision count
        int hash = _Hash(x, y); // hashed
        while (collision < _capacity &&
               ((_tag[hash] == USE && (_data[hash].X != x || _data[hash].Y != y)) ||
                _tag[hash] == DELETE))
        {
            hash = _Collision(x, y, ++collision);
        }
        if (collision >= _capacity || _tag[hash] == EMPTY)
        {
            return -1;
        }
        return hash;
    }

    void Insert(int x, int y, double data)
    {
        int collision = 0;      // collision count
        int hash = _Hash(x, y); // hashed
        int pos = -1;           // insert position
        while (collision < _capacity &&
               ((_tag[hash] == USE && (_data[hash].X != x || _data[hash].Y != y)) ||
                _tag[hash] == DELETE))
        {
            if (pos == -1 && _tag[hash] == DELETE)
            {
                pos = hash;
            }
            hash = _Collision(x, y, ++collision);
        }
        if (collision >= _capacity && pos == -1)
        {
            throw std::overflow_error("Hash table is full!");
        }
        else if (_tag[hash] == USE &&
                 (_data[hash].X != x || _data[hash].Y != y))
        {
            throw std::logic_error(
                "Given item is already stored in the table.");
        }
        else
        {
            if (pos == -1)
            {
                pos = hash;
            }
            _data[pos].X = x;
            _data[pos].Y = y;
            _data[pos].Data = data;
            _tag[pos] = USE;
            _count++;
        }
    }

    void Delete(int x, int y)
    {
        int i = Search(x, y);
        if (i != -1)
        {
            _tag[i] = DELETE;
        }
    }

    double &GetDataFromIndex(int n) const { return _data[n].Data; }
};

#endif
