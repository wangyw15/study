#ifndef CROSSLINK
#define CROSSLINK

#include <ios>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

template <typename T> struct CrossNode
{
    T Data;
    int Row;
    int Column;
    CrossNode *Right;
    CrossNode *Down;

    CrossNode()
    {
        Data = 0;
        Right = Down = nullptr;
        Row = Column = 0;
    }

    CrossNode(T data)
    {
        Data = data;
        Right = Down = nullptr;
        Row = Column = 0;
    }
};

template <typename T> class CrossList
{
  protected:
    CrossNode<T> *_Start = nullptr;
    int _Rows, _Columns, _Count;

  public:
    CrossList(int row = 3, int column = 3)
    {
        _Rows = row;
        _Columns = column;
        _Count = 0;
        _Start = new CrossNode<T>;

        CrossNode<T> *pointer = _Start;
        for (int i = 0; i < column; i++)
        {
            CrossNode<T> *node = new CrossNode<T>;
            pointer->Right = node;
            pointer = node;
        }
        pointer = _Start;
        for (int i = 0; i < row; i++)
        {
            CrossNode<T> *node = new CrossNode<T>;
            pointer->Down = node;
            pointer = node;
        }
    }

    CrossList(const CrossList<T>& other) { *this = other; }

    CrossList<T>& operator=(const CrossList<T>& other)
    {
        if (this == &other)
        {
            return *this;
        }

        CrossNode<T> *otherRow = other._Start, *otherCol = nullptr,
                     *pointer = nullptr, *tmp = nullptr;

        // clear all
        if (_Start != nullptr)
        {
            Clear(true);
        }
        else
        {
            _Start = new CrossNode<T>;
        }

        // recreate heads
        pointer = _Start;
        for (int i = 0; i < other._Columns; i++)
        {
            CrossNode<T> *node = new CrossNode<T>;
            pointer->Right = node;
            pointer = node;
        }
        pointer = _Start;
        for (int i = 0; i < other._Rows; i++)
        {
            CrossNode<T> *node = new CrossNode<T>;
            pointer->Down = node;
            pointer = node;
        }
        
        // copy data
        _Columns = other._Columns;
        _Rows = other._Rows;
        _Count = other._Count;

        pointer = _Start->Right;

        while ((otherRow = otherRow->Down) != nullptr)
        {
            otherCol = otherRow;
            while ((otherCol = otherCol->Right) != nullptr)
            {
                Set(otherCol->Row, otherCol->Column, otherCol->Data);
            }
        }
        return *this;
    }

    virtual ~CrossList()
    {
        Clear(true);
    }

    void Clear(bool deleteHeads = false)
    {
        CrossNode<T> *row = _Start, *col;
        while ((row = row->Down) != nullptr)
        {
            col = row->Right;
            while (col != nullptr)
            {
                CrossNode<T> *ctmp = col->Right;
                delete col;
                col = ctmp;
            }
            row->Right = nullptr;
        }
        col = _Start;
        while ((col = col->Right) != nullptr)
        {
            col->Down = nullptr;
        }
        _Count = 0;

        CrossNode<T> *pointer = _Start->Right, *tmp = nullptr;
        if (deleteHeads)
        {
            // clear horizontal heads
            while (pointer != nullptr)
            {
                tmp = pointer->Right;
                delete pointer;
                pointer = tmp;
            }
            // clear vertical heads
            pointer = _Start->Down;
            while (pointer != nullptr)
            {
                tmp = pointer->Down;
                delete pointer;
                pointer = tmp;
            }
        }
    }

    void Set(int row, int column, T value)
    {
        if (row >= _Rows || column >= _Columns || row < 0 || column < 0)
        {
            throw std::range_error("Out of range");
        }
        if (value == 0) // delete specified element
        {
            CrossNode<T> *pointer = _Start->Down, *prev;
            for (int i = 0; i < row; i++)
            {
                pointer = pointer->Down;
            }
            prev = pointer;
            pointer = pointer->Right;
            while (pointer != nullptr)
            {
                if (pointer->Column == column)
                {
                    prev->Right = pointer->Right;
                    delete pointer;
                    return;
                }
                prev = prev->Right;
                pointer = pointer->Right;
            }
        }
        else // add a node or modify an existing node
        {
            CrossNode<T> *rowHead = _Start->Down, *colHead = _Start->Right;
            for (int i = 0; i < row; i++)
            {
                rowHead = rowHead->Down;
            }
            for (int i = 0; i < column; i++)
            {
                colHead = colHead->Right;
            }

            // element exists
            bool horizontalInserted = false;
            CrossNode<T> *horizontalPointer = rowHead->Right,
                         *horizontalPrev = rowHead, *node = new CrossNode<T>;
            node->Data = value;
            node->Row = row;
            node->Column = column;
            while (horizontalPointer != nullptr)
            {
                if (horizontalPointer->Column == column)
                {
                    horizontalPointer->Data = value;
                    horizontalInserted = true;
                    return;
                }
                else if (horizontalPointer->Column > column)
                {
                    node->Right = horizontalPointer;
                    horizontalPrev->Right = node;
                    horizontalInserted = true;
                    break;
                }
                horizontalPointer = horizontalPointer->Right;
                horizontalPrev = horizontalPrev->Right;
            }
            if (!horizontalInserted)
            {
                node->Right = nullptr;
                horizontalPrev->Right = node;
                horizontalInserted = true;
            }

            bool verticalInserted = false;
            CrossNode<T> *verticalPointer = colHead->Down,
                         *verticalPrev = colHead;
            while (verticalPointer != nullptr)
            {
                if (verticalPointer->Row > row)
                {
                    node->Down = verticalPointer;
                    verticalPrev->Down = node;
                    verticalInserted = true;
                    break;
                }
                verticalPointer = verticalPointer->Down;
                verticalPrev = verticalPrev->Down;
            }
            if (!verticalInserted)
            {
                node->Down = nullptr;
                verticalPrev->Down = node;
                verticalInserted = true;
            }
            _Count++;
        }
    }

    void Transpose()
    {
        CrossNode<T> *row = _Start, *col = nullptr, *rtmp = nullptr,
                     *ctmp = nullptr;
        int ntmp = 0;
        while (row != nullptr)
        {
            rtmp = row->Down;
            col = row;
            while (col != nullptr)
            {
                ctmp = col->Right;

                // exchange pointer
                col->Right = col->Down;
                col->Down = ctmp;
                // exchange coordinate
                ntmp = col->Row;
                col->Row = col->Column;
                col->Column = ntmp;

                col = ctmp;
            }
            row = rtmp;
        }

        // exchange _Rows and _Columns
        ntmp = _Rows;
        _Rows = _Columns;
        _Columns = ntmp;
    }

    CrossList<T> &operator+(const CrossList<T> &other)
    {
        if (_Rows == other._Rows && _Columns == other._Columns)
        {
            CrossList<T> *ret = new CrossList<T>;
            CrossNode<T> *rHere = _Start->Down,
                *cHere = rHere->Right,
                *rThere = other._Start->Down,
                *cThere = rThere->Right;

            *ret = *this;

            for (int i = 0; i < _Rows; i++)
            {
                for (int j = 0; j < _Columns; j++)
                {
                    T here = 0;
                    T there = 0;
                    if (cHere != nullptr && cHere->Row == i && cHere->Column == j)
                    {
                        here = cHere->Data;
                        cHere = cHere->Right;
                    }
                    if (cThere != nullptr && cThere->Row == i &&
                        cThere->Column == j)
                    {
                        there = cThere->Data;
                        cThere = cThere->Right;
                    }
                    ret->Set(i, j, here + there);
                }
                if (i != _Rows - 1)
                {
                    rHere = rHere->Down;
                    cHere = rHere->Right;
                    rThere = rThere->Down;
                    cThere = rThere->Right;
                }
            }

            return *ret;
        }
        else
        {
            throw std::length_error("Unmatched shape");
        }
    }

    friend std::ostream &operator<<(std::ostream &out, const CrossList<T> &mat)
    {
        out << std::string("----------") << std::endl;
        CrossNode<T> *row = mat._Start->Down, *cell = row->Right;

        for (int i = 0; i < mat._Rows; i++)
        {
            for (int j = 0; j < mat._Columns; j++)
            {
                if (cell != nullptr && cell->Row == i && cell->Column == j)
                {
                    out << cell->Data << " ";
                    cell = cell->Right;
                }
                else
                {
                    out << "0 ";
                }
            }
            if (i != mat._Rows - 1)
            {
                row = row->Down;
                cell = row->Right;
            }
            out << std::endl;
        }
        out << std::string("----------") << std::endl;
        return out;
    }
};

#endif
