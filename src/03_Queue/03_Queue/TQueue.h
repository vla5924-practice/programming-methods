#ifndef _TQUEUE_H_
#define _TQUEUE_H_

template <typename ValueType>
class TQueue
{
	ValueType* elements;
	size_t size, count;
	size_t li, hi;
	size_t getNextIndex(size_t index) const;
public:
	explicit TQueue(size_t size = 0);
	TQueue(const TQueue& other);
	~TQueue();

	TQueue& push(ValueType value);
	ValueType pop();
	ValueType last() const;

	bool empty() const;
	bool full() const;
	size_t length() const;
	size_t capacity() const;
};

template<typename ValueType>
size_t TQueue<ValueType>::getNextIndex(size_t index) const
{
	return (index + 1) % size;
}

template<typename ValueType>
TQueue<ValueType>::TQueue(size_t size) : size(size)
{
	count = 0;
	li = 0;
	hi = size - 1;
	elements = size ? new ValueType[size] : nullptr;
}

template<typename ValueType>
TQueue<ValueType>::TQueue(const TQueue& other) : size(other.size), count(other.count), li(other.li), hi(other.hi)
{
	elements = size ? new ValueType[size] : nullptr;
	for (size_t i = 0; i < size; i++)
		elements[i] = other.elements[i];
}

template<typename ValueType>
TQueue<ValueType>::~TQueue()
{
	if (size > 0)
		delete[] elements;
}

template<typename ValueType>
TQueue<ValueType>& TQueue<ValueType>::push(ValueType value)
{
	if (full())
		throw "olala";
	elements[hi = getNextIndex(hi)] = value;
	count++;
	return *this;
}

template<typename ValueType>
ValueType TQueue<ValueType>::pop()
{
	if(empty())
		throw "olala";
	ValueType temp = elements[li];
	li = getNextIndex(li);
	count--;
	return temp;
}

template<typename ValueType>
ValueType TQueue<ValueType>::last() const
{
	if (empty())
		throw "olala";
	return elements[li];
}

template<typename ValueType>
bool TQueue<ValueType>::empty() const
{
	return count == 0;
}

template<typename ValueType>
bool TQueue<ValueType>::full() const
{
	return count == size;
}

template<typename ValueType>
size_t TQueue<ValueType>::length() const
{
	return count;
}

template<typename ValueType>
size_t TQueue<ValueType>::capacity() const
{
	return size;
}

#endif // !_TQUEUE_H_