#include <iostream>
#include <math.h>
#include "basic_functions.h"

using namespace std;

// Functions
int get_size();
void create_array_power_by_two(int size, int power_up[]);
void print_array(int size, int power_up[]);

int main()
{
	int size = get_size(); 	//------------------- Get the size from user
	int *power_up = new int[size]; 	//----------- Make a dynamic array with that size

	create_array_power_by_two(size, power_up); // Raze every integer to the power of 2

	print_array(size, power_up); //-------------- Print the array, integer by integer

	delete[] power_up; //------------------------ Free up the allocated memory

	return 0; //--------------------------------- Success
}

// Get the size for the dynamic array
int get_size()
{
	int size = 0;
	do
	{
		size = get_valid_input<int>("Enter size of array: ");
	} while (size < 1);
	return size;
}

// Raze every integer to the power of 2
void create_array_power_by_two(int size, int power_up[])
{
	for (int i = 0; i < size; i++)
	{
		power_up[i] = pow(2, i);
	}
}

// Print the array, integer by integer
void print_array(int size, int power_up[])
{
	for (int i = 0; i < size; i++)
	{
		cout << power_up[i] << endl;
	}
}