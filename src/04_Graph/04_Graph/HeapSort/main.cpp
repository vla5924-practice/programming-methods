#include <iostream>
#include "../Lib/TestClass.h"

int main()
{
    std::cout << "Hello World!\n"; 
    TestClass c;
    std::cout << c.echo(12345);
    c.helloWorld();
}