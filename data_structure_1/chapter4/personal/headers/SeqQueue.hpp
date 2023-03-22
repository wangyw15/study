#ifndef SEQQUEUE
#define SEQQUEUE

#include <ios>
#include <functional>
#include <stdexcept>

template <typename T>
class SeqQueue
{
protected:
    T* _Data = nullptr;
    long _Head = 0;
    long _Capacity = 0;
    long _Length = 0;
    std::function<std::ostream&(std::ostream&, SeqQueue<T>&)> _Printer = _DefaultPrinter;

    static std::ostream& _DefaultPrinter(std::ostream& out, SeqQueue<T>& queue)
    {
        out << std::string("[ ");
        long index = queue._Head;
        for (long i = 0; i < queue._Length; i++)
        {
            out << queue._Data[index] << (i == queue._Length - 1 ? "" : ", ");
            index = (index + 1) % queue._Capacity;
        }
        out << std::string(" ]");
        return out;
    }

public:
    SeqQueue(long capacity = 100)
    {
        _Capacity = capacity;
        _Data = new T[capacity];
        _Head = 0;
        _Length = 0;
    }

    SeqQueue(const SeqQueue<T> &queue)
    {
        *this = queue;
    }

    SeqQueue<T> &operator=(const SeqQueue<T> &queue)
    {
        if (&queue != this)
        {
            if (_Data != nullptr)
            {
                delete[] _Data;
            }
            _Data = new T[queue._Capacity];
            _Capacity = queue._Capacity;
            _Head = queue._Head;
            _Length = queue._Length;
            for (long i = 0; i < _Capacity; i++)
            {
                _Data[i] = queue._Data[i];
            }
        }
        return *this;
    }

    virtual ~SeqQueue()
    {
        if (_Data != nullptr)
        {
            delete[] _Data;
            _Data = nullptr;
        }
        _Head = 0;
        _Capacity = 0;
        _Length = 0;
    }

    friend std::ostream& operator<<(std::ostream &out, SeqQueue<T> &queue)
    {
        return queue._Printer(out, queue);
    }

    void SetPrinter(std::function<std::ostream&(std::ostream&, SeqQueue<T>&)> printer = _DefaultPrinter)
    {
        _Printer = printer;
    }

    long Length() const
    {
        return _Length;
    }

    bool IsEmpty() const
    {
        return _Length == 0;
    }

    void Clear()
    {
        _Head = 0;
        _Length = 0;
    }

    void Traverse(std::function<void(const T&)> func) const
    {
        long index = _Head;
        for (long i = 0; i < _Length; i++)
        {
            func(_Data[index]);
            index = (index + 1) % _Capacity;
        }
    }

    void EnQueue(T item)
    {
        if (_Length < _Capacity)
        {
            _Data[(_Head + (_Length++)) % _Capacity] = item;
        }
        else
        {
            throw std::overflow_error("Overflow");
        }
    }

    T DeQueue()
    {
        if (_Length > 0)
        {
            long temp = _Head;
            _Head = (_Head + 1) % _Capacity;
            _Length--;
            return _Data[temp];
        }
        throw std::underflow_error("Empty queue");
    }

    T& Head() const
    {
        if (_Head >= 0)
        {
            return _Data[_Head];
        }
        throw std::underflow_error("Empty queue");
    }
};

#endif
