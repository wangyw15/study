#ifndef MATRIX
#define MATRIX

#include <algorithm>
#include <ios>
#include <stdexcept>
#include <string>
#include <iostream>

template <typename T>
struct Triple
{
    int Row, Col;
    T Value;

    Triple(){};

    Triple(int row, int col, T value)
    {
        Row = row;
        Col = col;
        Value = value;
    }

    bool operator<(const Triple<T> &other)
    {
        return Value < other.Value;
    }

    bool operator>(const Triple<T> &other)
    {
        return Value > other.Value;
    }

    bool operator<=(const Triple<T> &other)
    {
        return Value <= other.Value;
    }

    bool operator>=(const Triple<T> &other)
    {
        return Value >= other.Value;
    }
};


template <typename T> class TriSparseMatrix
{
protected:
    int _Rows, _Columns, _Count;
    Triple<T>* _Data;

public:
    TriSparseMatrix(int row = 10, int column = 10)
    {
        _Rows = row;
        _Columns = column;
        _Count = 0;
        _Data = new Triple<T>[row * column];
    }

    TriSparseMatrix(const Triple<T> &other)
    {
        *this = other;
    }

    TriSparseMatrix &operator=(const Triple<T> &other)
    {
        if (&other != this)
        {
            delete [] _Data;
            _Rows = other._Rows;
            _Columns = other._Columns;
            _Count = other._Count;
            _Data = new Triple<T>[_Rows * _Columns];
            for (auto i = 0; i < _Count; i++)
            {
                _Data[i] = other._Data[i];
            }
        }
    }

    virtual ~TriSparseMatrix()
    {
        delete[] _Data;
        _Rows = _Columns = _Count = 0;
    }
    
    int Rows() const
    {
        return _Rows;
    }

    int Columns() const
    {
        return _Columns;
    }

    int Count()
    {
        return _Count;
    }

    void Set(int row, int column, T value)
    {
        if (value == 0)
        {
            return;
        }
        int i = 0;
        for (i = 0; i < _Count; i++)
        {
            if (_Data[i].Row == row && _Data[i].Col == column)
            {
                _Data[i].Value = value;
                return;
            }
            if (row * _Columns + column < _Data[i].Row * _Columns + _Data[i].Col)
            {
                break;
            }
        }

        for (int j = _Count; j > i; j--)
        {
            _Data[j] = _Data[j - 1];
        }
        _Data[i] = Triple<T>(row, column, value);
        _Count++;
    }

    void Transpose()
    {
        if (_Count == 0)
        {
            return;
        }

        TriSparseMatrix<T> *ret = new TriSparseMatrix<T>(_Columns, _Rows);
        ret->_Count = _Count;

        int count[_Columns], pos[_Columns];
        for (int i = 0; i < _Columns; i++)
        {
            count[i] = pos[i] = 0;
        }
        for (int i = 0; i < _Count; i++)
        {
            count[_Data[i].Col]++;
        }
        for (int i = 1; i < _Columns; i++)
        {
            pos[i] = count[i - 1] + pos[i - 1];
        }
        for (int i = 0; i < _Count; i++)
        {
            int j = pos[_Data[i].Col]++;
            ret->_Data[j].Row = _Data[i].Col;
            ret->_Data[j].Col = _Data[i].Row;
            ret->_Data[j].Value = _Data[i].Value;
        }
        *this = *ret;
    }
    
    TriSparseMatrix<T> &operator+(const TriSparseMatrix<T> &other)
    {
        if (_Rows == other._Rows && _Columns == other._Columns)
        {
            TriSparseMatrix<T> *ret = new TriSparseMatrix<T>;
            *ret = *this;
            int iHere = 0, iThere = 0;
            for (auto row = 0; row < _Rows; row++)
            {
                for (auto col = 0; col < _Columns; col++)
                {
                    T here = 0;
                    T there = 0;
                    if (iHere < _Count && _Data[iHere].Row == row && _Data[iHere].Col == col)
                    {
                        here = _Data[iHere++].Value;
                    }
                    if (iThere < other._Count && other._Data[iThere].Row == row && other._Data[iThere].Col == col)
                    {
                        there = other._Data[iThere++].Value;
                    }
                    ret->Set(row, col, here + there);
                }
            }
            return *ret;
        }
        else
        {
            throw std::length_error("Unmatched shape");
        }
    }

    friend std::ostream& operator<< (std::ostream& out, TriSparseMatrix<T>& mat)
    {
        out << std::string("----------") << std::endl;
        int i = 0;

        for (auto row = 0; row < mat._Rows; row++)
        {
            for (auto col = 0; col < mat._Columns; col++)
            {
                if (i < mat._Count && mat._Data[i].Row == row && mat._Data[i].Col == col)
                {
                    out << mat._Data[i++].Value << " ";
                }
                else
                {
                    out << "0 ";
                }
            }
            out << std::endl;
        }
        out << std::string("----------");
        return out;
    }
};

#endif
