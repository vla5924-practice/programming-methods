#ifndef _THEAP_H_
#define _THEAP_H_
#include <ciso646>

template<typename TData>
class THeap
{
    int form;
    int capacity;
    int size;
    int* keys;
    TData* elements;

    void transpose(int i, int j);
    int findMinChild(int i) const;
    void popUp(int i);
    void dipDown(int i);
    void heaping();
public:
    THeap(const THeap& other);
    THeap(const TData* const elements_, int size, int form_ = 2);
    ~THeap();

    TData* popTop();
};

inline int findMin(int first, int second)
{
    return first < second ? first : second;
}

template<typename TData>
void THeap<TData>::transpose(int i, int j)
{
    int temp = keys[i];
    keys[i] = keys[j];
    keys[j] = temp;
}

template<typename TData>
void THeap<TData>::popUp(int i)
{
    int parent = (i - 1) / form;
    while (i > 0)
    {
        if (keys[parent] > keys[i])
        {
            transpose(parent, i);
            i = parent;
        }
        else
            break;
    }
}

template<typename TData>
void THeap<TData>::dipDown(int i)
{
    int c = findMinChild(i);
    while ((c != -1) and (keys[c] < keys[i]))
    {
        transpose(c, i);
        i = c;
        c = findMinChild(i);
    }
}

template<typename TData>
void THeap<TData>::heaping()
{
    for (int i = size - 1; i >= 0; i--)
        dipDown(i);
}

template<typename TData>
int THeap<TData>::findMinChild(int i) const
{
    if (i * form + 1 >= size)
        return -1;
    int c1 = i * form + 1;
    int c2 = findMin(size - 1, i * form + form);
    int c = c1;
    for (int i = c1 + 1; i <= c2; i++)
        if (keys[i] < keys[c])
            c = i;
    return c;
}

template<typename TData>
THeap<TData>::THeap(const THeap<TData>& other)
{
    form = other.form;
    capacity = other.capacity;
    size = other.size;
    keys = new int[capacity];
    for (int i = 0; i < size; i++)
        keys[i] = other.keys[i];
    elements = other.elements;
}

template<typename TData>
THeap<TData>::THeap(const TData* const elements_, int size, int form_)
{
    elements = elements_;
    capacity = size_;
    size = size_;
    keys = new int[capacity];
    form = form_;
    // окучивание();
}

template<typename TData>
THeap<TData>::~THeap()
{
    if (capacity > 0)
        delete[] keys;
}

template<typename TData>
TData* THeap<TData>::popTop()
{
    TData* element = elements[0];
    transpose(0, size - 1);
    size -= 1;
    dipDown(0);
    return element;
}

#endif