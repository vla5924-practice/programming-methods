#include "TSplitSet.h"

TSplitSet::TSplitSet(int size_)
{
    size = size_;
    set = new int[size];
    for (int i = 0; i < size; i++)
        set[i] = -1;
}

TSplitSet::~TSplitSet()
{
    delete[] set;
}

void TSplitSet::createSingleton(int i)
{
    if (i < 0 || i >= size)
        throw std::out_of_range("Index undefined");
    set[i] = i;
}

void TSplitSet::unite(int i, int j)
{
    if (i < 0 || i >= size || j < 0 || j >= size)
        throw std::out_of_range("Index undefined");
    for (int k = 0; k < size; k++)
        if (set[k] == j)
            set[k] = i;
}

int TSplitSet::findSet(int i) const
{
    if (i < 0 || i >= size)
        throw std::out_of_range("Index undefined");
    return set[i];
}