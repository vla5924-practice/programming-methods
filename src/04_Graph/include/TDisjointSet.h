#ifndef _TDISJOINTSET_H_
#define _TDISJOINTSET_H_

#include <iostream>
#include <exception>

class TDisjointSet
{
    int size;
    int* set;

public:
    TDisjointSet(int size);
    ~TDisjointSet();
    void createSingleton(int i);
    void unite(int i, int j);
    int findSet(int i) const;
};

#endif