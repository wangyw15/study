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

template <typename TKey, typename TValue>
class HashTable
{
protected:
    std::shared_ptr<TValue[]> _data = nullptr;
    std::shared_ptr<int[]> _tag = nullptr;
    std::size_t _capacity = -1;
    std::size_t _count = 0;

    int _Hash(TKey key)
    {
        return key % p;
    }

    int _Collision(TKey key, int i)
    {
        return (_Hash(key) + i) % _capacity;
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
        _data = std::shared_ptr<TValue[]>(new TValue[capacity]);
        _tag = std::shared_ptr<int[]>(new int[capacity]{0});
    }

    ~HashTable()
    {
        _data.reset();
        _data = nullptr;
        _tag.reset();
        _tag = nullptr;
    }

    void Traverse(std::function<void(const TValue&)> func) const
    {
        for (std::size_t i = 0; i < _capacity; i++)
        {
            if (_tag[i] == USE)
            {
                func(_data[i]);
            }
        }
    }

    TValue &Search(const TKey& key) const
    {
        int collision = 0; // collision count
        int hash = _Hash(key); // hashed
        while (collision < _capacity &&
            ((_tag[hash] == USE && _data[hash] != key) || _tag[hash] == DELETE))
        {
            hash = _Collision(key, ++collision);
        }
        if (collision >= _capacity || _tag[hash] == EMPTY)
        {
            return -1;
        }
        return hash;
    }

    void Insert(const TKey& key, const TValue& data)
    {
        int collision = 0; // collision count
        int hash = _Hash(key); // hashed
        int pos = -1; // insert position
        while (collision < _capacity &&
            ((_tag[hash] == USE && _data[hash] != key) || _tag[hash] == DELETE))
        {
            if (pos == -1 && _tag[hash] == DELETE)
            {
                pos = hash;
            }
            hash = _Collision(key, ++collision);
        }
        if (collision >= _capacity && pos == -1)
        {
            throw std::overflow_error("Hash table is full!");
        }
        else if (_tag[hash] == USE && _data[hash] == key)
        {
            throw std::logic_error("Given item is already stored in the table.");
        }
        else
        {
            if (pos == -1)
            {
                pos = hash;
            }
            _data[pos] = data;
            _tag[pos] = USE;
        }
    }

    void Delete(const TKey& key)
    {
        int i = Search(key);
        if (i != -1)
        {
            _tag[i] = DELETE;
        }
    }

    TValue& GetDataFromIndex(int n) const { return _data[n]; }
};

#endif