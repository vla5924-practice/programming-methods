#include "CTree.h"

void CTree::Bypass::directDepthRecursive(TNode* root)
{
    if (root == nullptr)
        return;
    std::cout << root->key << std::endl;
    directDepthRecursive(root->pLeft);
    directDepthRecursive(root->pRight);
}

void CTree::Bypass::directDepth(TNode* root)
{
    if (root == nullptr)
        return;
    std::stack<TNode*> nodes;
    nodes.push(root);
    while (!nodes.empty())
    {
        TNode* node = nodes.top();
        nodes.pop();
        std::cout << node->key << std::endl;
        if (node->pRight != nullptr)
            nodes.push(node->pRight);
        if (node->pLeft != nullptr)
            nodes.push(node->pLeft);
    }
}

void CTree::Bypass::reverseDepth(TNode* root)
{
    if (root == nullptr)
        return;
    std::stack<TNode*> nodes, rNodes;
    nodes.push(root);
    while (!nodes.empty())
    {
        TNode* node = nodes.top();
        nodes.pop();
        if (node->pLeft != nullptr)
            nodes.push(node->pLeft);
        if (node->pRight != nullptr)
            nodes.push(node->pRight);
        rNodes.push(node);
    }
    while (!rNodes.empty())
    {
        TNode* node = rNodes.top();
        rNodes.pop();
        std::cout << node->key << std::endl;
    }
}

void CTree::Bypass::width(TNode* root)
{
    if (root == nullptr)
        return;
    std::queue<TNode*> nodes;
    nodes.push(root);
    while (!nodes.empty())
    {
        TNode* node = nodes.front();
        nodes.pop();
        std::cout << node->key << std::endl;
        if (node->pLeft != nullptr)
            nodes.push(node->pLeft);
        if (node->pRight != nullptr)
            nodes.push(node->pRight);
    }
}

void CTree::Operations::countLeavesRecursive(TNode* root, int& leavesCount)
{
    if (root == nullptr)
        return;
    countLeavesRecursive(root->pLeft, leavesCount);
    countLeavesRecursive(root->pRight, leavesCount);
    if ((root->pLeft == nullptr) && (root->pRight == nullptr))
        leavesCount += 1;
}

int CTree::Operations::countLeaves(TNode* root)
{
    if (root == nullptr)
        return 0;
    std::stack<TNode*> nodes;
    int leavesCount = 0;
    nodes.push(root);
    while (!nodes.empty())
    {
        TNode* node = nodes.top();
        nodes.pop();
        if ((node->pLeft == nullptr) && (node->pRight == nullptr))
            leavesCount += 1;
        if (node->pLeft != nullptr)
            nodes.push(node->pLeft);
        if (node->pRight != nullptr)
            nodes.push(node->pRight);
    }
    return leavesCount;
}

int CTree::Operations::calculateDepthRecursive(TNode* root)
{
    if (root == nullptr)
        return -1;
    int depthLeft = calculateDepthRecursive(root->pLeft);
    int depthRight = calculateDepthRecursive(root->pRight);
    return 1 + (depthLeft > depthRight ? depthLeft : depthRight);
}

int CTree::Operations::calculateDepth(TNode* root)
{
    if (root == nullptr)
        return 0;
    std::queue<TNode*> nodes;
    std::queue<int> levels;
    nodes.push(root);
    levels.push(0);
    int depth = 0;
    while (!nodes.empty())
    {
        TNode* node = nodes.front();
        nodes.pop();
        depth = levels.front();
        levels.pop();
        if (node->pLeft != nullptr)
        {
            nodes.push(node->pLeft);
            levels.push(depth + 1);
        }
        if (node->pRight != nullptr)
        {
            nodes.push(node->pRight);
            levels.push(depth + 1);
        }
    }
    return depth;
}

TNode* CTree::Operations::copyRecursive(TNode* root)
{
    if (root == nullptr)
        return nullptr;
    TNode* pLeft;
    TNode* pRight;
    pLeft = copyRecursive(root->pLeft);
    pRight = copyRecursive(root->pRight);
    TNode* node = new TNode;
    node->key = root->key;
    node->pLeft = pLeft;
    node->pRight = pRight;
    return node;
}

TNode* CTree::Operations::copy(TNode* root)
{
    if (root == nullptr)
        return nullptr;
    std::queue<TNode*> nodes;
    nodes.push(root);
    std::queue<TNode*> copyNodes;
    TNode* copyRoot = new TNode;
    *copyRoot = *root;
    copyNodes.push(copyRoot);
    while (!nodes.empty())
    {
        TNode* node = nodes.front();
        nodes.pop();
        TNode* copyNode = copyNodes.front();
        copyNodes.pop();
        if (node->pLeft != nullptr)
        {
            nodes.push(node->pLeft);
            copyNode->pLeft = new TNode;
            *copyNode->pLeft = *node->pLeft;
            copyNodes.push(copyNode->pLeft);
        }
        if (node->pRight != nullptr)
        {
            nodes.push(node->pRight);
            copyNode->pRight = new TNode;
            *copyNode->pRight = *node->pRight;
            copyNodes.push(copyNode->pRight);
        }
    }
    return copyRoot;
}
