#include<bits/stdc++.h>
using namespace std;

  class Vector
 {
 	public:
 	  Vector():_size(0), _data(NULL) {} //创建一个空vector
 	
 	  Vector(double *arr, size_t n):_size(n) //创建一个vector,元素个数为nSize
 	  {
 	  	_data = new double[_size];
 	  	memcpy(_data, arr, _size * sizeof(double));
	  }

    Vector(const Vector &source, int begin, int end):_size(end - begin + 1)
    {
      _data = new double[_size];
      memcpy(_data,source._data,_size* sizeof(double));//复制source中[begin,end]区间内数组的元素到vector中
    }
	  
    Vector(size_t n, const double &x):_size(n) //创建一个vector，元素个数为n,且值均为x
    {
      _data = new double[_size];
      for(int i = 0; i < _size; i++)
      {
        _data[i] = x;
      }
    }
	  Vector(const Vector &source) //复制构造函数
      {
    
       _size = source._size;
       _data = new double[_size];
       memcpy(_data, source._data, _size * sizeof(double));
      }
 	
 	  ~Vector() //析构函数
      {
        delete[] _data;
        _size = 0;
      }
      
    Vector &operator=(const Vector &source) //深赋值运算函数
      {
        if (&source == this) 
		{
        return *this;
        }
        delete[] _data;
        _size = source._size;
        _data = new double[_size];
        memcpy(_data, source._data, _size * sizeof(double));
        return *this;
     }

    double &operator[](int n) 
    { 
      if(n >= _size)
      {
        throw "Out of range";
      }
      return _data[n]; 
    }

    void Push(double item) //向量尾部增加一个元素item
      {
        if (_size != 0) 
        {
        double *temp = _data;
        _data = new double[++_size];
        memcpy(_data, temp, (_size - 1) * sizeof(double));
        _data[_size - 1] = item;
        delete[] temp;
        } 
       else 
	      {
        _data = new double[_size++];
        _data[0] = item;
        }
     }

    void Insert(int index, const double &item) //在向量下标为index的元素前增加一个元素item
      {
        if(index < _size )
        {
          double *temp = _data;
          _data = new double[++_size];
          memcpy(_data, temp, index *sizeof(double));
          _data[index] = item;
          memcpy(_data + index + 1, temp + index, (_size - index - 1) *sizeof(double));
        }
        else throw "Out of range";
      }
    
    void Change(int index, const double &item) //将向量下标为index的元素更换为item
    {
      if(index < _size )
        {
          double *temp = _data;
          _data = new double[_size];
          memcpy(_data, temp, index *sizeof(double));
          _data[index] = item;
          memcpy(_data + index + 1, temp + index + 1, (_size - index - 1) *sizeof(double));
        }
        else throw "Out of range";
    }
 	
 	  void Remove(int n) //删除向量中下标为n的元素
      {
        if (_size != 0) 
		    {
          double *temp = _data;
          _data = new double[--_size];
          memcpy(_data, temp, n*sizeof(double) );
          memcpy(_data + n, temp + n + 1, (_size - n)* sizeof(double));
        } 
		    else 
		    {
          throw "Empth Vector";
        }
      }
    
    void Pop_back() //删除向量中最后一个元素
    {
      if (_size == 0)
      {
        throw "Empty vector";
      }
      else
      {
        double *temp = _data;
        _data = new double[--_size];
        memcpy(_data, temp, _size *sizeof(double));

      }
    }

    void clear()//清空向量中所有元素
    {
      _data = NULL;
      _size = 0;
    }
    
    bool empty() const
    {
      if (_data == NULL)
      {
        return true;
      }
      else return false;
    }
    
    size_t Size() { return _size; }//返回向量中元素的个数

    double Length() //求向量的模长
    {
      double len2 = 0;
      for (int i = 0; i < _size; i++)
      {
        len2 += _data[i] * _data[i];
      }
      return sqrt(len2);
    }

   friend void Swap( Vector &a, Vector &b)
    {
      Vector temp;
      temp = a;
      a = b;
      b = temp; 
    }

    friend double &operator*(const Vector &a, const Vector &b) //重载求向量内积的乘号
    {
      
      if ((a._size == 0) || (b._size == 0))
      {
        throw "Empty vector";
      }
      else if (a._size != b._size)
      {
        throw "Size of Vectors are different";
      }
      else
      {
        double sum = 0;
        for(int i = 0; i < a._size; i++)
        {
          sum += a._data[i] * b._data[i];
        }
        return sum;
      }
    }
   /*
    friend Vector operator+(const Vector &a, const Vector &b)//重载求向量内积的乘号
    {
      Vector temp;
      if ((a._size == 0) || (b._size == 0))
      {
        throw "Empty vector";
      }
      else if (a._size != b._size)
      {
        throw "Size of Vectors are different";
      }
      else
      {
        
        for(int i = 0; i < a._size; i++)
        {
          temp._data[i] = a._data[i] + b._data[i];
        }
        return temp;
      }
    }
    */
    Vector operator+(const Vector &b) //重载+
    {
      Vector temp(_size,0);
      if ((_size == 0) || (_size == 0))
      {
        throw "Empty vector";
      }
      else if (_size != b._size)
      {
        throw "Size of Vectors are different";
      }
      else
      {
        
        for(int i = 0; i < _size; i++)
        {
           temp._data[i] = _data[i] + b._data[i];
        }
        return temp;
      }
    }
    
    /*
   friend Vector operator-(const Vector &a, const Vector &b)//重载求向量内积的乘号
    {
      Vector temp;
      if ((a._size == 0) || (b._size == 0))
      {
        throw "Empty vector";
      }
      else if (a._size != b._size)
      {
        throw "Size of Vectors are different";
      }
      else
      {
      
        for(int i = 0; i < a._size; i++)
        {
          temp._data[i] = a._data[i] - b._data[i];
        }
        return temp;
      }
    }*/

    Vector operator-(const Vector &b) //重载-
   {
      Vector temp(_size,0);
      if ((_size == 0) || (b._size == 0))
      {
        throw "Empty vector";
      }
      else if (_size != b._size)
      {
        throw "Size of Vectors are different";
      }
      else
      {
         for(int i = 0; i < _size; i++)
        {
          temp._data[i] =_data[i] - b._data[i];
        }
        return temp;
      }
   }
   
  friend ostream &operator<<(ostream &output, const Vector &A) //重载<<
  {
    if (A._size != 0)
    {
    output << "(";
    for (int i = 0; i < A._size - 1; i++)
        output << A._data[i] << ", ";
    output << A._data[A._size - 1];
    output << ")" << endl;
    return output;
    }
    else cout << "Empty Vector" << endl;
  }

   void Show()
   {
     cout << "(";
     for (int i = 0; i < _size; i++)
    {
       if(i<_size-1)
            cout << _data[i] << ", ";
       else cout << _data[i] ;
    }
    cout << ")" << endl;
   }
 	
 	private:
 	  double *_data;
 	  int _size;
 	
 };
