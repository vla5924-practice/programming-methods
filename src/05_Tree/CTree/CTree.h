#pragma once
#include <iostream>
#include <stack>
#include <queue>

struct TNode
{
    int key;
    TNode* pLeft = nullptr;
    TNode* pRight = nullptr;
};

namespace CTree
{
    namespace Bypass
    {
        void directDepthRecursive(TNode* root);
        void directDepth(TNode* root);
        void reverseDepth(TNode* root);
        void width(TNode* root);
    }

    namespace Operations
    {
        void countLeavesRecursive(TNode* root, int& leavesCount);
        int countLeaves(TNode* root);
        int calculateDepthRecursive(TNode* root);
        int calculateDepth(TNode* root);
        TNode* copyRecursive(TNode* root);
        TNode* copy(TNode* root);
    }
}