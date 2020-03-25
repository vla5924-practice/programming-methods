#include <iostream>
#include <random>
#include "THeap.h"

constexpr int size = 10;

int main()
{
    std::random_device rd;
    std::mt19937_64 generator(rd()); // Mersenne

    int arr[size] = { 0 };
    for (int i = 0; i < size; i++)
        arr[i] = static_cast<int>(generator() % 1000U);

    THeap<int> heap(arr, size);
    heap.sort();
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << ' ';
}