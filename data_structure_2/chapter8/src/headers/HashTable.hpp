#ifndef HASH_TABLE
#define HASH_TABLE

#include <cstddef>
#include <memory>
#include <string>
#include <functional>

#define DELETE -1
#define EMPTY 0
#define USE 1

template <typename TKey, typename TData>
class HashTable
{
protected:
    std::shared_ptr<TData[]> _data = nullptr;
    std::shared_ptr<int[]> _tag = nullptr;
    std::size_t _capacity = -1;
    std::size_t _count = 0;

    int Hash(TKey item)
    {
        
    }

    int Collision(TKey key, int i)
    {

    }

public:
    HashTable(int capacity)
    {
        _capacity = capacity;
        _count = 0;
        _data = std::shared_ptr<TData[]>(new TData[capacity]);
        _tag = std::shared_ptr<int[]>(new int[capacity]{0});
    }

    ~HashTable()
    {
        _data.reset();
        _data = nullptr;
        _tag.reset();
        _tag = nullptr;
    }

    void Traverse(std::function<void(const TData&)> func) const
    {
        for (std::size_t i = 0; i < _capacity; i++)
        {
            if (_tag[i] == USE)
            {
                func(_data[i]);
            }
        }
    }

    int Search(const TKey& key) const
    {

    }

    void Insert(const TData& item)
    {

    }

    void Delete(const TKey& key)
    {

    }
};

#endif