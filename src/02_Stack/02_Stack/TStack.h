#ifndef _TSTACK_H_
#define _TSTACK_H_

#include <string>
#include <cstring>
#include <exception>

template <typename ValueType>
class TStack
{
	size_t size;
	size_t nextEmpty;
	ValueType* elements;
public:
	explicit TStack(size_t size = 0);
	TStack(const TStack& other);
	~TStack();

	TStack<ValueType>& push(ValueType value);
	ValueType top() const;
	void pop();

	size_t height() const;
	size_t capacity() const;
	bool empty() const;
	bool full() const;

	class FullError : std::exception
	{
		const std::string whatStr = "Stack is full.";
	public:
		virtual const char* what() { return whatStr.c_str(); }
	};
	class EmptyError : std::exception
	{
		const std::string whatStr = "Stack is empty.";
	public:
		virtual const char* what() { return whatStr.c_str(); }
	};
};


template<typename ValueType>
TStack<ValueType>::TStack(size_t size) : size(size)
{
	nextEmpty = 0;
	elements = size ? new ValueType[size] : nullptr;
}

template<typename ValueType>
TStack<ValueType>::TStack(const TStack& other) : size(other.size), nextEmpty(other.nextEmpty)
{
	elements = size ? new ValueType[size] : nullptr;
	memcpy(elements, other.elements, size * sizeof(ValueType));
}

template<typename ValueType>
TStack<ValueType>::~TStack()
{
	if (elements)
		delete[] elements;
}

template<typename ValueType>
TStack<ValueType>& TStack<ValueType>::push(ValueType value)
{
	if (full())
		throw FullError();
	elements[nextEmpty++] = value;
	return *this;
}

template<typename ValueType>
ValueType TStack<ValueType>::top() const
{
	if (empty())
		throw EmptyError();
	return elements[nextEmpty - 1];
}

template<typename ValueType>
void TStack<ValueType>::pop()
{
	if (empty())
		throw EmptyError();
	nextEmpty--;
}

template<typename ValueType>
size_t TStack<ValueType>::height() const
{
	return nextEmpty;
}

template<typename ValueType>
size_t TStack<ValueType>::capacity() const
{
	return size;
}

template<typename ValueType>
bool TStack<ValueType>::empty() const
{
	return nextEmpty == 0;
}

template<typename ValueType>
bool TStack<ValueType>::full() const
{
	return nextEmpty == size;
}

#endif // !_TSTACK_H_