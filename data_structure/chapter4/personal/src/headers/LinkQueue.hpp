#ifndef LINKQUEUE
#define LINKQUEUE

#include <ios>
#include <functional>
#include <stdexcept>

template <typename T>
struct Node
{
    T Data;
    Node<T> *Next;
};

template <typename T>
class LinkQueue
{
protected:
    Node<T>* _Rear = nullptr;
    long _Length = 0;
    std::function<std::ostream&(std::ostream&, const LinkQueue<T>&)> _Printer = _DefaultPrinter;

    static std::ostream& _DefaultPrinter(std::ostream& out, const LinkQueue<T>& queue)
    {
        out << std::string("[ ");
        if (queue._Rear != nullptr)
        {
            Node<T> *pointer = queue._Rear;
            while ((pointer = pointer->Next) != queue._Rear)
            {
                out << pointer->Data << ", ";
            }
            out << pointer->Data;
        }
        out << std::string(" ]");
        return out;
    }

public:
    LinkQueue()
    {
        _Rear = nullptr;
        _Length = 0;
    }

    LinkQueue(const LinkQueue<T> &queue)
    {
        *this = queue;
    }

    LinkQueue<T> &operator=(const LinkQueue<T> &queue)
    {
        if (&queue != this)
        {
            if (_Rear != nullptr)
            {
                Clear();
            }
            if (queue._Rear != nullptr)
            {
                _Length = queue._Length;
                _Printer = queue._Printer;
                /*_Rear = new Node<T>;
                _Rear->Data = queue._Rear->Data;
                _Rear->Next = _Rear;*/

                Node<T> *pointer = queue._Rear;
                // Node<T> *selfPointer = _Rear;
                while ((pointer = pointer->Next) != queue._Rear)
                {
                    EnQueue(pointer->Data);
                    /*Node<T> *newNode = new Node<T>;
                    newNode->Data = pointer->Data;
                    newNode->Next = selfPointer->Next;
                    selfPointer->Next = newNode;
                    selfPointer = newNode;*/
                }
                EnQueue(pointer->Data);
            }
        }
        return *this;
    }

    virtual ~LinkQueue()
    {
        Clear();
    }

    friend std::ostream& operator<<(std::ostream &out, const LinkQueue<T> &queue)
    {
        return queue._Printer(out, queue);
    }

    void SetPrinter(std::function<std::ostream&(std::ostream&, LinkQueue<T>&)> printer = _DefaultPrinter)
    {
        _Printer = printer;
    }

    long Length() const
    {
        return _Length;
    }

    bool IsEmpty() const
    {
        return _Rear == nullptr;
    }

    void Clear()
    {
        if (_Rear != nullptr)
        {
            Node<T> *pointer = _Rear->Next;
            while (pointer != _Rear)
            {
                Node<T> *tmp = pointer->Next;
                delete pointer;
                pointer = tmp;
            }
            delete _Rear;
            _Rear = nullptr;
        }
        _Length = 0;
    }

    void Traverse(std::function<void(const T&)> func) const
    {
        Node<T> *pointer = _Rear;
        while ((pointer = pointer->Next) != _Rear)
        {
            func(pointer->Data);
        }
        func(pointer->Data);
    }

    void EnQueue(T item)
    {
        if (_Rear == nullptr)
        {
            _Rear = new Node<T>;
            _Rear->Data = item;
            _Rear->Next = _Rear;
        }
        else
        {
            Node<T>* newNode = new Node<T>;
            newNode->Data = item;
            newNode->Next = _Rear->Next;
            _Rear->Next = newNode;
            _Rear = newNode;
        }
        _Length++;
    }

    T DeQueue()
    {
        if (_Rear != nullptr)
        {
            T ret = _Rear->Next->Data;
            if (_Rear->Next == _Rear)
            {
                delete _Rear;
                _Rear = nullptr;
            }
            else
            {
                Node<T> *newHead = _Rear->Next->Next;
                delete _Rear->Next;
                _Rear->Next = newHead;
            }
            _Length--;
            return ret;
        }
        throw std::underflow_error("Empty queue");
    }

    T& Head() const
    {
        if (_Rear != nullptr)
        {
            return _Rear->Next->Data;
        }
        throw std::underflow_error("Empty queue");
    }
};

#endif
