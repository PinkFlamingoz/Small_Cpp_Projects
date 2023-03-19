#include <iostream>

using namespace std;

void allocateMemory(int*& variable3);

int main()
{
	// - & - REFERENCE ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// int& variable1: This is a reference to an integer variable.
	// It means that variable1 is an alias or an alternate name for an existing integer variable.
	// Any changes made to variable1 will affect the original variable it refers to.

	int x = 10;
	int& variable1 = x; // variable1 is a reference to x

	cout << "x = " << x << endl; // prints x = 10
	cout << "variable1 = " << variable1 << endl; // prints variable1 = 10

	variable1 = 20; // changes the value of x
	cout << "x = " << x << endl; // prints x = 20
	cout << "variable1 = " << variable1 << endl; // prints variable1 = 20

	// - & - REFERENCE ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// - * - POINTER ------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// int* variable2: This is a pointer variable that holds the memory address of an integer variable.
	// It means that variable2 is a pointer variable that can store the address of an integer variable.
	// To access the value stored at the memory address variable2 points to, you need to use the dereference operator *.

	// &y: This is the address-of operator used to get the memory address of a variable.
	// It means that &y returns the memory address of the variable y.
	// This operator is often used to pass the memory address of a variable as a parameter to a function or to initialize a pointer variable with the address of another variable.

	int y = 10;
	int* variable2 = &y; // pointer variable2 holds the address of y

	cout << "y = " << y << endl; // prints y = 10
	cout << "variable2 = " << variable2 << endl; // prints the memory address of y

	*variable2 = 20; // changes the value of y
	cout << "y = " << y << endl; // prints y = 20
	cout << "variable2 = " << variable2 << endl; // prints the memory address of y

	// - * - POINTER ------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// - *& - REFERENCE TO A POINTER --------------------------------------------------------------------------------------------------------------------------------------------------------

	// int*& variable3: This is a reference to a pointer variable.
	// It means that variable3 is an alias or an alternate name for an existing pointer variable.
	// Any changes made to variable3 will affect the original pointer variable it refers to.

	int* variable3 = nullptr; // initialize pointer variable3 to nullptr

	allocateMemory(variable3); // dynamically allocate memory for variable3

	*variable3 = 10; // set the value of variable3 to 10
	cout << "variable3 = " << *variable3 << endl; // prints variable3 = 10

	delete variable3; // deallocate the memory

	// In this example, variable3 is a reference to a pointer variable that can store the memory address of an integer variable.
	// The allocateMemory function takes a reference to a pointer variable and dynamically allocates memory for an integer using the new operator.
	// The program initializes variable3 to nullptr,
	// calls allocateMemory to allocate memory for variable3,
	// sets the value of variable3 to 10,
	// prints the value of variable3,
	// deallocates the memory using the delete operator,
	// and returns 0.
	// Since variable3 is a reference to the pointer variable, any changes made to variable3 inside the function allocateMemory will be reflected in the original variable outside the function.

	// - *& - REFERENCE TO A POINTER --------------------------------------------------------------------------------------------------------------------------------------------------------
	return 0;
}

void allocateMemory(int*& variable3)
{
	variable3 = new int; // dynamically allocate memory for an integer
}