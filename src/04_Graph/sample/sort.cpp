#include <iostream>
#include <random>
#include "TArrayController.h"

int main()
{
    std::random_device rd;
    std::mt19937 generator(rd()); // Mersenne

    std::cout << "Input array size: ";
    int size = 1;
    std::cin >> size;

    int* arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = static_cast<int>(generator() % 1000U);
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';

    TArrayController::heapSort(arr, size);
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << ' ';
    std::cout << '\n';

    delete[] arr;
}