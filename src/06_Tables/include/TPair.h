#ifndef _TPAIR_H_
#define _TPAIR_H_

template<typename TKey, typename TData>
struct TPair
{
    TKey key;
    TData* data;
    explicit TPair(TKey key_, TData* data_ = nullptr);
};

template<typename TKey, typename TData>
TPair<TKey, TData>::TPair(TKey key_, TData* data_)
    : key(key_), data(data_)
{
}

#endif
