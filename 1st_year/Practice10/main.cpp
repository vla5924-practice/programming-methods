#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "Container.h"

void generate(int*, int);
int random();
void print(Container<int>);
void print(Container<int*>);

int main()
{
	int example[10];
	generate(example, 10);
	int needle = random(), needle2 = random();

	std::cout << "TEST #1: SIMPLE CONTAINER\n";
	Container<int> c;
	std::cout << "Adding: ";
	for (int i = 0; i < 10; i++)
		c.add(example[i]), std::cout << c[i] << ' '; // operator[] test
	std::cout << "\nSet element [" << needle << "] to " << needle2 << ": ";
	try
	{
		c[needle] = needle2;
		std::cout << "success  ";
	}
	catch (std::out_of_range)
	{
		std::cout << "index is too big  ";
	}
	print(c);
	std::cout << "Size: " << c.size() << '\n';
	std::cout << "Is empty: " << (c.empty() ? "true" : "false") << '\n';

	std::cout << "Find (value = " << needle << "): ";
	int index = c.find(needle);
	if (index != -1)
		std::cout << "found on index " << index << '\n';
	else
		std::cout << "not found\n";

	std::cout << "Remove (value = " << needle2 << "): ";
	try
	{
		c.remove(needle2);
		std::cout << "deleted  ";
	}
	catch (std::range_error)
	{
		std::cout << "not found  ";
	}
	print(c);

	std::cout << "Remove (index = " << needle << "): ";
	try
	{
		c.iremove(needle);
		std::cout << "deleted  ";
	}
	catch (std::out_of_range)
	{
		std::cout << "index is too big  ";
	}
	print(c);

	Container<int> cc = c;
	std::cout << "Copying to container: ";
	print(cc);

	//////////////////////////////////////////////////////////////////////////

	generate(example, 10);
	needle = random(), needle2 = random();

	std::cout << "\nTEST #2: POINTERS CONTAINER\n";
	Container<int*> c2;
	std::cout << "Adding: ";
	for (int i = 0; i < 5; i++)
		c2.add(example + i), std::cout << *(c2[i]) << ' ';
	for (int i = 5; i < 9; i++)
	{
		int* ptr = new int(example[i]);
		c2.add(ptr), std::cout << *(c2[i]) << ' ';
	}
	int* ptr = new int(example[9]);
	c2.add(ptr), std::cout << *(c2[9]) << '\n';
	std::cout << "Set element [" << needle << "] to &" << needle2 << ": ";
	try
	{
		c2[needle] = new int(needle2);
		std::cout << "success  ";
	}
	catch (std::out_of_range)
	{
		std::cout << "index is too big  ";
	}
	print(c2);
	std::cout << "Size: " << c2.size() << '\n';
	std::cout << "Is empty: " << (c2.empty() ? "true" : "false") << '\n';

	std::cout << "Find (value = " << needle << "): ";
	index = c2.find(needle);
	if (index != -1)
		std::cout << "found on index " << index << '\n';
	else
		std::cout << "not found\n";

	std::cout << "Remove (value = " << needle2 << "): ";
	try
	{
		c2.remove(needle2);
		std::cout << "deleted  ";
	}
	catch (std::range_error)
	{
		std::cout << "not found  ";
	}
	print(c2);

	std::cout << "Remove (index = " << needle << "): ";
	try
	{
		c2.iremove(needle);
		std::cout << "deleted  ";
	}
	catch (std::out_of_range)
	{
		std::cout << "index is too big  ";
	}
	print(c2);

	Container<int*> cc2 = c2;
	std::cout << "Copying to container: ";
	print(cc2);
	std::cout << "Let's modify: ";
	try
	{
		*(cc2[0]) = random();
		std::cout << "success  ";
	}
	catch (std::out_of_range)
	{
		std::cout << "index is unaccessible  ";
	}
	print(cc2);
	std::cout << "Base container: ";
	print(c2);
}

void generate(int* a, int count)
{
	srand((unsigned)time(0));
	for (int i = 0; i < count; i++)
		a[i] = random();
}

int random()
{
	return rand() % 11;
}

void print(Container<int> c)
{
	std::cout << "{ ";
	for (ContainerIterator<int> i = c.begin(); i != c.end(); ++i)
		std::cout << *i << ' ';
	std::cout << "}\n";
}

void print(Container<int*> c)
{
	std::cout << "{ ";
	for (ContainerIterator<int*> i = c.begin(); i != c.end(); ++i)
		std::cout << *(*i) << ' ';
	std::cout << "}\n";
}