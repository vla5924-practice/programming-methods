#include <cstdlib>
#include <ctime>
#include "TList.h"
#define RANDOM (rand() % 100)

int main()
{
    TList<int, void*> list;
    srand(static_cast<unsigned>(time(0)));
    int randoms[] = { RANDOM, RANDOM, RANDOM, RANDOM, RANDOM, RANDOM, RANDOM, RANDOM, RANDOM, RANDOM };
    std::cout << "Empty list:\n";
    list.outputRaw(std::cout);
    std::cout << "\nInsert " << randoms[0] << ", " << randoms[1] << " to end: \n";
    list.insertToEnd(randoms[0]);
    list.insertToEnd(randoms[1]);
    list.outputRaw(std::cout);
    std::cout << "\nInsert " << randoms[2] << ", " << randoms[3] << " to start: \n";
    list.insertToStart(randoms[2]);
    list.insertToStart(randoms[3]);
    list.outputRaw(std::cout);
    std::cout << "\nFind " << randoms[1] << " and modify to " << randoms[4] << ": \n";
    auto node = list.find(randoms[1]);
    node.key = randoms[4];
    list.outputRaw(std::cout);
    std::cout << "\nInsert " << randoms[5] << " after " << randoms[2] << ", " << randoms[6] << " after " << randoms[4] << ": \n";
    list.insertAfter(randoms[2], randoms[5]);
    list.insertAfter(randoms[4], randoms[6]);
    list.outputRaw(std::cout);
    std::cout << "\nInsert " << randoms[5] << " before " << randoms[9] << ": \n";
    try
    {
        list.insertBefore(randoms[9], randoms[5]);
        std::cout << "inserted\n";
    }
    catch (TListException::NodeNotFound& e)
    {
        std::cerr << e.what();
    }
    std::cout << "\nInsert " << randoms[7] << " before " << randoms[0] << ", " << randoms[8] << " before " << randoms[3] << ": \n";
    list.insertBefore(randoms[0], randoms[7]);
    list.insertBefore(randoms[3], randoms[8]);
    list.outputRaw(std::cout);
    std::cout << "\nInsert " << randoms[5] << " after " << randoms[9] << ": \n";
    try
    {
        list.insertAfter(randoms[9], randoms[5]);
        std::cout << "inserted\n";
    }
    catch (TListException::NodeNotFound& e)
    {
        std::cerr << e.what();
    }
    std::cout << "\nFind " << randoms[9] << ": \n";
    node = list.find(randoms[9]);
    std::cout << (node ? "found\n" : "not found\n");
    std::cout << "\nRemove " << randoms[7] << ":\n";
    list.remove(randoms[7]);
    list.outputRaw(std::cout);
    std::cout << "\Remove " << randoms[9] << ": \n";
    try
    {
        list.remove(randoms[9]);
        std::cout << "removed\n";
    }
    catch (TListException::NodeNotFound& e)
    {
        std::cerr << e.what();
    }
    std::cout << "\nIterating (output example):\n";
    for (auto i : list)
        std::cout << i.key << ' ';
    std::cout << "\nIterating (all keys " << randoms[9] << " assuming example):\n";
    for (auto i : list)
        i.key = randoms[9];
    list.outputRaw(std::cout);
    std::cout << "\nRemove all:\n";
    list.removeAll();
    list.outputRaw(std::cout);

    
}