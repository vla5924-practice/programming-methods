#include "TList.h"

int main()
{
    TList<int, int> list;
    list.outputRaw(std::cout);
    int* num1 = new int(4);
    std::cout << "\nInsert 1, 5 to end: \n";
    list.insertToEnd(1, num1);
    list.insertToEnd(5, nullptr);
    list.outputRaw(std::cout);
    std::cout << "\nInsert 2, 8 to end: \n";
    list.insertToStart(2, num1);
    list.insertToStart(8, nullptr);
    list.outputRaw(std::cout);
    std::cout << "\nFind 2 and modify to 16: \n";
    auto node = list.find(2);
    std::cout << node.key << ' ' << *(node.pData) << '\n';
    node.key = 16;
    list.outputRaw(std::cout);
    std::cout << "\nInsert 9 after 5, 17 after 1: \n";
    list.insertAfter(5, 9);
    list.insertAfter(1, 17);
    list.outputRaw(std::cout);
    std::cout << "\nInsert 32 before 8, 400 before 5: \n";
    list.insertBefore(8, 32);
    list.insertBefore(5, 400);
    list.outputRaw(std::cout);
    std::cout << "\nFind unknown: \n";
    node = list.find(5000);
    std::cout << (node ? "found\n" : "not found\n");
}