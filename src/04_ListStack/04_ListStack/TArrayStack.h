#ifndef _TARRAYSTACK_H_
#define _TARRAYSTACK_H_

#include "TStack.h"

template <typename ValueType>
class TArrayStack : public TStack<ValueType>
{
    size_t size;
    size_t nextEmpty;
    ValueType* elements;
public:
    explicit TArrayStack(size_t size = 0);
    TArrayStack(const TArrayStack& other);
    ~TArrayStack();

    void push(ValueType value);
    ValueType top() const;
    void pop();

    size_t height() const;
    size_t capacity() const;
    bool empty() const;
    bool full() const;
};


template<typename ValueType>
TArrayStack<ValueType>::TArrayStack(size_t size) : size(size)
{
    nextEmpty = 0;
    elements = size ? new ValueType[size] : nullptr;
}

template<typename ValueType>
TArrayStack<ValueType>::TArrayStack(const TArrayStack& other) : size(other.size), nextEmpty(other.nextEmpty)
{
    elements = size ? new ValueType[size] : nullptr;
    memcpy(elements, other.elements, size * sizeof(ValueType));
}

template<typename ValueType>
TArrayStack<ValueType>::~TArrayStack()
{
    if (elements)
        delete[] elements;
}

template<typename ValueType>
void TArrayStack<ValueType>::push(ValueType value)
{
    if (full())
        throw TStack<ValueType>::FullError();
    elements[nextEmpty++] = value;
}

template<typename ValueType>
ValueType TArrayStack<ValueType>::top() const
{
    if (empty())
        throw TStack<ValueType>::EmptyError();
    return elements[nextEmpty - 1];
}

template<typename ValueType>
void TArrayStack<ValueType>::pop()
{
    if (empty())
        throw TStack<ValueType>::EmptyError();
    nextEmpty--;
}

template<typename ValueType>
size_t TArrayStack<ValueType>::height() const
{
    return nextEmpty;
}

template<typename ValueType>
size_t TArrayStack<ValueType>::capacity() const
{
    return size;
}

template<typename ValueType>
bool TArrayStack<ValueType>::empty() const
{
    return nextEmpty == 0;
}

template<typename ValueType>
bool TArrayStack<ValueType>::full() const
{
    return nextEmpty == size;
}

#endif // !_TARRAYSTACK_H_