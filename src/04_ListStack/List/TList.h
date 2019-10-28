#ifndef _TLIST_H_
#define _TLIST_H_
#include <iostream>
#include <iterator>

template <typename TNodeTypename>
class TListIterator : public std::iterator<std::input_iterator_tag, TNodeTypename>
{
    template <typename, typename> friend class TList;
    TNodeTypename* pNode;
    TListIterator(TNodeTypename* pNode);
public:
    TListIterator(const TListIterator& other) = default;
    ~TListIterator() = default;
    bool operator!=(TListIterator const& other) const;
    bool operator==(TListIterator const& other) const;
    typename TListIterator<TNodeTypename>::reference operator*() const;
    TListIterator& operator++();
    TListIterator& operator++(int);
};

template <typename TKey, typename TData>
class TList
{
public:
    struct TNode
    {
        TKey key = 0;
        TData* pData = nullptr;
        TList<TKey, TData>::TNode* pNext = nullptr;
        explicit TNode(TKey key = 0, TData* pData = nullptr, TNode* pNext = nullptr);
    };
    struct TPair
    {
    private:
        template<typename, typename> friend class TList;
        bool found = true;
        explicit TPair(bool found);
        TPair(const TKey& key, const TData*& pData, bool found);
    public:
        TKey& key;
        TData*& pData;
        TPair() = default;
        TPair(const TPair& other) = default;
        TPair(const TNode* node);
        TPair(const TKey& key, const TData*& pData);
        ~TPair() = default;
        operator bool() const;
    };
private:
    TList::TNode* pFirst;
    TList::TNode* pCurrent;
    TList::TNode* pPrev;
    TList::TNode* pNext;
    inline typename TNode* newNode(TKey key, TData* pData, TNode* pNext = nullptr) const;
    typename TNode* findNode(TKey needle) const;
public:
    TList();
    TList(const TList& other);
    TList(const TList<TKey, TData>::TNode* firstNode);
    ~TList();

    typename TPair find(TKey needle);
    void insertToStart(TKey key, TData* pData = nullptr);
    void insertToEnd(TKey key, TData* pData = nullptr);
    void insertBefore(TKey needle, TKey key, TData* pData = nullptr);
    void insertAfter(TKey needle, TKey key, TData* pData = nullptr);
    void remove(TKey needle);
    void removeAll();

    void reset();
    bool isEnded() const;
    typename TPair current() const;
    void next();

    typedef TListIterator<TList::TNode> iterator;
    typedef TListIterator<TList::TNode> const_iterator;
    typename iterator begin();
    typename iterator end();
    typename const_iterator begin() const;
    typename const_iterator end() const;

    TList& operator+=(TKey key);

    void output(std::ostream& stream) const;
};

// ------------------------------------------------------------------
// ------------------------------ TNODE -----------------------------
// ------------------------------------------------------------------

template<typename TKey, typename TData>
TList<TKey, TData>::TNode::TNode(TKey key, TData* pData, TList<TKey, TData>::TNode* pNext)
    : key(key), pData(pData), pNext(pNext)
{
}

// ------------------------------------------------------------------
// ------------------------------ TPAIR -----------------------------
// ------------------------------------------------------------------

template<typename TKey, typename TData>
TList<TKey, TData>::TPair::TPair(const TList<TKey, TData>::TNode* node)
{
    key = node->key;
    pData = node->pData;
}

template<typename TKey, typename TData>
TList<TKey, TData>::TPair::TPair(const TKey& key, const TData*& pData)
    : key(key), pData(pData) {}

template<typename TKey, typename TData>
TList<TKey, TData>::TPair::TPair(const TKey& key, const TData*& pData, bool found)
    : key(key), pData(pData), found(found) {}

template<typename TKey, typename TData>
TList<TKey, TData>::TPair::TPair(bool found)
    : key(0), pData(nullptr), found(found) {}

template<typename TKey, typename TData>
TList<TKey, TData>::TPair::operator bool() const
{
    return found;
}

// ------------------------------------------------------------------
// ------------------------------ TLIST -----------------------------
// ------------------------------------------------------------------

template<typename TKey, typename TData>
inline typename TList<TKey, TData>::TNode* TList<TKey, TData>::newNode(TKey key, TData* pData, TNode* pNext) const
{
    return new TNode(key, pData ? new TData(*pData) : nullptr, pNext);
}

template<typename TKey, typename TData>
TList<TKey, TData>::TList()
{
    pFirst = pCurrent = pPrev = pNext = nullptr;
}

template<typename TKey, typename TData>
TList<TKey, TData>::TList(const TList& other)
{
    if (!other.pFirst)
        return;
    TNode* temp = other.pFirst, prev = nullptr;
    while (temp)
    {
        TNode* node = newNode(temp.key, temp.pData);
        if (prev)
            prev->pNext = node;
        prev = node;
        temp = temp->pNext;
    }
    reset();
}

template<typename TKey, typename TData>
TList<TKey, TData>::TList(const TList<TKey, TData>::TNode* firstNode)
{
    if (!firstNode)
        return;
    TNode* temp = firstNode, prev = nullptr;
    while (temp)
    {
        TNode* pNode = newNode(temp.key, temp.pData);
        if (prev)
            prev->pNext = pNode;
        prev = pNode;
        temp = temp->pNext;
    }
    reset();
}

template<typename TKey, typename TData>
TList<TKey, TData>::~TList()
{
    removeAll();
}

template<typename TKey, typename TData>
typename TList<TKey, TData>::TNode* TList<TKey, TData>::findNode(TKey needle) const
{
    if (!pFirst)
        return nullptr;
    TNode* temp = pFirst;
    while (temp)
    {
        if (temp->key == needle)
            return temp;
        temp = temp->pNext;
    }
    return nullptr;
}

template<typename TKey, typename TData>
typename TList<TKey, TData>::TPair TList<TKey, TData>::find(TKey needle)
{
    if (!pFirst)
        return TPair(false);
    TNode* temp = pFirst;
    while (temp)
    {
        if (pFirst->key == needle)
            return TPair(temp->key, temp->pData);
        temp = temp->pNext;
    }
    return TPair(false);
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insertToStart(TKey key, TData* pData)
{
    TNode* pNode = newNode(key, pData, pFirst);
    pFirst = pNode;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insertToEnd(TKey key, TData* pData)
{
    if (!pFirst)
    {
        pFirst = newNode(key, pData);
        reset();
        return;
    }
    TNode* temp = pFirst;
    while (temp->pNext)
        temp = temp->pNext;
    temp->pNext = newNode(key, pData, nullptr);
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insertBefore(TKey needle, TKey key, TData* pData)
{
    if (!pFirst)
        return;
    if (pFirst->key == needle)
    {
        TNode* pNode = newNode(key, pData, pFirst);
        pFirst = pNode;
        reset();
        return;
    }
    TNode* temp = pFirst;
    while (temp->pNext && (temp->pNext->key != needle))
        temp = temp->next;
    if (!temp->pNext)
        return;
    TNode* pNode = newNode(key, pData, temp->pNext);
    temp->pNext = pNode;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insertAfter(TKey needle, TKey key, TData* pData)
{
    TNode* prev = findNode(needle);
    if (!prev)
        return;
    TNode* pNode = newNode(key, pData, prev->pNext);
    prev->pNext = pNode;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::remove(TKey needle)
{
    if (!pFirst)
        return;
    if (pFirst->key == needle)
    {
        TNode* pNode = pFirst;
        pFirst = pFirst->pNext;
        if (pNode->pData)
            delete pNode->pData;
        delete pNode;
        return;
    }
    TNode* temp = pFirst;
    while (temp->pNext && (temp->pNext->key != needle))
        temp = temp->pNext;
    if (!temp->pNext)
        return;
    TNode* pNode = temp->pNext;
    temp->pNext = pNode->pNext;
    if (pNode->pData)
        delete pNode->pData;
    delete pNode;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::removeAll()
{
    if (!pFirst)
        return;
    TNode* temp = pFirst;
    while (temp)
    {
        TNode* node = temp;
        temp = temp->pNext;
        if(node->pData)
            delete node->pData;
        delete node;
    }
    pFirst = nullptr;
    reset();
}

template<typename TKey, typename TData>
void TList<TKey, TData>::reset()
{
    pCurrent = pFirst;
    pPrev = nullptr;
    pNext = pFirst ? pFirst->pNext : nullptr;
}

template<typename TKey, typename TData>
bool TList<TKey, TData>::isEnded() const
{
    return pCurrent == nullptr;
}

template<typename TKey, typename TData>
typename TList<TKey, TData>::TPair TList<TKey, TData>::current() const
{
    return isEnded() ? TPair(false) : TPair(pCurrent->key, pCurrent->pData);
}

template<typename TKey, typename TData>
void TList<TKey, TData>::next()
{
    if (pCurrent == nullptr)
        return;
    pPrev = pCurrent;
    pCurrent = pNext;
    pNext = pNext ? pNext->pNext : pNext;
}

template<typename TKey, typename TData>
TList<TKey, TData>& TList<TKey, TData>::operator+=(TKey key)
{
    insertToEnd(key, nullptr);
    return *this;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::output(std::ostream& stream) const
{
    TNode* temp = pFirst;
    while (temp)
    {
        stream << temp << ' ';
        temp = temp->pNext;
    }
}

// ------------------------------------------------------------------
// ----------------------- ITERATION IN TLIST -----------------------
// ------------------------------------------------------------------

template<typename TKey, typename TData>
typename TList<TKey, TData>::iterator TList<TKey, TData>::begin()
{
    return iterator(pFirst);
}

template<typename TKey, typename TData>
typename TList<TKey, TData>::iterator TList<TKey, TData>::end()
{
    return iterator(nullptr);
}

template<typename TKey, typename TData>
typename TList<TKey, TData>::const_iterator TList<TKey, TData>::begin() const
{
    return iterator(pFirst);
}

template<typename TKey, typename TData>
typename TList<TKey, TData>::const_iterator TList<TKey, TData>::end() const
{
    return iterator(nullptr);
}

// ------------------------------------------------------------------
// -------------------------- TLISTITERATOR -------------------------
// ------------------------------------------------------------------

template <typename TNodeTypename>
TListIterator<TNodeTypename>::TListIterator(TNodeTypename* pNode) : pNode(pNode) {}

template <typename TNodeTypename>
bool TListIterator<TNodeTypename>::operator!=(TListIterator const& other) const
{
    return pNode != other.pNode;
}

template <typename TNodeTypename>
bool TListIterator<TNodeTypename>::operator==(TListIterator const& other) const
{
    return pNode == other.pNode;
}

template <typename TNodeTypename>
typename TListIterator<TNodeTypename>::reference TListIterator<TNodeTypename>::operator*() const
{
    return *pNode;
}

template <typename TNodeTypename>
TListIterator<TNodeTypename>& TListIterator<TNodeTypename>::operator++()
{
    if (pNode)
        pNode = pNode->pNext;
    return *this;
}

template <typename TNodeTypename>
TListIterator<TNodeTypename>& TListIterator<TNodeTypename>::operator++(int)
{
    if (pNode)
        pNode = pNode->pNext;
    return *this;
}

#endif // !_TLIST_H_