#ifndef _TBINARYTREE_H_
#define _TBINARYTREE_H_
#define _TBinaryTreeIter typename TBinaryTree<TKey, TData>::Iterator
#define _TBinaryTreeNode typename TBinaryTree<TKey, TData>::Node

#include "TBinaryTreeNode.h"
#include "TBinaryTreeIterator.h"
#include "TPair.h"

template <typename TKey, typename TData>
class TBinaryTree
{
public:
    using Node = TBinaryTreeNode<TKey, TData>;
    using Iterator = TBinaryTreeIterator<TBinaryTree<TKey, TData>>;
    using Key = TKey;
    using Data = TData;
    using Pair = TPair<TKey, TData>;

protected:
    Node* root_;
    inline Iterator makeIter(Node* node) const;
    static Node* findMax(Node* root);
    static Node* findMin(Node* root);
    static Node* findPrev(Node* root);
    static Node* findNext(Node* root);

public:
    TBinaryTree();
    TBinaryTree(const TBinaryTree& other);
    TBinaryTree(TBinaryTree&& other);
    ~TBinaryTree();

    inline bool owns(const Iterator& iter) const;
    inline Iterator root() const;
    inline Iterator null() const;
    inline Iterator notFound() const;

    Iterator find(const TKey& needle) const;
    Iterator findMax() const;
    Iterator findMin() const;
    Iterator findNext(const Iterator& iter) const;
    Iterator findPrev(const Iterator& iter) const;

    void insert(const TKey& key, TData* data = nullptr);
    void remove(const TKey& key);
    void remove(Iterator& iter);
};

template<typename TKey, typename TData>
inline _TBinaryTreeIter TBinaryTree<TKey, TData>::makeIter(Node* node) const
{
    return Iterator(this, node);
}

template<typename TKey, typename TData>
_TBinaryTreeNode* TBinaryTree<TKey, TData>::findMax(Node* root)
{
    if (root_ == nullptr)
        return nullptr;
    Node* current = root;
    while (current->right != nullptr)
        current = current->right;
    return current;
}

template<typename TKey, typename TData>
_TBinaryTreeNode* TBinaryTree<TKey, TData>::findMin(Node* root)
{
    if (root_ == nullptr)
        return nullptr;
    Node* current = root;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

template<typename TKey, typename TData>
_TBinaryTreeNode* TBinaryTree<TKey, TData>::findPrev(Node* node)
{
    if (node == nullptr)
        return nullptr;
    Node* result = nullptr;
    Node* current = node;
    if (current->left != nullptr)
    {
        result = findMax(current->left);
        return result;
    }
    result = current->parent;
    Node* temp = current;
    while ((result != nullptr) && (temp == result->left))
    {
        temp = result;
        result = result->parent;
    }
    return result;
}

template<typename TKey, typename TData>
_TBinaryTreeNode* TBinaryTree<TKey, TData>::findNext(Node* node)
{
    if (node == nullptr)
        return nullptr;
    Node* result = nullptr;
    Node* current = node;
    if (current->right != nullptr)
    {
        result = findMin(current->right);
        return result;
    }
    result = current->parent;
    Node* temp = current;
    while ((result != nullptr) && (temp == result->right))
    {
        temp = result;
        result = result->parent;
    }
    return result;
}

template<typename TKey, typename TData>
TBinaryTree<TKey, TData>::TBinaryTree()
    : root_(nullptr)
{
}

template<typename TKey, typename TData>
TBinaryTree<TKey, TData>::TBinaryTree(const TBinaryTree& other)
    : root_(other.root_)
{
    // TODO
}

template<typename TKey, typename TData>
TBinaryTree<TKey, TData>::TBinaryTree(TBinaryTree&& other)
    : root(other.root_)
{
    other.root_ = nullptr;
}

template<typename TKey, typename TData>
TBinaryTree<TKey, TData>::~TBinaryTree()
{
    // TODO
}

template<typename TKey, typename TData>
inline bool TBinaryTree<TKey, TData>::owns(const Iterator& iter) const
{
    return iter.owningTree == this;
}

template<typename TKey, typename TData>
inline _TBinaryTreeIter TBinaryTree<TKey, TData>::root() const
{
    return Iterator(this, root_);
}

template<typename TKey, typename TData>
inline _TBinaryTreeIter TBinaryTree<TKey, TData>::null() const
{
    return Iterator(this, nullptr);
}

template<typename TKey, typename TData>
inline _TBinaryTreeIter TBinaryTree<TKey, TData>::notFound() const
{
    return Iterator(this, nullptr);
}

template<typename TKey, typename TData>
_TBinaryTreeIter TBinaryTree<TKey, TData>::find(const TKey& needle) const
{
    Iterator iter = root();
    while (iter.isAccessible() && iter.key() != needle)
    {
        if (needle < iter.key())
            iter.toLeft();
        else
            iter.toRight();
    }
    return iter;
}

template<typename TKey, typename TData>
_TBinaryTreeIter TBinaryTree<TKey, TData>::findMax() const
{
    Node* node = findMax(root_);
    return makeIter(node);
}

template<typename TKey, typename TData>
_TBinaryTreeIter TBinaryTree<TKey, TData>::findMin() const
{
    Node* node = findMin(root_);
    return makeIter(node);
}

template<typename TKey, typename TData>
_TBinaryTreeIter TBinaryTree<TKey, TData>::findNext(const Iterator& iter) const
{
    if (!owns(iter) || !iter.isAccessible())
        return null();
    Node* result = findNext(iter.node);
    return makeIter(result);
}

template<typename TKey, typename TData>
_TBinaryTreeIter TBinaryTree<TKey, TData>::findPrev(const Iterator& iter) const
{
    if (!owns(iter) || !iter.isAccessible())
        return null();
    Node* result = findPrev(iter.node);
    return makeIter(result);
}

template<typename TKey, typename TData>
void TBinaryTree<TKey, TData>::insert(const TKey& key, TData* data)
{
    Node* node = new Node(key, data);
    if (root_ == nullptr)
    {
        root_ = node;
        return;
    }
    Node* temp = root_;
    Node* parent = nullptr;
    while (temp != nullptr)
    {
        parent = temp;
        if (node->key < temp->key)
            temp = temp->left;
        else
            temp = temp->right;
    }
    node->parent = parent;
    if (node->key < parent->key)
        parent->left = node;
    else
        parent->right = node;
}

template<typename TKey, typename TData>
void TBinaryTree<TKey, TData>::remove(const TKey& key)
{
    Iterator needle = find(key);
    remove(needle);
}

template<typename TKey, typename TData>
void TBinaryTree<TKey, TData>::remove(Iterator& iter)
{
    if (!owns(iter) || !iter.isAccessible())
        return;
    Node* z = iter.node;
    Node* y = nullptr;
    Node* x = nullptr;
    if ((z->left != nullptr) && (z->right != nullptr))
        y = findNext(z); // z has 2 parents
    else
        y = z; // z has 0 or 1 parent
    if (y->left != nullptr)
        x = y->left;
    else
        x = y->right;
    if (x != nullptr)
        x->parent = y->parent;
    if (y->parent != nullptr)
    {
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }
    if (y != z)
    {
        z->key = y->key;
        // delete z->data;
        z->data = y->data;
        delete y; // (?)
    }
    else
        delete z; // (?)
    iter.node = nullptr;
}

#endif
