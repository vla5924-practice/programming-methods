#include "pch.h"
#include <xutility>
#include "../Lib/THeap.h"

constexpr int arraySize = 8;
int controlArray[] = { -5, 0, 14, 3, -2, 1, 0, 7 };
int sortedArray[]  = { 14, 7, 3, 1, 0, 0, -2, -5 };

TEST(THeap, can_create_heap_with_positive_size) 
{
    ASSERT_NO_THROW(THeap<int> heap(controlArray, arraySize));
}

TEST(THeap, cannot_create_heap_with_negative_size) 
{
    EXPECT_ANY_THROW(THeap<int> heap(controlArray, -1));
}

TEST(THeap, can_heapify)
{
    THeap<int> heap(controlArray, arraySize);
    EXPECT_EQ(-5, controlArray[0]);
    /* ... */
}

TEST(THeap, can_check_is_full)
{
    THeap<int> heap(controlArray, arraySize);
    EXPECT_TRUE(heap.full());
}

TEST(THeap, can_get_top_element)
{
    THeap<int> heap(controlArray, arraySize);
    EXPECT_EQ(-5, heap.popMin());
    EXPECT_EQ(false, heap.full());
}

TEST(THeap, can_sort)
{
    THeap<int> heap(controlArray, arraySize);
    ASSERT_NO_THROW(heap.sort());
}

TEST(THeap, can_sort_correctly)
{
    THeap<int> heap(controlArray, arraySize);
    EXPECT_TRUE(std::equal(controlArray, controlArray + arraySize, sortedArray, sortedArray + arraySize));
}