#ifndef SINGLE_LINK_LIST_WITHOUT_HEAD
#define SINGLE_LINK_LIST_WITHOUT_HEAD

#include <algorithm>
#include <functional>
#include <ios>
#include <iostream>
#include <string>

template <typename T> struct Node
{
    T data;
    Node *next;
};

template <typename T> class SingleLinkListWithoutHead
{
  protected:
    static std::ostream &_DefaultPrinter(std::ostream &out,
                                         SingleLinkListWithoutHead<T> &list)
    {
        out << std::string("[ ");
        Node<T> *pointer = list._head;
        if (list._length == 1)
        {
            out << pointer->data;
        }
        else
        {
            for (auto i = 0; i < list._length; i++)
            {
                out << pointer->data << (i != list._length - 1 ? ", " : "");
                pointer = pointer->next;
            }
        }
        out << std::string(" ]");
        return out;
    }

    Node<T> *_head = nullptr;
    long _length = 0;
    std::function<std::ostream &(std::ostream &,
                                 SingleLinkListWithoutHead<T> &)>
        _printer = _DefaultPrinter;

  public:
    SingleLinkListWithoutHead()
    {
        _head = nullptr;
        _length = 0;
    }

    SingleLinkListWithoutHead(T arr[], int n, bool sortData = false)
    {
        if (sortData)
        {
            std::sort(arr, arr + n);
        }

        if ((_length = n) != 0)
        {
            _head = new Node<T>;
            _head->data = arr[0];
            _head->next = _head;

            Node<T> *pointer = _head;
            for (auto i = 1; i < n; i++)
            {
                Node<T> *current = new Node<T>;
                current->data = arr[i];
                current->next = _head;

                pointer->next = current;
                pointer = current;
            }
        }
    }

    virtual ~SingleLinkListWithoutHead() { Clear(); }

    SingleLinkListWithoutHead(const SingleLinkListWithoutHead &list)
    {
        *this = list;
    }

    SingleLinkListWithoutHead<T> &
    operator=(const SingleLinkListWithoutHead &list)
    {
        if (&list != this && (_length = list._length) != 0)
        {
            _head = new Node<T>;
            _head->data = list._head->data;
            _head->next = _head;

            Node<T> *pointer = _head;
            Node<T> *listPointer = list._head->next;
            for (auto i = 1; i < _length; i++)
            {
                Node<T> *current = new Node<T>;
                current->data = listPointer->data;
                current->next = _head;

                pointer->next = current;
                pointer = current;
                listPointer = listPointer->next;
            }
        }

        return *this;
    }

    long Length() const { return _length; }

    Node<T> *Head() { return _head; }

    bool IsEmpty() const { return _length == 0; }

    void Traverse(std::function<void(T)> func) const
    {
        Node<T> *pointer = _head;
        for (auto i = 0; i < _length; i++)
        {
            func(pointer->data);
            pointer = pointer->next;
        }
    }

    long Locate(T item) const
    {
        Node<T> *pointer = _head;
        for (auto i = 0; i < _length; i++)
        {
            if (item == pointer->data)
            {
                return i;
            }
            pointer = pointer->next;
        }
        return -1;
    }

    void Change(int n, T item)
    {
        if (n < _length)
        {
            Node<T> *pointer = _head;
            for (auto i = 0; i < n; i++)
            {
                pointer = pointer->next;
            }
            pointer->data = item;
        }
        else
        {
            throw "Index out of range";
        }
    }

    void Delete(int n)
    {
        if (n < _length)
        {
            Node<T> *pointer = _head;
            if (n == 0)
            {
                for (auto i = 0; i < _length - 1; i++)
                {
                    pointer = pointer->next;
                }
                pointer->next = _head->next;
                delete _head;
                _head = pointer->next;
            }
            else
            {
                for (auto i = 0; i < n - 1; i++)
                {
                    pointer = pointer->next;
                }
                Node<T> *temp = pointer->next;
                pointer->next = pointer->next->next;
                delete temp;
            }
            _length--;
        }
        else
        {
            throw "Index out of range";
        }
    }

    void Insert(int n, T item)
    {
        if (n <= _length)
        {
            Node<T> *pointer = _head;
            if (n == 0)
            {
                for (auto i = 0; i < _length - 1; i++)
                {
                    pointer = pointer->next;
                }
                Node<T> *node = new Node<T>();
                node->data = item;
                node->next = _head;

                pointer->next = node;
                _head = node;
            }
            else
            {
                for (auto i = 0; i < n - 1; i++)
                {
                    pointer = pointer->next;
                }
                Node<T> *node = new Node<T>();
                node->data = item;
                node->next = pointer->next;
                pointer->next = node;
            }
            _length++;
        }
        else
        {
            throw "Index out of range";
        }
    }

    void Clear()
    {
        Node<T> *pointer = _head;
        for (auto i = 0; i < _length; i++)
        {
            Node<T> *temp = pointer->next;
            delete pointer;
            pointer = temp;
        }
        _length = 0;
    }

    T &operator[](int n) const
    {
        if (n < _length)
        {
            auto index = 0;
            Node<T> *pointer = _head;
            for (auto i = 0; i < n; i++)
            {
                pointer = pointer->next;
            }
            return pointer->data;
        }
        else
        {
            throw "Index out of range";
        }
    }

    void Reverse()
    {
        if (_length >= 1)
        {
            Node<T> *pointer = _head;
            Node<T> *previous = nullptr;
            Node<T> *temp = nullptr;
            for (auto i = 0; i < _length; i++)
            {
                temp = pointer;
                pointer = pointer->next;
                temp->next = previous;
                previous = temp;
            }
            _head->next = previous;
            _head = previous;
        }
    }

    void Sort()
    {
        Node<T> *pointer = _head;
        for (auto i = 0; i < _length - 1; i++)
        {
            pointer = _head;
            for (auto j = 0; j < _length - 1 - i; j++)
            {
                if (pointer->data > pointer->next->data)
                {
                    auto temp = pointer->data;
                    pointer->data = pointer->next->data;
                    pointer->next->data = temp;
                }
                pointer = pointer->next;
            }
        }
    }

    void InsertByOrder(const T item)
    {
        Sort();

        Node<T> *node = new Node<T>;
        node->data = item;
        _length++;

        if (item < _head->data)
        {
            node->data = _head->data;
            _head->data = item;
            node->next = _head->next;
            _head->next = node;
            return;
        }

        Node<T> *pointer = _head;
        for (auto i = 0; i < _length - 2; i++)
        {
            if (pointer->next->data >= item)
            {
                node->next = pointer->next;
                pointer->next = node;
                return;
            }
            pointer = pointer->next;
        }
        node->next = pointer->next;
        pointer->next = node;
    }

    void MergeByOrder(SingleLinkListWithoutHead &list)
    {
        Sort();
        list.Sort();

        long newLength = _length + list._length, listIndex = 0, selfIndex = 0;

        Node<T> *newHead = new Node<T>;
        newHead->next = nullptr;

        Node<T> *pointer = newHead;
        Node<T> *listPointer = list._head;
        Node<T> *selfPointer = _head;

        for (auto i = 0; i < newLength; i++)
        {
            if (listIndex >= list._length)
            {
                T data(selfPointer->data);
                Node<T> *node = new Node<T>;
                node->data = data;
                node->next = nullptr;

                pointer->next = node;
                pointer = node;
                selfPointer = selfPointer->next;
                selfIndex++;
            }
            else if (selfIndex >= _length)
            {
                T data(listPointer->data);
                Node<T> *node = new Node<T>;
                node->data = data;
                node->next = nullptr;

                pointer->next = node;
                pointer = node;
                listPointer = listPointer->next;
                listIndex++;
            }
            else if (listIndex < list._length && selfIndex < _length)
            {
                if (selfPointer->data < listPointer->data)
                {
                    T data(selfPointer->data);
                    Node<T> *node = new Node<T>;
                    node->data = data;
                    node->next = nullptr;

                    pointer->next = node;
                    pointer = node;
                    selfPointer = selfPointer->next;
                    selfIndex++;
                }
                else
                {
                    T data(listPointer->data);
                    Node<T> *node = new Node<T>;
                    node->data = data;
                    node->next = nullptr;

                    pointer->next = node;
                    pointer = node;
                    listPointer = listPointer->next;
                    listIndex++;
                }
            }
        }

        Clear();
        pointer->next = newHead->next;
        _head = newHead->next;
        _length = newLength;
    }

    void
    SetPrintMethod(std::function<std::ostream &(std::ostream &,
                                                SingleLinkListWithoutHead<T> &)>
                       printer = _DefaultPrinter)
    {
        _printer = printer;
    }

    friend std::ostream &operator<<(std::ostream &out,
                                    SingleLinkListWithoutHead<T> &list)
    {
        return list._printer(out, list);
    }
};

#endif