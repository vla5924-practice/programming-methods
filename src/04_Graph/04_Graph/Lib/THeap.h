#ifndef _THEAP_H_
#define _THEAP_H_
#include <ciso646>
#include <functional>

template<typename TData>
class THeap
{
public:
    typedef std::function<int(const TData&)> TWeightFunc;
    int base;
    int capacity;
    int size;
    int* keys;
    TData* elements;
    //int(*weight)(const TData&);
    TWeightFunc weight;

    void transpose(int i, int j);
    int min(int first, int second) const;
    int getWeight(int i) const;
    int findMinChild(int i) const;
    //void popUp(int i);
    void dipDown(int i);
    void heapify();
public:
    THeap(const THeap& other);
    THeap(TData* const elements_, int size_, TWeightFunc weight_, int base_ = 2);
    ~THeap();
    TData* pullTop();
    void sort();
};

template<typename TData>
void THeap<TData>::transpose(int i, int j)
{
    int temp = keys[i];
    keys[i] = keys[j];
    keys[j] = temp;
}

template<typename TData>
inline int THeap<TData>::min(int first, int second) const
{
    return first < second ? first : second;
}

template<typename TData>
inline int THeap<TData>::getWeight(int i) const
{
    return weight(elements[keys[i]]);
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
        if (getWeight(i) < getWeight(minChild))
            minChild = i;
    return minChild;

}

template<typename TData>
void THeap<TData>::dipDown(int i)
{
    int minChild = findMinChild(i);
    while ((minChild != -1) and (getWeight(minChild) < getWeight(i)))
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
THeap<TData>::THeap(const THeap<TData>& other)
{
    base = other.base;
    capacity = other.capacity;
    size = other.size;
    keys = new int[capacity];
    for (int i = 0; i < size; i++)
        keys[i] = other.keys[i];
    elements = other.elements;
}

template<typename TData>
THeap<TData>::THeap(TData* const elements_, int size_, TWeightFunc weight_, int base_)
{
    elements = elements_;
    capacity = size_;
    size = size_;
    keys = new int[capacity];
    for (int i = 0; i < size; i++)
        keys[i] = i;
    base = base_;
    weight = weight_;
    heapify();
}

template<typename TData>
THeap<TData>::~THeap()
{
    if (capacity > 0)
        delete[] keys;
}

template<typename TData>
TData* THeap<TData>::pullTop()
{
    int index = keys[0];
    transpose(0, size - 1);
    dipDown(0);
    size--;
    return elements + index;
}

template<typename TData>
void THeap<TData>::sort()
{
    int realSize = size;
    for (int i = size - 1; i >= 0; i--)
    {
        transpose(0, i);
        size--;
        dipDown(0);
        elements[i] = elements[keys[i]];
    }
    size = realSize;
}

#endif