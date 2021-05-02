#include <iostream>
#include "TBinaryTree.h"
#include "TAVLTree.h"
#include "TOrderedTable.h"
#include "TTreeTable.h"
#include "THashTable.h"

int main()
{
    TBinaryTree<int, int> tree;
    tree.insert(1);
    tree.insert(2);
    auto iter = tree.find(2);
    std::cout << iter.key();

    TAVLTree<int, int> avl = TAVLTree<int, int>();
    auto iter3 = avl.root();
    //std::cout << iter3.key();

    TArrayTable<int, int> table1(8);
    TOrderedTable<int, int> table2(8);
    table1.insert(2);
    table1.insert(1);
    table1.insert(4);
    std::cout << table1.find(2)()->getKey();

    table2.insert(2);
    table2.insert(1);
    table2.insert(4);
    std::cout << table2.find(4)()->getKey();
    table2.remove(2);
    std::cout << table2.find(4)()->getKey();

    TTreeTable<int, int> table3;

    THashTable<int, int> table4(16);
    table4.insert(8);
    table4.insert(3);
    table4.insert(44);
    std::cout << table4.find(3)->getKey();
    table4.remove(44);
    std::cout << table4.find(3)->getKey();

    return 0;
}