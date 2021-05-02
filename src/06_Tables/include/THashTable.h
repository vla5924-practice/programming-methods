#ifndef _THASHTABLE_H_
#define _THASHTABLE_H_
#define _THashTableIter typename THashTable<TKey, TData>::Iterator

#include "EXCEPT.h"
#include "TBaseTable.h"
#include "TIterator.h"
#include "TChain.h"

template <typename TKey, typename TData>
class THashTable : public TBaseTable<TKey, TData>
{
public:
    using BaseType = TBaseTable<TKey, TData>;
    using Key = TKey;
    using Data = TData;
    using Entry = TChainNode<TKey, TData>;
    using Iterator = Entry*; // TODO
    using Pair = BaseType::Pair;

protected:
    using BaseType::entriesCount;
    size_t chainsCount;
    TChain<TKey, TData>* chains;
    size_t hash(const TKey& key) const;

public:
    explicit THashTable(size_t chainsCount_ = 64);
    ~THashTable();

    using BaseType::empty;
    bool full() const;
    virtual Iterator find(const TKey& needle) const;

    virtual void insert(const TKey& key, TData* data = nullptr);
    virtual void remove(const TKey& key);

    EXCEPT(DuplicateError, "There is an entry with given key in the table already.");
    EXCEPT(NotFoundError, "Given key not found.");
};

template<typename TKey, typename TData>
inline size_t THashTable<TKey, TData>::hash(const TKey& key) const
{
    return key % chainsCount;
}

template<typename TKey, typename TData>
THashTable<TKey, TData>::THashTable(size_t chainsCount_)
    : chainsCount(chainsCount_)
{
    if (chainsCount == 0)
        chains = nullptr;
    else
        chains = new TChain<TKey, TData>[chainsCount];
}

template<typename TKey, typename TData>
THashTable<TKey, TData>::~THashTable()
{
    if (chains)
        delete[] chains;
}

template<typename TKey, typename TData>
bool THashTable<TKey, TData>::full() const
{
    return false;
}

template<typename TKey, typename TData>
_THashTableIter THashTable<TKey, TData>::find(const TKey& needle) const
{
    size_t index = hash(needle);
    for (auto i = chains[index].head; i != nullptr; i = i->next)
        if (i->getKey() == needle)
            return Iterator(i);
    return Iterator(nullptr);
}

template<typename TKey, typename TData>
void THashTable<TKey, TData>::insert(const TKey& key, TData* data)
{
    if (find(key))
        throw DuplicateError();
    size_t index = hash(key);
    chains[index].add(key, data);
    entriesCount++;
}

template<typename TKey, typename TData>
void THashTable<TKey, TData>::remove(const TKey& key)
{
    size_t index = hash(key);
    if (!chains[index].remove(key))
        throw NotFoundError();
    entriesCount--;
}

#endif
