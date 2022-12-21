#ifndef LINKLIST
#define LINKLIST

#include <iostream>
#include <ios>

template <typename T>
class LinkList
{
private:
    struct ListNode
    {
        T data;
        ListNode* prev;
        ListNode* next;
    };

    ListNode* _head, * _tail;
    long _size;

    ListNode* _NewNode()
    {
        return new ListNode;
    }

    void _Initialize()
    {
        _head = _NewNode();
        _tail = _NewNode();
        _head->next = _tail;
        _head->prev = nullptr;
        _tail->prev = _head;
        _tail->next = nullptr;
        _size = 0;
    }

public:
    ListNode* Begin()
    {
        return _head->next;
    }

    ListNode* End()
    {
        return _tail;
    }

    T& operator[](long n)
    {
        if (n >= _size)
        {
            throw "list index out of range";
        }
        auto ret = Begin();
        for (long i = 0; i < n; i++)
        {
            ret = ret->next;
        }
        return ret->data;
    }

    T& Get(long n) const
    {
        return this[n];
    }

    void Append(const T data)
    {
        auto node = _NewNode();
        /*node->data = new T;
        memcpy((void*)node->data, &data, sizeof(data));*/
        node->data = data;
        node->next = End();
        node->prev = End()->prev;
        End()->prev->next = node;
        End()->prev = node;
        _size++;
    }

    void Remove(long n)
    {
        auto target = Begin();
        for (long i = 0; i < n; i++)
        {
            target = target->next;
        }
        target->prev->next = target->next;
        target->next->prev = target->prev;
        delete target;
        _size--;
    }

    void Modify(long n, const T newData)
    {
        auto target = Begin();
        for (long i = 0; i < n; i++)
        {
            target = target->next;
        }
        target->data = new T;
        memcpy(node->data, &newData, sizeof(newData));
    }

    void Clear()
    {
        auto i = _head;
        while (i->next != nullptr)
        {
            i = i->next;
            delete i;
        }
        _Initialize();
    }

    size_t Size() const
    {
        return _size;
    }

    LinkList()
    {
        _Initialize();
    }

    LinkList(const LinkList& source)
    {
        *this = source;
    }

    ~LinkList()
    {
        auto i = _head;
        while (i->next != nullptr)
        {
            i = i->next;
            delete i->prev;
        }
    }

    LinkList& operator=(const LinkList& source)
    {
        if (this == &source)
        {
            return *this;
        }

        Clear();
        for (auto i = 0; i < source.Size(); i++)
        {
            Append(source[i]);
        }
        return *this;
    }
};

#endif