#ifndef MY_VECTOR
#define MY_VECTOR

#include <cstddef>
#include <cstring>
#include <iostream>

template <typename T> class Vector {
public:
  Vector() : _size(0), _data(nullptr) {}

  Vector(T *arr, std::size_t n) : _size(n) {
    _data = new T[_size];
    memcpy(_data, arr, _size * sizeof(T));
  }

  ~Vector() {
    delete[] _data;
    _size = 0;
  }

  Vector(const Vector &source) {
    delete[] _data;
    _size = source._size;
    _data = new T[_size];
    memcpy(_data, source._data, _size * sizeof(T));
  }

  Vector &operator=(const Vector &source) {
    if (&source == this) {
      return *this;
    }
    delete[] _data;
    _size = source._size;
    _data = new T[_size];
    memcpy(_data, source._data, _size * sizeof(T));
    return *this;
  }

  T &operator[](int n) { return _data[n]; }

  void Push(T item) {
    if (_size != 0) {
      T *temp = _data;
      _data = new T[++_size];
      memcpy(_data, temp, (_size - 1) * sizeof(T));
      _data[_size - 1] = item;
      delete[] temp;
    } else {
      _data = new T[_size++];
      _data[0] = item;
    }
  }

  void Remove(int n) {
    if (_size == 0) {
      throw "Empty vector";
    } else {
      T *temp = _data;
      _data = new T[--_size];
      memcpy(_data, temp, n * sizeof(T));
      memcpy(_data + n, temp + n + 1, (_size - n) * sizeof(T));
    }
  }

  std::size_t Size() { return _size; }

private:
  T *_data;
  int _size;
};

#endif