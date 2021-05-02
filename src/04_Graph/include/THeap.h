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

    int min(int first, int second) const;

public:
    THeap<TData>(const THeap<TData>&) = default;
    THeap<TData>(TData* elements_, int size_, int base_ = 2);
    ~THeap<TData>() = default;

    int findMinChild(int i) const;
    const TData& topMin() const;

    void transpose(int i, int j);
    void popUp(int i);
    void dipDown(int i);
    void heapify();
    void popMin();

    bool full() const;
    bool empty() const;
    inline int getSize() const;
    inline int getCapacity() const;

    friend std::ostream& operator<<(std::ostream& stream, const THeap& heap);
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
std::ostream& operator<<(std::ostream& stream, const THeap<TData>& heap)
{
    for (int i = 0; i < heap.size; i++)
        stream << heap.elements[i] << ' ';
    return stream;
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