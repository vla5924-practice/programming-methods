#ifndef _THEAP_H_
#define _THEAP_H_
#include <iostream>

template<typename TData>
class THeap
{
    int capacity;
    int size;
    int base;
    TData* elements;

    void transpose(int i, int j);
    int min(int first, int second) const;
    int findMinChild(int i) const;
    void popUp(int i);
    void dipDown(int i);
public:
    THeap<TData>(const THeap<TData>&) = default;
    THeap<TData>(TData* elements_, int size_, int base_ = 2);
    ~THeap<TData>() = default;

    void heapify();
    void popMin();
    const TData& topMin() const;
    void sort();

    void output() const;

    bool full() const;
    bool empty() const;

    inline int getSize() const;
    inline int getCapacity() const;
};

template<typename TData>
THeap<TData>::THeap(TData* elements_, int size_, int base_)
{
    base = base_;
    capacity = size_;
    size = size_;
    elements = elements_;
    heapify();
}

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
    lastChild = min(size - 1, base * (i + 1));
    minChild = firstChild;
    for (int i = firstChild + 1; i <= lastChild; i++)
        if (elements[i] < elements[minChild])
            minChild = i;
    return minChild;
}

template<typename TData>
void THeap<TData>::popUp(int i)
{
    while (i > 0)
    {
        int p = (i - 1) / base;
        if (elements[p] > elements[i])
        {
            transpose(i, p);
            i = p;
        }
        else
            break;
    }
}

template<typename TData>
void THeap<TData>::dipDown(int i)
{
    int minChild = findMinChild(i);
    while ((minChild != -1) && (elements[minChild] < elements[i]))
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
        dipDown(i);
}

template<typename TData>
void THeap<TData>::popMin()
{
    elements[0] = elements[size - 1];
    size--;
    dipDown(0);
}

template<typename TData>
const TData& THeap<TData>::topMin() const
{
    return elements[0];
}

template<typename TData>
void THeap<TData>::sort()
{
    heapify();
    while (size > 1)
    {
        transpose(0, size - 1);
        size--;
        dipDown(0);
    }
    output();
}

template<typename TData>
void THeap<TData>::output() const
{
    for (int i = 0; i < capacity; i++)
        std::cout << elements[i] << ' ';
    std::cout << '\n';
}

template<typename TData>
bool THeap<TData>::full() const
{
    return capacity == size;
}

template<typename TData>
bool THeap<TData>::empty() const
{
    return size == 0;
}

template<typename TData>
int THeap<TData>::getSize() const
{
    return size;
}

template<typename TData>
int THeap<TData>::getCapacity() const
{
    return capacity;
}

#endif // !_THEAP_H_