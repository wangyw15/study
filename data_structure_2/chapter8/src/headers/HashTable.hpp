#ifndef HASH_TABLE
#define HASH_TABLE

#include <cstddef>
#include <memory>
#include <string>
#include <functional>
#include <stdexcept>

#define DELETE -1
#define EMPTY 0
#define USE 1

template <typename T>
class HashTable
{
protected:
    std::shared_ptr<T[]> _data = nullptr;
    std::shared_ptr<int[]> _tag = nullptr;
    std::size_t _capacity = -1;
    std::size_t _count = 0;
    std::size_t p = 0;

    int _Hash(T item)
    {
        return item % p;
    }

    int _Collision(T item, int i)
    {
        return (_Hash(item) + i) % _capacity;
    }

    int _IsPrime(size_t num)
    {
        for(size_t i = 2; i < num; i++)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    }

public:
    HashTable(int capacity)
    {
        _capacity = capacity;
        _count = 0;
        _data = std::shared_ptr<T[]>(new T[capacity]);
        _tag = std::shared_ptr<int[]>(new int[capacity]{0});

        // find p
        for (p = _capacity; p > 0; p--)
        {
            if (_IsPrime(p))
            {
                break;
            }
        }
    }

    ~HashTable()
    {
        _data.reset();
        _data = nullptr;
        _tag.reset();
        _tag = nullptr;
    }

    void Traverse(std::function<void(const T&)> func) const
    {
        for (std::size_t i = 0; i < _capacity; i++)
        {
            if (_tag[i] == USE)
            {
                func(_data[i]);
            }
        }
    }

    int Search(const T& item) const
    {
        int collision = 0; // collision count
        int hash = _Hash(item); // hashed
        while (collision < _capacity &&
            ((_tag[hash] == USE && _data[hash] != item) || _tag[hash] == DELETE))
        {
            hash = _Collision(item, ++collision);
        }
        if (collision >= _capacity || _tag[hash] == EMPTY)
        {
            return -1;
        }
        return hash;
    }

    void Insert(const T& item)
    {
        int collision = 0; // collision count
        int hash = _Hash(item); // hashed
        int pos = -1; // insert position
        while (collision < _capacity &&
            ((_tag[hash] == USE && _data[hash] != item) || _tag[hash] == DELETE))
        {
            if (pos == -1 && _tag[hash] == DELETE)
            {
                pos = hash;
            }
            hash = _Collision(item, ++collision);
        }
        if (collision >= _capacity && pos == -1)
        {
            throw std::overflow_error("Hash table is full!");
        }
        else if (_tag[hash] == USE && _data[hash] == item)
        {
            throw std::logic_error("Given item is already stored in the table.");
        }
        else
        {
            if (pos == -1)
            {
                pos = hash;
            }
            _data[pos] = item;
            _tag[pos] = USE;
        }
    }

    void Delete(const T& item)
    {
        int i = Search(item);
        if (i != -1)
        {
            _tag[i] = DELETE;
        }
    }
};

#endif