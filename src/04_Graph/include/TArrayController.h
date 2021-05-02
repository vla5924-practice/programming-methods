#ifndef _TARRAYCONTROLLER_H_
#define _TARRAYCONTROLLER_H_

#include "THeap.h"

class TArrayController
{
public:
    template<typename TData>
    static void heapSort(TData* arr, int size);
};

template<typename TData>
void TArrayController::heapSort(TData* arr, int size)
{
    THeap<TData> heap(arr, size);
    while (!heap.empty())
    {
        int heapSize = heap.getSize();
        TData elem = heap.topMin();
        heap.popMin();
        arr[heapSize - 1] = elem;
    }
}

#endif