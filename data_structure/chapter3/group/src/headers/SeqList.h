#ifndef SEQLIST
#define SEQLIST

#include <iostream>

#define DEFAULT_SIZE 1000
#define DEFAULT_INFINITY 1000000

enum Status
{
    SUCCESS,
    FAIL,
    UNDER_FLOW,
    OVER_FLOW,
    RANGE_ERROR,
    DUPLICATE_ERROR,
    NOT_PRESENT,
    ENTRY_INSERTED,
    ENTRY_FOUND,
    VISITED,
    UNVISITED
};

template <typename ElemType> class SeqList
{
  protected:
    int length;
    int maxLength;
    ElemType *elems;

  public:
    SeqList(int size = DEFAULT_SIZE);
    SeqList(ElemType v[], int n, int size = DEFAULT_SIZE);

    virtual ~SeqList();

    int GetLength() const;
    bool IsEmpty() const;
    void Clear();
    void Traverse(void (*Visit)(const ElemType &)) const;
    int LocateElem(const ElemType &e) const;
    ElemType *GetElems() { return this->elems; };
    Status GetElem(int i, ElemType &e) const;
    Status SetElem(int i, const ElemType &e);
    Status DeleteElem(int i, ElemType &e);
    Status InsertElem(int i, const ElemType &e);
    void InsertElem(const ElemType &e);
    SeqList(const SeqList<ElemType> &sa);
    SeqList<ElemType> &operator=(const SeqList<ElemType> &sa);
    void Show(); // 显示

    ElemType max() const;
    ElemType min() const;

    void deleteByRank(int l, int r);
    void deleteRange(const ElemType &s, const ElemType &t);

    SeqList<ElemType> &merge(const SeqList<ElemType> &se);
};

template <class ElemType> SeqList<ElemType>::SeqList(int size)
{
    elems = new ElemType[size];
    maxLength = size;
    length = 0;
}

template <class ElemType>
SeqList<ElemType>::SeqList(ElemType v[], int n, int size)
{
    this->length = n;
    this->elems = new ElemType[size];
    this->maxLength = size;
    for (int i = 0; i <= this->length - 1; i++)
    {
        this->elems[i] = v[i];
    }
}

template <class ElemType> SeqList<ElemType>::~SeqList() { delete[] elems; }

template <class ElemType> int SeqList<ElemType>::GetLength() const
{
    return length;
}

template <class ElemType> bool SeqList<ElemType>::IsEmpty() const
{
    return length == 0;
}

template <class ElemType> void SeqList<ElemType>::Clear() { length = 0; }

template <class ElemType>
void SeqList<ElemType>::Traverse(void (*visit)(const ElemType &)) const
{
    for (int i = 0; i < length; i++)
    {
        (*visit)(elems[i]);
    }
}

template <class ElemType>
int SeqList<ElemType>::LocateElem(const ElemType &e) const
{
    int i = 0;
    while (i < length && elems[i] != e)
    {
        i++;
    }
    return i < length ? i + 1 : 0;
}

template <class ElemType>
Status SeqList<ElemType>::GetElem(int i, ElemType &e) const
{
    if (i < 1 || i > length)
    {
        return NOT_PRESENT;
    }
    else
    {
        e = elems[i - 1];
        return ENTRY_FOUND;
    }
}

template <class ElemType>
Status SeqList<ElemType>::SetElem(int i, const ElemType &e)
{
    if (i < 1 || i > length)
    {
        return RANGE_ERROR;
    }
    else
    {
        elems[i - 1] = e;
        return SUCCESS;
    }
}

template <class ElemType>
Status SeqList<ElemType>::DeleteElem(int i, ElemType &e)
{
    if (i < 1 || i > length)
    {
        return RANGE_ERROR;
    }
    else
    {
        e = elems[i - 1];
        for (int j = i; j < length; j++)
        {
            elems[j - 1] = elems[j];
        }
        length--;
        return SUCCESS;
    }
}

template <class ElemType>
Status SeqList<ElemType>::InsertElem(int i, const ElemType &e)
{
    if (length == maxLength)
    {
        return OVER_FLOW;
    }
    else if (i < 1 || i > length + 1)
    {
        return RANGE_ERROR;
    }
    else
    {
        for (int j = length; j >= i; j--)
        {
            elems[j] = elems[j - 1];
        }
        elems[i - 1] = e;
        length++;
        return SUCCESS;
    }
}

template <class ElemType>
SeqList<ElemType>::SeqList(const SeqList<ElemType> &sa)
{
    *this = sa;
}

template <class ElemType>
SeqList<ElemType> &SeqList<ElemType>::operator=(const SeqList<ElemType> &sa)
{
    if (&sa != this)
    {
        this->elems = new ElemType[sa.maxLength];
        this->length = sa.length;
        this->maxLength = sa.maxLength;
        for (int i = 0; i <= this->length - 1; i++)
        {
            this->elems[i] = sa.elems[i];
        }
    }
    return *this;
}

template <typename ElemType> inline void SeqList<ElemType>::Show()
{
    for (int i = 0; i <= this->length - 1; i++)
    {
        std::cout << this->elems[i] << " ";
    }
}

template <typename ElemType> inline ElemType SeqList<ElemType>::max() const
{
    if (this->elems == nullptr)
    {
        return -1;
    }
    int rank = 0;
    ElemType max = this->elems[0];
    for (int i = 0; i <= this->length - 1; i++)
    {
        if (this->elems[i] > max)
        {
            max = this->elems[i];
            rank = i;
        }
    }
    return rank + 1;
}

template <typename ElemType> inline ElemType SeqList<ElemType>::min() const
{
    if (this->elems == nullptr)
    {
        return -1;
    }
    int rank = 0;
    ElemType min = this->elems[0];
    for (int i = 0; i <= this->length - 1; i++)
    {
        if (this->elems[i] < min)
        {
            min = this->elems[i];
            rank = i;
        }
    }
    return rank + 1;
}

template <class ElemType> void SeqList<ElemType>::InsertElem(const ElemType &e)
{
    if (length == maxLength)
    {
        return;
    }
    else if (this->length == 0)
    {
        this->elems[0] = e;
        this->length += 1;
        return;
    }
    else
    {
        int rank = this->length - 1, i;         // 记录插入位置
        for (i = 0; i <= this->length - 1; i++) // 找到位置
        {
            if (this->elems[i] > e)
            {
                rank = i;
                break;
            }
        }
        for (int j = this->length - 1; j >= i; j--) // 移位
        {
            this->elems[j + 1] = this->elems[j];
        }
        this->elems[i] = e; // 插入
        this->length += 1;
    }
}

template <typename ElemType>
inline void SeqList<ElemType>::deleteByRank(int l, int r) // 辅助函数
{
    while (r <= this->length - 1)
    {
        this->elems[l++] = this->elems[r++];
    }
    this->length -= r - l;
}

template <typename ElemType>
inline void SeqList<ElemType>::deleteRange(const ElemType &s,
                                           const ElemType &t) // 删除函数
{
    if (t > this->elems[this->length - 1] && s < this->elems[0])
    {
        this->length = 0;
        this->maxLength = 0;
        delete[] this->elems;
        this->elems = nullptr;
        return;
    }
    else if (s > this->elems[this->length - 1] || t < this->elems[0])
    {
        return;
    }
    else
    {
        int l, r;
        for (int i = 0; i <= this->length - 1;
             i++) // 找左位置（移动到达的位置）
        {
            if (this->elems[i] > s)
            {
                l = i;
                break;
            }
        }

        for (int i = this->length - 1; i >= 0; i--) // 找右位置(移动的位置)
        {
            if (this->elems[i] < t)
            {
                r = i + 1;
                break;
            }
        }

        if (l == 0)
        {
            deleteByRank(0, r);
        }
        else if (r > this->length - 1)
        {
            deleteByRank(l, this->length);
        }
        else
        {
            deleteByRank(l, r);
        }
    }
}

template <typename ElemType>
inline SeqList<ElemType> &SeqList<ElemType>::merge(const SeqList<ElemType> &se)
{
    int i = 0, j = 0, k = 0;
    SeqList<ElemType> *s = new SeqList<ElemType>;
    s->maxLength = this->maxLength + se.maxLength;
    s->length = this->length + se.length;
    while (i <= this->length - 1 && j <= se.length - 1)
    {
        if (this->elems[i] <= se.elems[j])
        {
            s->elems[k++] = this->elems[i++];
        }
        else
        {
            s->elems[k++] = se.elems[j++];
        }
    }
    while (i <= this->length - 1)
    {
        s->elems[k++] = this->elems[i++];
    }
    while (j <= se.length - 1)
    {
        s->elems[k++] = se.elems[j++];
    }
    return *s;
}

#endif
