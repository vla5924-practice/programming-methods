#ifndef _TSTACK_H_
#define _TSTACK_H_

#include <string>
#include <cstring>
#include <exception>

template <typename ValueType>
class TStack
{
public:

    virtual void push(ValueType value) = 0;
    virtual ValueType top() const = 0;
    virtual void pop() = 0;

    virtual size_t height() const = 0;
    virtual bool empty() const = 0;
    virtual bool full() const = 0;

    class FullError : std::exception
    {
        const std::string whatStr = "Stack is full.";
    public:
        virtual const char* what() { return whatStr.c_str(); }
    };
    class EmptyError : std::exception
    {
        const std::string whatStr = "Stack is empty.";
    public:
        virtual const char* what() { return whatStr.c_str(); }
    };
};

#endif // !_TSTACK_H_