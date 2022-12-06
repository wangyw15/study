#ifndef SINGLELINKLIST
#define SINGLELINKLIST

#include <functional>
#include <algorithm>
#include <ios>

template <typename T>
struct Node
{
	T data;
	Node* next;
};

template <typename T>
class SingleLinkList
{
protected:
	Node<T>* _head;
	int _length;
	std::function<std::ostream& (std::ostream&, SingleLinkList<T>&)> _printer;

	static std::ostream& _DefaultPrinter(std::ostream& out, SingleLinkList<T>& list)
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

public:
	SingleLinkList()
	{
		_head = new Node<T>;
		// _head->data = NULL;
		_head->next = nullptr;
		_length = 0;
		SetPrintMethod();
	}

	SingleLinkList(T arr[], int n, bool sortData = false)
	{
		if (sortData)
		{
			std::sort(arr, arr + n);
		}

		_head = new Node<T>;
		// _head->data = NULL;

		_length = n;
		auto pointer = _head;
		for (auto i = 0; i < n; i++)
		{
			auto current = new Node<T>;
			current->data = arr[i];
			current->next = nullptr;
			
			pointer->next = current;
			pointer = current;
		}
		SetPrintMethod();
	}

	~SingleLinkList()
	{
		Clear();
		delete _head;
	}

	int Length() const
	{
		return _length;
	}

	Node<T>* Head()
	{
		return _head;
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
		if (n < _length)
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

	void Reverse()
	{
		if (_length >= 1)
		{
			Node<T>* pointer = _head->next;
			Node<T>* previous = nullptr;
			Node<T>* temp = nullptr;
			while (pointer != nullptr)
			{
				temp = pointer;
				pointer = pointer->next;
				temp->next = previous;
				previous = temp;
			}
			_head->next = previous;
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
				if (pointer->data > pointer->next->data)
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
		_length++;

		while (pointer->next != nullptr)
		{
			if (pointer->next->data >= item)
			{
				node->next = pointer->next;
				pointer->next = node;
				return;
			}
			pointer = pointer->next;
		}
		pointer->next = node;
	}

	void MergeByOrder(SingleLinkList& list)
	{
		Sort();
		list.Sort();

		auto newLength = _length + list._length;

		Node<T>* newHead = new Node<T>;
		// newHead->data = NULL;
		newHead->next = nullptr;

		Node<T>* pointer = newHead;
		Node<T>* listPointer = list._head->next;
		Node<T>* selfPointer = _head->next;

		for (auto i = 0; i < newLength; i++)
		{
			if (listPointer == nullptr)
			{
				T data(selfPointer->data);
				Node<T>* node = new Node<T>;
				node->data = data;
				node->next = nullptr;

				pointer->next = node;
				pointer = node;
				selfPointer = selfPointer->next;
			}
			else if (selfPointer == nullptr)
			{
				T data(listPointer->data);
				Node<T>* node = new Node<T>;
				node->data = data;
				node->next = nullptr;

				pointer->next = node;
				pointer = node;
				listPointer = listPointer->next;
			}
			else if (listPointer != nullptr && selfPointer != nullptr)
			{
				if (selfPointer->data < listPointer->data)
				{
					T data(selfPointer->data);
					Node<T>* node = new Node<T>;
					node->data = data;
					node->next = nullptr;

					pointer->next = node;
					pointer = node;
					selfPointer = selfPointer->next;
				}
				else
				{
					T data(listPointer->data);
					Node<T>* node = new Node<T>;
					node->data = data;
					node->next = nullptr;

					pointer->next = node;
					pointer = node;
					listPointer = listPointer->next;
				}
			}
		}

		Clear();
		_head = newHead;
		_length = newLength;
	}

	void SetPrintMethod(std::function<std::ostream& (std::ostream&, SingleLinkList<T>&)> printer = _DefaultPrinter)
	{
		_printer = printer;
	}

	friend std::ostream& operator<< (std::ostream& out, SingleLinkList<T>& list)
	{
		/*out << "[ ";
		Node<T>* pointer = list._head;
		while ((pointer = pointer->next) != nullptr)
		{
			out << pointer->data << (pointer->next != nullptr ? ", " : "");
		}
		out << " ]";
		return out;*/
		return list._printer(out, list);
	}
};

#endif