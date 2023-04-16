#include <iostream>
#include "basic_functions.h"

using namespace std;

// Functions
int get_input();

int main()
{
	int size = get_input(); // Get the size of the memory we want to allocate

	//* C++ Style -----------------------------------------------------------------------------------------------------------------------
	int *p = nullptr; //------- Set the pointer to null if it doesn't point to anything

	p = new int[size]; //------ Dynamically allocate memory for array

	// int* p = new int; //---- Dynamically allocate a single integer
	// int* p = new int(42); // Dynamically allocate a single integer initialized with the value 42

	delete[] p; //------------- Free up the allocated memory
	//* C++ Style -----------------------------------------------------------------------------------------------------------------------

	//* C Style -------------------------------------------------------------------------------------------------------------------------
	int *cp = nullptr; //---------------------- Set the pointer to null if it doesn't point to anything

	cp = (int *)malloc(size * sizeof(int)); //- Dynamically allocate memory for array

	// int* cp = (int *)malloc(sizeof(int)); // Dynamically allocate a single integer

	if (cp == nullptr) // --------------------- Catch if memory allocation failed
	{
		cerr << "Memory allocation failed! " << endl;
		return 1;
	}

	free(cp); //------------------------------- Free up the allocated memory
	//* C Style -------------------------------------------------------------------------------------------------------------------------

	return 0;
}

// Get the size of the memory we want to allocate
int get_input()
{
	int number = 0;
	do
	{
		number = get_valid_input<long>("Enter size of memory allocation: ");
	} while (number < 1);
	return number;
}