#ifndef _TLIST_H_
#define _TLIST_H_
#include <iostream>
#include <iterator>
#include <exception>
#include <string>

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
    typename TNodeTypename* operator*() const;
    TListIterator operator++();
    TListIterator operator++(int);
};

template <typename TKey, typename TData>
class TList
{
public:
    class TNode
    {
        template <typename, typename> friend class TList;
        template <typename> friend class TListIterator;
        TNode* pNext;
    public:
        TKey key;
        TData data;
        explicit TNode(TKey key = 0, TData data = 0, TNode* pNext = nullptr);
        TNode(const TNode& other);
    };
private:
    TList::TNode* pFirst;
public:
    TList();
    TList(const TList& other);
    TList(const TList<TKey, TData>::TNode* firstNode);
    ~TList();

    typedef TListIterator<TList::TNode> iterator;
    typedef TListIterator<TList::TNode> const_iterator;

    typename TNode* find(TKey needle);
    typename TNode* getFirst();
    void insertToStart(TKey key, TData data = nullptr);
    void insertToEnd(TKey key, TData data = nullptr);
    void insertBefore(TKey needle, TKey key, TData data = 0);
    void insertBefore(iterator i, TKey key, TData data = 0);
    void insertAfter(TKey needle, TKey key, TData data = 0);
    void insertAfter(iterator i, TKey key, TData data = 0);
    void remove(TKey needle);
    void remove(iterator& i);
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
TList<TKey, TData>::TNode::TNode(TKey key, TData data, TList<TKey, TData>::TNode* pNext)
    : key(key), data(data), pNext(pNext)
{
}

template<typename TKey, typename TData>
TList<TKey, TData>::TNode::TNode(const TNode& other)
    : key(other.key), data(other.data), pNext(pNext)
{
}

// ------------------------------------------------------------------
// ------------------------------ TLIST -----------------------------
// ------------------------------------------------------------------

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
    pFirst = new TNode(other.pFirst->key, other.pFirst->data);
    TNode* temp = other.pFirst->pNext;
    TNode* prev = pFirst;
    while (temp)
    {
        TNode* pNode = new TNode(temp->key, temp->data);
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
    pFirst = new TNode(firstNode->key, firstNode->data);
    TNode* temp = firstNode->pNext;
    TNode* prev = pFirst;
    while (temp)
    {
        TNode* pNode = new TNode(temp.key, temp.data);
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
typename TList<TKey, TData>::TNode* TList<TKey, TData>::find(TKey needle)
{
    if (!pFirst)
        return nullptr;
    TNode* temp = pFirst;
    while (temp)
    {
        if (temp->key == needle)
            temp;
        temp = temp->pNext;
    }
    return nullptr;
}

template<typename TKey, typename TData>
typename TList<TKey, TData>::TNode* TList<TKey, TData>::getFirst()
{
    return pFirst;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insertToStart(TKey key, TData data)
{
    TNode* pNode = new TNode(key, data, pFirst);
    pFirst = pNode;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insertToEnd(TKey key, TData data)
{
    if (!pFirst)
    {
        pFirst = new TNode(key, data);
        return;
    }
    TNode* temp = pFirst;
    while (temp->pNext)
        temp = temp->pNext;
    temp->pNext = new TNode(key, data, nullptr);
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insertBefore(TKey needle, TKey key, TData data)
{
    if (!pFirst)
        throw TListException::NodeNotFound();
    if (pFirst->key == needle)
    {
        TNode* pNode = new TNode(key, data, pFirst);
        pFirst = pNode;
        return;
    }
    TNode* temp = pFirst;
    while (temp->pNext && (temp->pNext->key != needle))
        temp = temp->pNext;
    if (!temp->pNext)
        throw TListException::NodeNotFound();
    TNode* pNode = new TNode(key, data, temp->pNext);
    temp->pNext = pNode;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insertBefore(iterator i, TKey key, TData data)
{
    if (!pFirst)
        throw TListException::NodeNotFound();
    if (!i.pNode)
    {
        insertToEnd((*i).key, (*i).data);
        return;
    }
    TNode* needle = i.pNode;
    if (pFirst == needle)
    {
        TNode* pNode = new TNode(key, data, pFirst);
        pFirst = pNode;
        return;
    }
    TNode* temp = pFirst;
    while (temp->pNext && (temp->pNext != needle))
        temp = temp->pNext;
    if (!temp->pNext)
        throw TListException::NodeNotFound();
    TNode* pNode = new TNode(key, data, temp->pNext);
    temp->pNext = pNode;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insertAfter(iterator i, TKey key, TData data)
{
    if (!i.pNode)
        throw TListException::NodeNotFound();
    TNode* pNode = new TNode(key, data, i.pNode->pNext);
    i.pNode->pNext = pNode;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insertAfter(TKey needle, TKey key, TData data)
{
    TNode* prev = findNode(needle);
    if (!prev)
        throw TListException::NodeNotFound();
    TNode* pNode = new TNode(key, data, prev->pNext);
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
    delete pNode;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::remove(iterator& i)
{
    if (!pFirst || !i.pNode)
        throw TListException::NodeNotFound();
    TNode* needle = i.pNode;
    if (pFirst == needle)
    {
        TNode* pNode = pFirst;
        pFirst = pFirst->pNext;
        delete pNode;
        return;
    }
    TNode* temp = pFirst;
    while (temp->pNext && (temp->pNext != needle))
        temp = temp->pNext;
    if (!temp->pNext)
        throw TListException::NodeNotFound();
    temp->pNext = needle->pNext;
    delete needle;
    i.pNode = nullptr;

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
        if (temp->data)
            stream << *(temp->data);
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
        if (temp->data)
            stream << *(temp->data);
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
typename TNodeTypename* TListIterator<TNodeTypename>::operator*() const
{
    return pNode;
}

template <typename TNodeTypename>
TListIterator<TNodeTypename> TListIterator<TNodeTypename>::operator++()
{
    if (pNode)
        pNode = pNode->pNext;
    return *this;
}

template <typename TNodeTypename>
TListIterator<TNodeTypename> TListIterator<TNodeTypename>::operator++(int)
{
    TNodeTypename* temp = pNode;
    if (pNode)
        pNode = pNode->pNext;
    return TListIterator<TNodeTypename>(temp);
}

#endif // !_TLIST_H_