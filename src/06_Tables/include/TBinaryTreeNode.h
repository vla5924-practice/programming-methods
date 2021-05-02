#ifndef _TBINARYTREENODE_H_
#define _TBINARYTREENODE_H_

template <typename TKey, typename TData>
class TBinaryTreeNode
{
protected:
    template<typename, typename> friend class TBinaryTree;
    template<typename> friend class TBinaryTreeIterator;
    TKey key;
    TBinaryTreeNode<TKey, TData>* left;
    TBinaryTreeNode<TKey, TData>* right;
    TBinaryTreeNode<TKey, TData>* parent;
public:
    TData* data;
    explicit TBinaryTreeNode(TKey key_, TData* data_ = nullptr, 
        TBinaryTreeNode* parent_ = nullptr, TBinaryTreeNode* left_ = nullptr, 
        TBinaryTreeNode* right_ = nullptr);
    TKey getKey() const { return key; };
};

template<typename TKey, typename TData>
TBinaryTreeNode<TKey, TData>::TBinaryTreeNode(TKey key_, TData* data_, 
    TBinaryTreeNode* parent_, TBinaryTreeNode* left_, TBinaryTreeNode* right_)
    : key(key_), data(data_), parent(parent_), left(left_), right(right_)
{
}

#endif
