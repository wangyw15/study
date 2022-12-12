#ifndef SEQQUEUE
#define SEQQUEUE

#include <ios>
#include <functional>

template <typename T>
class SeqQueue
{
protected:
    T* _Data = nullptr;
    T* _Head = nullptr;
    long _Capacity = 0;
    long _Length = 0;
    std::function<std::ostream&(std::ostream&, SeqQueue<T>&)> _Printer = _DefaultPrinter;

    static std::ostream& _DefaultPrinter(std::ostream& out, SeqQueue<T>& stack)
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
    SeqQueue(long capacity = 100)
    {
        _Capacity = capacity;
        _Data = new T[capacity];
        _Head = nullptr;
        _Length = 0;
    }

    virtual ~SeqQueue()
    {
        delete[] _Data;
        _Data = nullptr;
        _Head = nullptr;
        _Capacity = 0;
        _Length = 0;
    }
};

#endif
