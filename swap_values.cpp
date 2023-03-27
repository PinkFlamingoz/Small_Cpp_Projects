#include <iostream>
#include "basic_functions.h"

using namespace std;

// Functions
int get_value();
void swap1(int *a, int *b);
void swap2(int &a, int &b);
void print(int a, int b, string prompt);

int main()
{
	int x = get_value(); //------- Get the user input of X
	int y = get_value(); //------- Get the user input of Y

	print(x, y, "Before swap1: ");
	swap1(&x, &y); //------------- Swap using pointers
	print(x, y, "After swap1: ");
	swap2(x, y); //--------------- Swap using references
	print(x, y, "After swap2: ");

	return 0;
}

// Get the input from the user
int get_value()
{
	int number = get_valid_input<int>("Enter number: ");
	return number;
}

// Swap using pointers
void swap1(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// Swap using references
void swap2(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

// Print the input
void print(int a, int b, string prompt)
{
	cout << prompt << endl;
	cout << "A is: " << a << ", " << "B is: " << b << endl;
}