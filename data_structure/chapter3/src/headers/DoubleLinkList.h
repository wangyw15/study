#ifndef DOUBLELINKLIST
#define DOUBLELINKLIST

#include <algorithm>
#include <ios>

template <typename T>
struct Node
{
	T data;
	Node* next;
	Node* prev;
};

template <typename T>
class DoubleLinkList
{
protected:
	Node<T>* _head;
	int _length;

public:
	DoubleLinkList()
	{
		_head = new Node<T>;
		// _head->data = NULL;
		_head->next = nullptr;
		_head->prev = nullptr;
		_length = 0;
	}

	DoubleLinkList(T arr[], int n, bool sortData = false)
	{
		if (sortData)
		{
			std::sort(arr, arr + n);
		}

		_head = new Node<T>;
		_head->prev = nullptr;

		_length = n;
		auto pointer = _head;
		for (auto i = 0; i < n; i++)
		{
			auto current = new Node<T>;
			current->data = arr[i];
			current->next = nullptr;
			current->prev = pointer;

			pointer->next = current;
			pointer = current;
		}
	}

	~DoubleLinkList()
	{
		Clear();
		delete _head;
	}

	int Length() const
	{
		return _length;
	}

	void Clear()
	{
		_length = 0;
		Node<T>* pointer = _head->next;
		while (pointer != nullptr)
		{
			Node<T>* temp = pointer->next;
			delete pointer;
			pointer = temp;
		}
		_length = 0;
	}

	T& operator[](int n) const
	{
		if (n < _size)
		{
			auto index = 0;
			Node<T>* pointer = _head;
			while ((pointer = pointer->next) != nullptr)
			{
				if (index++ == n)
				{
					return pointer->data;
				}
			}
			return nullptr;
		}
		else
		{
			return nullptr;
		}
	}

	void Sort()
	{
		Node<T>* pointer = _head->next;
		auto count = _length - 1;
		for (auto i = 0; i < _length - 1; i++)
		{
			pointer = _head->next;
			for (auto j = 0; j < _length - 1 - i; j++)
			{
				if (pointer->data < pointer->next->data)
				{
					auto temp = pointer->data;
					pointer->data = pointer->next->data;
					pointer->next->data = temp;
				}
				pointer = pointer->next;
			}
		}
	}

	void InsertByOrder(const T item)
	{
		Sort();
		auto n = 0;

		Node<T>* pointer = _head;
		Node<T>* node = new Node<T>;
		node->data = item;
		node->next = nullptr;
		_head->prev = nullptr;
		_length++;

		while (pointer->next != nullptr)
		{
			if (pointer->next->data <= item)
			{
				node->next = pointer->next;
				pointer->next = node;
				return;
			}
			pointer = pointer->next;
		}
		pointer->next = node;
	}

	void Swap()
	{
		Node<T>* pointer = _head;
		Node<T>* maxItem = _head->next;
		Node<T>* minItem = _head->next;
		while ((pointer = pointer->next) != nullptr)
		{
			if (pointer->data > maxItem->data)
			{
				maxItem = pointer;
			}
			if (pointer->data < minItem->data)
			{
				minItem = pointer;
			}
		}
		T temp = maxItem->data;
		maxItem->data = minItem->data;
		minItem->data = temp;
	}

	friend std::ostream& operator<< (std::ostream& out, DoubleLinkList<T>& list)
	{
		out << "[ ";
		Node<T>* pointer = list._head;
		while ((pointer = pointer->next) != nullptr)
		{
			out << pointer->data << (pointer->next != nullptr ? ", " : "");
		}
		out << " ]";
		return out;
	}
};

#endif
