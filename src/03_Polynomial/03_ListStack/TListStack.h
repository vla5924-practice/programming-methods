#ifndef _TLISTSTACK_H_
#define _TLISTSTACK_H_

#include "TStack.h"
#include "TList.h"

template <typename ValueType>
class TListStack : public TStack<ValueType>
{
    typedef TList<ValueType, void*> TListS;
    typedef typename TListS::TPair TPairS;
    typedef typename TListS::TNode TNodeS;
    TListS* list;
public:
    TListStack();
    TListStack(const TListStack& other);
    ~TListStack();

    void push(ValueType value);
    ValueType top() const;
    void pop();

    size_t height() const;
    bool empty() const;
    bool full() const;
};


template<typename ValueType>
TListStack<ValueType>::TListStack()
{
    list = new TListS();
}

template<typename ValueType>
TListStack<ValueType>::TListStack(const TListStack& other)
{
    list = new TListS();
    *list = *(other.list);
}

template<typename ValueType>
TListStack<ValueType>::~TListStack()
{
    delete list;
}

template<typename ValueType>
void TListStack<ValueType>::push(ValueType value)
{
    if (full())
        throw TStack<ValueType>::FullError();
    list->insertToStart(value);
}

template<typename ValueType>
ValueType TListStack<ValueType>::top() const
{
    if (empty())
        throw TStack<ValueType>::EmptyError();
    TPairS first = list->getFirst();
    return first.key;
}

template<typename ValueType>
void TListStack<ValueType>::pop()
{
    if (empty())
        throw TStack<ValueType>::EmptyError();
    TPairS first = list->getFirst();
    list->remove(first.key);
}

template<typename ValueType>
size_t TListStack<ValueType>::height() const
{
    return list->size();
}

template<typename ValueType>
bool TListStack<ValueType>::empty() const
{
    return list->empty();
}

template<typename ValueType>
bool TListStack<ValueType>::full() const
{
    TNodeS* node = new TNodeS;
    if (node)
    {
        delete node;
        return false;
    }
    else
        return true;
}

#endif // !_TLISTSTACK_H_