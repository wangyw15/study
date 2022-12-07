#ifndef SEQLIST
#define SEQLIST

#include <algorithm>
#include <ios>
#define CAPACITY_STEP 100

template <typename T> class SeqList
{
protected:
	int _length;
	int _capacity;
	T* _data;

public:
	SeqList(int capacity = CAPACITY_STEP)
	{
		_data = new T[capacity];
		_length = 0;
		_capacity = capacity;
	}

	SeqList(T arr[], int n, int capacity = CAPACITY_STEP, bool sortData = false)
	{
		if (sortData)
		{
			std::sort(arr, arr + n);
		}
		_length = n;
		_capacity = std::max(n, capacity) + CAPACITY_STEP;
		_data = new T[_capacity];
		for (auto i = 0; i < n; i++)
		{
			_data[i] = arr[i];
		}
	}

	virtual ~SeqList()
	{
		delete[] _data;
		_length = 0;
		_capacity = 0;
	}

	int Length() const
	{
		return _length;
	}

	int Capacity() const
	{
		return _capacity;
	}

	int Max() const
	{
		auto max = _data[0];
		auto maxIndex = 0;
		for (auto i = 0; i < _length; i++)
		{
			if (_data[i] > max)
			{
				max = _data[i];
				maxIndex = i;
			}
		}
		return maxIndex;
	}

	int Min() const
	{
		auto min = _data[0];
		auto minIndex = 0;
		for (auto i = 0; i < _length; i++)
		{
			if (_data[i] < min)
			{
				min = _data[i];
				minIndex = i;
			}
		}
		return minIndex;
	}

	bool IsEmpty() const
	{
		return _length == 0;
	}

	void Clear()
	{
		_length = 0;
	}

	void Insert(const T item, const int n)
	{
		if (n <= _length)
		{
			if (_length + 1 > _capacity)
			{
				_capacity += CAPACITY_STEP;
				auto newList = new T[_capacity];
				auto inserted = false;
				for (auto i = 0; i < _length; i++)
				{
					newList[i + (inserted ? 1 : 0)] = _data[i];
					if (!inserted && i == n)
					{
						newList[i] = item;
						inserted = true;
					}
				}
				if (!inserted)
				{
					newList[n] = item;
					inserted = true;
				}
				delete[] _data;
				_data = newList;
			}
			else
			{
				for (auto i = _length - 1; i > n; i--)
				{
					_data[i] = _data[i - 1];
				}
				_data[n] = item;
			}
			_length++;
		}
		else
		{
			throw "You cannot insert a element at the position which is bigger than current size";
		}
	}

	void InsertByOrder(const T item)
	{
		std::sort(_data, _data + _length);
		if (_length + 1 > _capacity)
		{
			_capacity += CAPACITY_STEP;
			auto newList = new T[_capacity];
			auto inserted = false;
			for (auto i = 0; i < _length; i++)
			{
				if (!inserted && item < _data[i])
				{
					newList[i] = item;
					inserted = true;
				}
				newList[i + (inserted ? 1 : 0)] = _data[i];
			}
			if (!inserted)
			{
				newList[_length] = item;
			}
			delete[] _data;
			_data = newList;
		}
		else
		{
			for (auto i = 0; i < _length; i++)
			{
				if (item < _data[i])
				{
					for (auto j = _length - 1; j >= i; j--)
					{
						_data[j + 1] = _data[j];
					}
					_data[i] = item;
					_length++;
					return;
				}
			}
			_data[_length] = item;
		}
		_length++;
	}

	void DeleteRange(const T smallest, const T biggest)
	{
		// std::sort(_data, _data + _length);
		if (smallest > biggest)
		{
			throw "Invalid parameters";
		}
		auto newSize = 0;
		for (auto i = 0; i < _length; i++)
		{
			if (_data[i] < smallest || _data[i] > biggest)
			{
				_data[newSize++] = _data[i];
			}
		}
		_length = newSize;
	}

	void MergeByOrder(const SeqList<T>& list)
	{
		std::sort(_data, _data + _length);
		std::sort(list._data, list._data + list._length);

		auto newSize = _length + list._length;
		_capacity = newSize;
		auto newList = new T[newSize];
		auto listIndex = 0;
		auto selfIndex = 0;

		for (auto i = 0; i < newSize; i++)
		{
			if (listIndex >= list._length)
			{
				newList[i] = _data[selfIndex++];
			}
			else if (selfIndex >= _length)
			{
				newList[i] = list._data[listIndex++];
			}
			else if (selfIndex < _length && listIndex < list._length)
			{
				if (_data[selfIndex] < list._data[listIndex])
				{
					newList[i] = _data[selfIndex++];
				}
				else
				{
					newList[i] = list._data[listIndex++];
				}
			}
		}

		delete[] _data;
		_data = newList;
		_length = newSize;
	}

	T& operator[](const int n) const
	{
		if (n < _length)
		{
			return _data[n];
		}
		else
		{
			return NULL;
		}
	}

	friend std::ostream& operator<< (std::ostream& out, SeqList<T>& list)
	{
		out << "[ ";
		for (auto i = 0; i < list._length; i++)
		{
			out << list._data[i] << (i != list._length - 1 ? ", ": "");
		}
		out << " ]";
		return out;
	}
};

#endif