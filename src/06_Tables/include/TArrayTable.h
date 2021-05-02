#ifndef _TARRAYTABLE_H_
#define _TARRAYTABLE_H_
#define _TArrayTableIter typename TArrayTable<TKey, TData>::Iterator

#include "EXCEPT.h"
#include "TBaseTable.h"
#include "TIterator.h"

template <typename TKey, typename TData>
class TArrayTable : public TBaseTable<TKey, TData>
{
public:
    using BaseType = TBaseTable<TKey, TData>;
    using Key = TKey;
    using Data = TData;
    using Entry = TTableEntry<TKey, TData>;
    using Iterator = TIterator<Entry*>;
    using Pair = BaseType::Pair;

protected:
    using BaseType::entriesCount;
    size_t capacity;
    Entry** entries;
    size_t getIndex(Entry** entry) const;
    size_t getIndex(Iterator i) const;

public:
    TArrayTable();
    explicit TArrayTable(size_t capacity_);
    ~TArrayTable();

    using BaseType::empty;
    bool full() const;
    virtual Iterator find(const TKey& needle) const;

    virtual void insert(const TKey& key, TData* data = nullptr);
    virtual void remove(const TKey& key);

    virtual Iterator begin() const;
    virtual Iterator end() const;

    EXCEPT(FullError, "Table is full.");
    EXCEPT(DuplicateError, "There is an entry with given key in the table already.");
    EXCEPT(NotFoundError, "Given key not found.");
};

template<typename TKey, typename TData>
size_t TArrayTable<TKey, TData>::getIndex(Entry** entry) const
{
    return entry - entries;
}

template<typename TKey, typename TData>
size_t TArrayTable<TKey, TData>::getIndex(Iterator i) const
{
    return i.ptr - entries;
}

template<typename TKey, typename TData>
TArrayTable<TKey, TData>::TArrayTable()
    : BaseType(), capacity(0), entries(nullptr)
{
}

template<typename TKey, typename TData>
TArrayTable<TKey, TData>::TArrayTable(size_t capacity_)
    : capacity(capacity_)
{
    if (capacity > 0)
        entries = new Entry*[capacity];
}

template<typename TKey, typename TData>
TArrayTable<TKey, TData>::~TArrayTable()
{
    if (entries != nullptr)
    {
        for (size_t i = 0; i < entriesCount; i++)
            delete entries[i];
        delete[] entries;
    }
}

template<typename TKey, typename TData>
bool TArrayTable<TKey, TData>::full() const
{
    return entriesCount == capacity;
}

template<typename TKey, typename TData>
_TArrayTableIter TArrayTable<TKey, TData>::find(const TKey& needle) const
{
    for (auto i = begin(); i != end(); i++)
        if (i()->getKey() == needle)
            return Iterator(i);
    return Iterator(nullptr);
}

template<typename TKey, typename TData>
void TArrayTable<TKey, TData>::insert(const TKey& key, TData* data)
{
    if (full())
        throw FullError();
    if (find(key))
        throw DuplicateError();
    entries[entriesCount++] = new Entry(key, data);
}

template<typename TKey, typename TData>
void TArrayTable<TKey, TData>::remove(const TKey& key)
{
    auto iter = find(key);
    if (!iter)
        throw NotFoundError();
    int index = getIndex(iter);
    delete entries[index];
    entries[index] = entries[entriesCount - 1];
    entriesCount--;
}

template<typename TKey, typename TData>
_TArrayTableIter TArrayTable<TKey, TData>::begin() const
{
    return Iterator(entries);
}

template<typename TKey, typename TData>
_TArrayTableIter TArrayTable<TKey, TData>::end() const
{
    return Iterator(entries + entriesCount);
}

#endif
