#ifndef _TORDEREDTABLE_H_
#define _TORDEREDTABLE_H_
#define _TOrderedTableIter typename TOrderedTable<TKey, TData>::Iterator

#include "TArrayTable.h"

template <typename TKey, typename TData>
class TOrderedTable : public TArrayTable<TKey, TData>
{
public:
    using BaseType = TArrayTable<TKey, TData>;
    using Key = TKey;
    using Data = TData;
    using Entry = BaseType::Entry;
    using Iterator = BaseType::Iterator;
    using Pair = BaseType::Pair;

protected:
    using BaseType::entries;
    using BaseType::entriesCount;
    using BaseType::capacity;

    void sort();
    using BaseType::getIndex;

public:
    TOrderedTable() = default;
    explicit TOrderedTable(size_t capacity_);
    TOrderedTable(const BaseType& super);
    ~TOrderedTable() = default;

    using BaseType::full;
    using BaseType::empty;
    virtual Iterator find(const TKey& needle) const;

    virtual void insert(const TKey& key, TData* data = nullptr);
    virtual void remove(const TKey& key);

    using BaseType::begin;
    using BaseType::end;

    EXCEPT(FullError, "Table is full.");
    EXCEPT(DuplicateError, "There is an entry with given key in the table already.");
    EXCEPT(NotFoundError, "Given key not found.");
};

template<typename TKey, typename TData>
void TOrderedTable<TKey, TData>::sort()
{
    for (size_t i = 0; i < entriesCount; i++)
        for (size_t j = 1; j < entriesCount - 1; j++)
            if (entries[j - 1]->getKey() > entries[j]->getKey())
            {
                Entry* temp = entries[j];
                entries[j] = entries[j - 1];
                entries[j - 1] = temp;
            }
}

template<typename TKey, typename TData>
TOrderedTable<TKey, TData>::TOrderedTable(size_t capacity_)
    : BaseType(capacity_)
{
}

template<typename TKey, typename TData>
TOrderedTable<TKey, TData>::TOrderedTable(const BaseType& super)
    : entriesCount(super.entriesCount), capacity(super.capacity)
{
    entries = new Entry * [capacity];
    for (size_t i = 0; i < entriesCount; i++)
        entries[i] = new Entry(super.entries[i]);
    sort();
}

template<typename TKey, typename TData>
_TOrderedTableIter TOrderedTable<TKey, TData>::find(const TKey& needle) const
{
    size_t middle;
    size_t left = 0;
    size_t right = entriesCount - 1;
    while (left <= right)
    {
        middle = (left + right) / 2;
        if (needle == entries[middle]->getKey())
            return Iterator(entries + middle);
        else if (needle < entries[middle]->getKey())
            right = middle - 1;
        else
            left = middle + 1;
    }
    return Iterator(nullptr);
}

template<typename TKey, typename TData>
void TOrderedTable<TKey, TData>::insert(const TKey& key, TData* data)
{
    if (full())
        throw FullError();
    auto nextOrdered = begin();
    while ((nextOrdered != end()) && (nextOrdered()->getKey() < key))
    {
        if (nextOrdered()->getKey() == key)
            throw DuplicateError();
        nextOrdered++;
    }
    size_t index = getIndex(nextOrdered);
    if (!empty())
        for (size_t i = entriesCount; i > index; i--)
            entries[i] = entries[i - 1];
    entries[index] = new Entry(key, data);
    entriesCount++;
}

template<typename TKey, typename TData>
void TOrderedTable<TKey, TData>::remove(const TKey& key)
{
    auto iter = find(key);
    if (!iter)
        throw NotFoundError();
    size_t index = getIndex(iter);
    delete entries[index];
    for (size_t i = index + 1; i < entriesCount; i++)
        entries[i - 1] = entries[i];
    entriesCount--;
}

#endif