#ifndef _TBASETABLE_H_
#define _TBASETABLE_H_

#include "TTableEntry.h"
#include "TPair.h"

template <typename TKey, typename TData>
class TBaseTable
{
protected:
    size_t entriesCount;
public:
    using Key = TKey;
    using Data = TData;
    using Entry = TTableEntry<TKey, TData>;
    using Pair = TPair<TKey, TData>;
    TBaseTable();
    virtual ~TBaseTable();
    inline size_t getEntriesCount() const;
    virtual bool empty() const;
    virtual bool full() const = 0;
};

template<typename TKey, typename TData>
TBaseTable<TKey, TData>::TBaseTable()
    : entriesCount(0)
{
}

template<typename TKey, typename TData>
TBaseTable<TKey, TData>::~TBaseTable()
{
}

template<typename TKey, typename TData>
size_t TBaseTable<TKey, TData>::getEntriesCount() const
{
    return entriesCount;
}

template<typename TKey, typename TData>
bool TBaseTable<TKey, TData>::empty() const
{
    return entriesCount == 0;
}

#endif
