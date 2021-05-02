#ifndef _TCHAINNODE_H_
#define _TCHAINNODE_H_

#include "TTableEntry.h"

template<typename TKey, typename TData>
class TChainNode : public TTableEntry<TKey, TData>
{
public:
    using BaseType = TTableEntry<TKey, TData>;
protected:
    template<typename, typename> friend class THashTable;
    template<typename, typename> friend class TChain;
    using BaseType::key;
    TChainNode<TKey, TData>* next;
public:
    using BaseType::data;
    using BaseType::getKey;
    TChainNode(const TKey& key_, TData* data_ = nullptr, TChainNode* next_ = nullptr)
        : BaseType(key_, data_), next(next_) {};
};

#endif // !_TCHAINNODE_H_
