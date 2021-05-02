#ifndef _TITERATOR_H_
#define _TITERATOR_H_

template <typename T>
class THIterator
{
protected:
    template<typename, typename> friend class THashTable;
    T* ptr;
public:
    explicit TIterator(T* ptr_) : ptr(ptr_) {};
    TIterator(const TIterator&) = default;
    TIterator<T>& operator++(int) { ptr++; return *this; };
    TIterator<T>& operator--(int) { ptr--; return *this; };
    T operator*() { return *ptr; };
    T operator()() { return *ptr; };
    bool operator==(const TIterator& other) { return ptr == other.ptr; }
    bool operator!=(const TIterator& other) { return ptr != other.ptr; }
    operator bool() { return ptr != nullptr; }
};

#endif