#ifndef _TSPLITSET_H_
#define _TSPLITSET_H_
#include <iostream>
#include <exception>

class TSplitSet
{
    int size;
    int* set;

public:
    TSplitSet(int size);
    ~TSplitSet();
    void createSingleton(int i);
    void unite(int i, int j);
    int findSet(int i) const;
};
#endif // !_TSPLITSET_H_