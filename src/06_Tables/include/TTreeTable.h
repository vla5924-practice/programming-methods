#ifndef _TTREETABLE_H_
#define _TTREETABLE_H_
#define _TTreeTableIter typename TTreeTable<TKey, TData>::Iterator

#include "EXCEPT.h"
#include "TBaseTable.h"
#include "TAVLTree.h"

template <typename TKey, typename TData>
class TTreeTable : public TBaseTable<TKey, TData>
{
public:
    using BaseType = TBaseTable<TKey, TData>;
    using Key = TKey;
    using Data = TData;
    using Tree = TAVLTree<TKey, TData>;
    using Iterator = typename Tree::Iterator;
    using Entry = typename Tree::Node;
    using Pair = typename BaseType::Pair;

protected:
    using BaseType::entriesCount;
    Tree tree;

public:
    TTreeTable() = default;
    ~TTreeTable() = default;

    using BaseType::empty;
    bool full() const;
    Iterator find(const TKey& needle) const;

    void insert(const TKey& key, TData* data = nullptr);
    void remove(const TKey& key);

    bool owns(const Iterator& iter) const;
    Iterator root() const;
    Iterator null() const;
    Iterator notFound() const;

    Iterator begin() const;
    Iterator end() const;

    EXCEPT(DuplicateError, "There is an entry with given key in the table already.");
    EXCEPT(NotFoundError, "Given key not found.");
};

template<typename TKey, typename TData>
bool TTreeTable<TKey, TData>::full() const
{
    return false;
}

template<typename TKey, typename TData>
_TTreeTableIter TTreeTable<TKey, TData>::find(const TKey& needle) const
{
    return tree.find(needle);
}

template<typename TKey, typename TData>
void TTreeTable<TKey, TData>::insert(const TKey& key, TData* data)
{
    if (find(key) != notFound())
        throw DuplicateError();
    tree.insert(key, data);
    entriesCount++;
}

template<typename TKey, typename TData>
void TTreeTable<TKey, TData>::remove(const TKey& key)
{
    auto iter = find(key);
    if (owns(iter) && iter == null())
        return NotFoundError();
    tree.remove(key);
    entriesCount--;
}

template<typename TKey, typename TData>
bool TTreeTable<TKey, TData>::owns(const Iterator& iter) const
{
    return tree.owns(iter);
}

template<typename TKey, typename TData>
_TTreeTableIter TTreeTable<TKey, TData>::root() const
{
    return tree.root();
}

template<typename TKey, typename TData>
_TTreeTableIter TTreeTable<TKey, TData>::null() const
{
    return tree.null();
}

template<typename TKey, typename TData>
_TTreeTableIter TTreeTable<TKey, TData>::notFound() const
{
    return tree.notFound();
}

template<typename TKey, typename TData>
_TTreeTableIter TTreeTable<TKey, TData>::begin() const
{
    return root();
}

template<typename TKey, typename TData>
_TTreeTableIter TTreeTable<TKey, TData>::end() const
{
    return null();
}

#endif