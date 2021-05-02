#ifndef _TAVLTREE_H_
#define _TAVLTREE_H_

#include "TBinaryTree.h"
#include "TAVLTreeNode.h"

template <typename TKey, typename TData>
class TAVLTree : public TBinaryTree<TKey, TData>
{
public:
    using BaseType = TBinaryTree<TKey, TData>;
    using Node = TAVLTreeNode<TKey, TData>;
    using Iterator = TBinaryTreeIterator<TAVLTree<TKey, TData>>;
    using Key = TKey;
    using Data = TData;
    using Pair = TPair<TKey, TData>;
protected:
    using BaseType::root_;
    TBalanceFactor leftBalancing(Node* node);
    TBalanceFactor rightBalancing(Node* node);
public:
    TAVLTree() = default;
    TAVLTree(const TAVLTree& other);
    TAVLTree(TAVLTree&& other);
    ~TAVLTree() = default;

    using BaseType::find;
    void insert(const TKey& key, TData* data = nullptr);
    void remove(const TKey& key);
    void remove(Iterator& iter);

    using BaseType::root;
    using BaseType::null;
    using BaseType::owns;
};

template<typename TKey, typename TData>
TBalanceFactor TAVLTree<TKey, TData>::leftBalancing(Node* node)
{
    TBalanceFactor balance = 0;
    switch (node->balance)
    {
    case 1:
        Node* right = reinterpret_cast<Node*>(node->right);
        if (right->balance == 1)
        {
            node->right = right->left;
            right->left = node;
            node->balance = 0;
            node = right;
        }
        else
        {
            Node* left = reinterpret_cast<Node*>(right->left);
            right->left = left->right;
            left->right = right;
            node->right = left->right;
            left->left = node;
            if (left->balance == -1)
                node->balance = -1;
            else
                node->balance = 0;
            if (left->balance == 1)
                node->balance = 1;
            else
                node->balance = 0;
            node = left;
            node->balance = 0;
        }
        balance = 0;
        break;
    case 0:
        node->balance = 1;
        balance = 1;
        break;
    case -1:
        node->balance = 0;
        balance = 0;
        break;
    return balance;
    }
}

template<typename TKey, typename TData>
TBalanceFactor TAVLTree<TKey, TData>::rightBalancing(Node* node)
{
    // TODO
    return TBalanceFactor();
}

template<typename TKey, typename TData>
TAVLTree<TKey, TData>::TAVLTree(const TAVLTree& other)
    : BaseType(other)
{
    // TODO
}

template<typename TKey, typename TData>
TAVLTree<TKey, TData>::TAVLTree(TAVLTree&& other)
{
    root_ = other.root_;
    other.root_ = nullptr;
}

template<typename TKey, typename TData>
void TAVLTree<TKey, TData>::insert(const TKey& key, TData* data)
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
void TAVLTree<TKey, TData>::remove(const TKey& key)
{
    // TODO
}

template<typename TKey, typename TData>
void TAVLTree<TKey, TData>::remove(Iterator& iter)
{
    // TODO
}

#endif