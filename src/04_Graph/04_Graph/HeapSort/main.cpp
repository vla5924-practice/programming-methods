#include <iostream>
#include "../Lib/THeap.h"

int main()
{
    int arr[] = { 5, 3, 4, -1, 0, 10, 3, 0, 7, 6 };
    THeap<int> heap(arr, 10, [](int n) { return n; });
}