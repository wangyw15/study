#ifndef SEQSTACK
#define SEQSTACK

#include <ostream>
#include <string>
#include <functional>

template <typename T>
class SeqStack
{
protected:
    T* _Data = nullptr;
    long _Capacity = 0;
    long _Top = -1;
    std::function<std::ostream&(std::ostream&, SeqStack<T>&)> _Printer = _DefaultPrinter;

    // stackfull
    void _Expand()
    {
        T* newData = new T[_Capacity * 2];
        for (long i = 0; i < _Top + 1; i++)
        {
            newData[i] = _Data[i];
        }
        delete [] _Data;
        _Data = newData;
        _Capacity *= 2;
    }
    
    static std::ostream& _DefaultPrinter(std::ostream& out, SeqStack<T>& stack)
    {
        out << std::string("[ ");
        for (long i = stack._Top; i >= 0; i--)
        {
            out << (stack._Data[i]) << (i == 0 ? "" : ", ");
        }
        out << std::string(" ]");
        return out;
    }

public:
    SeqStack(long capacity = 100)
    {
        if (_Data != nullptr)
        {
            delete[] _Data;
        }
        _Data = new T[capacity];
        _Capacity = capacity;
        _Top = -1;
    }

    SeqStack(const SeqStack<T> &stack)
    {
        *this = stack;
    }

    SeqStack<T> &operator=(const SeqStack<T> &stack)
    {
        if (&stack != this)
        {
            _Top = stack._Top;
            _Printer = stack._Printer;
            _Capacity = stack._Capacity;
            _Data = new T[_Capacity];

            for (long i = _Top; i >= 0; i--)
            {
                _Data[i] = stack._Data[i];
            }
        }
        return *this;
    }

    virtual ~SeqStack()
    {
        delete[] _Data;
        _Capacity = 0;
        _Top = -1;
    }

    void Clear()
    {
        delete[] _Data;
        _Data = new T[_Capacity];
        _Top = -1;
    }

    bool IsEmpty() const
    {
        return _Top == -1;
    }

    long Length() const
    {
        return _Top + 1;
    }

    void Traverse(std::function<void(const T)> func) const
    {
        for (long i = _Top; i >= 0; i--)
        {
            func(_Data[i]);
        }
    }

    void Push(const T item)
    {
        if (_Top + 1 >= _Capacity)
        {
            _Expand();
        }
        _Data[++_Top] = item;
    }

    T Pop()
    {
        if (_Top - 1 >= 0)
        {
            return _Data[_Top--];
        }
        else
        {
            throw "Index out of range";
        }
    }

    T &Top() const
    {
        if (_Top >= 0)
        {
            return _Data[_Top];
        }
        else
        {
            throw "Empty stack";
        }
    }

    T &operator[](int n) const
    {
        if (n <= _Top && n >= 0)
        {
            return _Data[n];
        }
        else
        {
            throw "Index out of range";
        }
    }

    void SetPrinter(std::function<std::ostream&(std::ostream&, SeqStack<T>&)> printer = _DefaultPrinter)
    {
        _Printer = printer;
    }

    friend std::ostream& operator<<(std::ostream &out, SeqStack<T> &stack)
    {
        return stack._Printer(out, stack);
    }
};

#endif
