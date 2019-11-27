#ifndef _TLIST_H_
#define _TLIST_H_
#include <iostream>
#include <iterator>
#include <exception>
#include <string>

template <typename TNodeTypename, typename TPairTypename>
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
    typename TPairTypename operator*() const;
    TListIterator operator++();
    TListIterator operator++(int);
};

template <typename TKey, typename TData>
class TList
{
public:
    struct TNode
    {
        TKey key;
        TData* pData;
        TNode* pNext = nullptr;
        explicit TNode(TKey key = 0, TData* pData = nullptr, TNode* pNext = nullptr);
        TNode(TKey key, TData data, TNode* pNext = nullptr);
        TNode(const TNode& other);
    };
    struct TPair
    {
    private:
        template<typename, typename> friend class TList;
        template<typename, typename> friend class TListIterator;
        static TKey mockKey;
        static TData* mockData;
        bool found = true;
        TNode* baseNode = nullptr;
        explicit TPair(bool found);
        TPair(TKey& key, TData*& pData, TList<TKey, TData>::TNode* baseNode, bool found);
    public:
        TKey& key;
        TData* pData;
        TPair() = default;
        TPair(const TPair& other) = default;
        TPair(TNode* pNode);
        TPair(TKey& key, TData*& pData);
        ~TPair() = default;
        operator bool() const;
        typename TPair& operator=(const TPair& other);
    };
private:
    TList::TNode* pFirst;
    inline typename TNode* newNode(TKey key, TData* pData, TNode* pNext = nullptr) const;
    typename TNode* findNode(TKey needle) const;
public:
    TList();
    TList(const TList& other);
    TList(const TList<TKey, TData>::TNode* firstNode);
    ~TList();

    typedef TListIterator<TList::TNode, TList::TPair> iterator;
    typedef TListIterator<TList::TNode, TList::TPair> const_iterator;

    typename TPair find(TKey needle);
    typename TPair getFirst();
    void insertToStart(TKey key, TData* pData = nullptr);
    void insertToEnd(TKey key, TData* pData = nullptr);
    void insertBefore(TKey needle, TKey key, TData* pData = nullptr);
    void insertBefore(iterator i, TKey key, TData* pData);
    void insertAfter(TKey needle, TKey key, TData* pData = nullptr);
    void insertAfter(iterator i, TKey key, TData* pData);
    void remove(TKey needle);
    void remove(iterator i);
    void removeAll();

    size_t size() const;
    bool empty() const;

    typename iterator begin();
    typename iterator end();
    typename const_iterator begin() const;
    typename const_iterator end() const;

    void output(std::ostream& stream, const char* separator = " ", const char* ending = "\n") const;
    void outputRaw(std::ostream& stream) const;
};

namespace TListException
{
    class NodeNotFound : ::std::exception
    {
        const ::std::string whatStr = "Node with given key not found.";
    public:
        virtual const char* what() { return whatStr.c_str(); }
    };
}

// ------------------------------------------------------------------
// ------------------------------ TNODE -----------------------------
// ------------------------------------------------------------------

template<typename TKey, typename TData>
TList<TKey, TData>::TNode::TNode(TKey key, TData* pData, TList<TKey, TData>::TNode* pNext)
    : key(key), pData(pData), pNext(pNext)
{
}

template<typename TKey, typename TData>
TList<TKey, TData>::TNode::TNode(TKey key, TData data, TList<TKey, TData>::TNode* pNext)
    : key(key), pData(new TData(data)), pNext(pNext)
{
}

template<typename TKey, typename TData>
TList<TKey, TData>::TNode::TNode(const TNode& other)
    : key(other.key), pData(other.pData ? new TData(*(other.pData)) : nullptr), pNext(pNext)
{
}

// ------------------------------------------------------------------
// ------------------------------ TPAIR -----------------------------
// ------------------------------------------------------------------

template<typename TKey, typename TData>
TKey TList<TKey, TData>::TPair::mockKey = 0;

template<typename TKey, typename TData>
TData* TList<TKey, TData>::TPair::mockData = nullptr;

template<typename TKey, typename TData>
TList<TKey, TData>::TPair::TPair(TList<TKey, TData>::TNode* pNode)
    : key(pNode ? pNode->key : mockKey), pData(pNode ? pNode->pData : mockData), 
      baseNode(pNode), found(pNode) {}

template<typename TKey, typename TData>
TList<TKey, TData>::TPair::TPair(TKey& key, TData*& pData)
    : key(key), pData(pData) {}

template<typename TKey, typename TData>
TList<TKey, TData>::TPair::TPair(TKey& key, TData*& pData, TNode* baseNode, bool found)
    : key(key), pData(pData), baseNode(baseNode), found(found) {}

template<typename TKey, typename TData>
TList<TKey, TData>::TPair::TPair(bool found)
    : key(mockKey), pData(mockData), found(found) {}

template<typename TKey, typename TData>
TList<TKey, TData>::TPair::operator bool() const
{
    return found;
}

template<typename TKey, typename TData>
typename TList<TKey, TData>::TPair& TList<TKey, TData>::TPair::operator=(const TPair& other)
{
    key = other.key;
    pData = other.pData;
    found = other.found;
    return *this;
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
    pFirst = nullptr;
}

template<typename TKey, typename TData>
TList<TKey, TData>::TList(const TList& other) : TList()
{
    if (!other.pFirst)
        return;
    pFirst = newNode(other.pFirst->key, other.pFirst->pData);
    TNode* temp = other.pFirst->pNext;
    TNode* prev = pFirst;
    while (temp)
    {
        TNode* pNode = newNode(temp->key, temp->pData);
        prev->pNext = pNode;
        prev = pNode;
        temp = temp->pNext;
    }
}

template<typename TKey, typename TData>
TList<TKey, TData>::TList(const TList<TKey, TData>::TNode* firstNode) : TList()
{
    if (!firstNode)
        return;
    pFirst = newNode(firstNode->key, firstNode->pData);
    TNode* temp = firstNode->pNext;
    TNode* prev = pFirst;
    while (temp)
    {
        TNode* pNode = newNode(temp.key, temp.pData);
        prev->pNext = pNode;
        prev = pNode;
        temp = temp->pNext;
    }
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
        if (temp->key == needle)
            return TPair(temp->key, temp->pData, temp, true);
        temp = temp->pNext;
    }
    return TPair(false);
}

template<typename TKey, typename TData>
typename TList<TKey, TData>::TPair TList<TKey, TData>::getFirst()
{
    return pFirst ? TPair(pFirst->key, pFirst->pData) : TPair(false);
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
        throw TListException::NodeNotFound();
    if (pFirst->key == needle)
    {
        TNode* pNode = newNode(key, pData, pFirst);
        pFirst = pNode;
        return;
    }
    TNode* temp = pFirst;
    while (temp->pNext && (temp->pNext->key != needle))
        temp = temp->pNext;
    if (!temp->pNext)
        throw TListException::NodeNotFound();
    TNode* pNode = newNode(key, pData, temp->pNext);
    temp->pNext = pNode;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insertBefore(iterator i, TKey key, TData* pData)
{
    if (!pFirst)
        throw TListException::NodeNotFound();
    if (!i.pNode)
    {
        insertToEnd((*i).key, (*i).pData);
        return;
    }
    TKey needle = (*i).key;
    if (pFirst->key == needle)
    {
        TNode* pNode = newNode(key, pData, pFirst);
        pFirst = pNode;
        return;
    }
    TNode* temp = pFirst;
    while (temp->pNext && (temp->pNext->key != needle))
        temp = temp->pNext;
    if (!temp->pNext)
        throw TListException::NodeNotFound();
    TNode* pNode = newNode(key, pData, temp->pNext);
    temp->pNext = pNode;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insertAfter(iterator i, TKey key, TData* pData)
{
    if (!i.pNode)
        throw TListException::NodeNotFound();
    TNode* pNode = newNode(key, pData, i.pNode->pNext);
    i.pNode->pNext = pNode;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insertAfter(TKey needle, TKey key, TData* pData)
{
    TNode* prev = findNode(needle);
    if (!prev)
        throw TListException::NodeNotFound();
    TNode* pNode = newNode(key, pData, prev->pNext);
    prev->pNext = pNode;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::remove(TKey needle)
{
    if (!pFirst)
        throw TListException::NodeNotFound();
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
        throw TListException::NodeNotFound();
    TNode* pNode = temp->pNext;
    temp->pNext = pNode->pNext;
    if (pNode->pData)
        delete pNode->pData;
    delete pNode;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::remove(iterator i)
{
    if (!pFirst || !i.pNode)
        throw TListException::NodeNotFound();
    TKey needle = i.pNode->key;
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
        throw TListException::NodeNotFound();
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
        TNode* pNode = temp;
        temp = temp->pNext;
        if (pNode->pData)
            delete pNode->pData;
        delete pNode;
    }
    pFirst = nullptr;
}

template<typename TKey, typename TData>
size_t TList<TKey, TData>::size() const
{
    if (!pFirst)
        return 0;
    TNode* temp = pFirst;
    size_t i = 0;
    while (temp)
    {
        i++;
        temp = temp->pNext;
    }
    return i;
}

template<typename TKey, typename TData>
bool TList<TKey, TData>::empty() const
{
    return pFirst == nullptr;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::output(std::ostream& stream, const char* separator, const char* ending) const
{
    TNode* temp = pFirst;
    while (temp)
    {
        if (temp->pData)
            stream << *(temp->pData);
        else
            stream << "nullptr";
        stream << separator;
        temp = temp->pNext;
    }
    stream << ending;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::outputRaw(std::ostream& stream) const
{
    TNode* temp = pFirst;
    stream << "[\n";
    while (temp)
    {
        stream << "    {\n        " << temp->key << "\n        ";
        if (temp->pData)
            stream << *(temp->pData);
        else
            stream << "nullptr";
        stream << "\n    }\n";
        temp = temp->pNext;
    }
    stream << "]\n";
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

template <typename TNodeTypename, typename TPairTypename>
TListIterator<TNodeTypename, TPairTypename>::TListIterator(TNodeTypename* pNode) : pNode(pNode) {}

template <typename TNodeTypename, typename TPairTypename>
bool TListIterator<TNodeTypename, TPairTypename>::operator!=(TListIterator const& other) const
{
    return pNode != other.pNode;
}

template <typename TNodeTypename, typename TPairTypename>
bool TListIterator<TNodeTypename, TPairTypename>::operator==(TListIterator const& other) const
{
    return pNode == other.pNode;
}

template <typename TNodeTypename, typename TPairTypename>
typename TPairTypename TListIterator<TNodeTypename, TPairTypename>::operator*() const
{
    return TPairTypename(pNode);
}

template <typename TNodeTypename, typename TPairTypename>
TListIterator<TNodeTypename, TPairTypename> TListIterator<TNodeTypename, TPairTypename>::operator++()
{
    if (pNode)
        pNode = pNode->pNext;
    return *this;
}

template <typename TNodeTypename, typename TPairTypename>
TListIterator<TNodeTypename, TPairTypename> TListIterator<TNodeTypename, TPairTypename>::operator++(int)
{
    TNodeTypename* temp = pNode;
    if (pNode)
        pNode = pNode->pNext;
    return TListIterator<TNodeTypename, TPairTypename>(temp);
}

#endif // !_TLIST_H_