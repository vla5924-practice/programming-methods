#ifndef _THEAP_H_
#define _THEAP_H_
#include <ciso646>

template<typename TData>
class THeap
{
public:
    int base;
    int capacity;
    int size;
    TData* elements;

    void transpose(int i, int j);
    int min(int first, int second) const;
    int findMinChild(int i) const;
    //void popUp(int i);
    void dipDown(int i);
    void heapify();
public:
    THeap(const THeap& other) = default;
    THeap(TData* elements_, int size_, int base_ = 2);
    ~THeap() = default;
    TData pullTop();
    void sort();
};

template<typename TData>
void THeap<TData>::transpose(int i, int j)
{
    TData temp = elements[i];
    elements[i] = elements[j];
    elements[j] = temp;
}

template<typename TData>
inline int THeap<TData>::min(int first, int second) const
{
    return first < second ? first : second;
}

template<typename TData>
int THeap<TData>::findMinChild(int i) const
{
    if (i * base + 1 >= size)
        return -1;
    int firstChild, lastChild, minChild;
    firstChild = i * base + 1;
    lastChild = min(size - 1, i * base + base);
    minChild = firstChild;
    for (int i = firstChild + 1; i <= lastChild; i++)
        if (elements[i] < elements[minChild])
            minChild = i;
    return minChild;

}

template<typename TData>
void THeap<TData>::dipDown(int i)
{
    int minChild = findMinChild(i);
    while ((minChild != -1) and (elements[minChild] < elements[i]))
    {
        transpose(i, minChild);
        i = minChild;
        minChild = findMinChild(i);
    }
}

template<typename TData>
void THeap<TData>::heapify()
{
    for (int i = size - 1; i >= 0; i--)
    {
        dipDown(i);
    }
}

template<typename TData>
THeap<TData>::THeap(TData* elements_, int size_, int base_)
{
    capacity = size_;
    size = size_;
    elements = elements_;
    base = base_;
    heapify();
}

template<typename TData>
TData THeap<TData>::pullTop()
{
    TData element = elements[0];
    transpose(0, size - 1);
    dipDown(0);
    size--;
    return element;
}

template<typename TData>
void THeap<TData>::sort()
{
    heapify();
    int realSize = size;
    int i = size - 1;
    while (size > 1)
    {
        transpose(0, size - 1);
        size--;
        dipDown(0);
        i--;
    }
    size = realSize;
}

#endif