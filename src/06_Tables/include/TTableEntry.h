#ifndef _TTABLEENTRY_H_
#define _TTABLEENTRY_H_

template <typename TKey, typename TData>
class TTableEntry
{
protected:
    TKey key;
public:
    TData* data;
    TTableEntry();
    explicit TTableEntry(const TKey& key_, TData* data_ = nullptr);
    TKey getKey() const;
};

template<typename TKey, typename TData>
TTableEntry<TKey, TData>::TTableEntry()
    : data(nullptr)
{
}

template<typename TKey, typename TData>
TTableEntry<TKey, TData>::TTableEntry(const TKey& key_, TData* data_)
    : key(key_), data(data_)
{
}

template<typename TKey, typename TData>
TKey TTableEntry<TKey, TData>::getKey() const
{
    return key;
}

#endif
