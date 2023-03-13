#include <iostream>
#include <math.h>
#include <D:\Xixijan\repos\Small_C++_Projects\basic_get_functions.h>

using namespace std;

int get_size();
void create_array_power_by_two(int size, int power_up[]);
void print_array(int size, int power_up[]);

int main()
{
	// Get the size from user
	int size = get_size();
	int* power_up = new int[size];
	// Dinamicaly create a array of that size where each element is 2 times the previous one
	create_array_power_by_two(size, power_up);
	// Print the array, integer by integer
	print_array(size, power_up);

	delete[] power_up;

	return 0;
}

int get_size()
{
	int size;
	do
	{
		size = get_valid_input<int>("Enter size of array: ");
	} while (size < 1);
	return size;
}

void create_array_power_by_two(int size, int power_up[])
{
	for (int i = 0; i < size; i++)
	{
		power_up[i] = pow(2, i);
	}
}

void print_array(int size, int power_up[])
{
	for (int i = 0; i < size; i++)
	{
		cout << power_up[i] << endl;
	}
}