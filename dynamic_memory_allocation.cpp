#include <iostream>
#include "basic_get_functions.h"

using namespace std;

long get_input();

int main()
{
	long size = get_input();

	int *p = nullptr;
	try
	{						// int* p = new int(42);  dynamically allocate a single integer initialized with the value 42
		p = new int[size];  // int* p = new int;   dynamically allocate a single integer
	}
	catch (const bad_alloc &e)
	{
		cout << "Memory allocation failed: " << e.what() << endl;
		return 1;
	}

	delete[] p;

	// =====================================================================================

	int *cp = nullptr;
	cp = (int *)malloc(size * sizeof(int)); // int* cp = (int *)malloc(sizeof(int));   dynamically allocate a single integer
	if (cp == nullptr)
	{
		cout << "Memory allocation failed! " << endl;
		return 1;
	}
	free(cp);

	return 0;
}

long get_input()
{
	long number;
	do
	{
		number = get_valid_input<long>("Enter size of memory allocation: ");
	} while (number < 1);
	return number;
}