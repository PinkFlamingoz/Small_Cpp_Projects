#include <iostream>
#include "headers/basic_functions.h"

using namespace std;

// Functions
int get_size();
void fill_array(int size, int array[]);
char get_max_or_min();
int max(int size, int array[]);
int min(int size, int array[]);
void print_results(char answer, int size, int array[]);

int main()
{
	int size = get_size(); //------------- Get the size for an array
	int *array = new int[size]; //-------- Make a dynamic array with that size

	fill_array(size, array); //----------- Fill that array with user inputed values

	char answer = get_max_or_min(); //---- Get the max, min or both

	print_results(answer, size, array); // Print the results

	delete[] array; //-------------------- Free up the allocated memory

	return 0; //-------------------------- Success
}

// Get the size of the array
int get_size()
{
	int size = 0;
	do
	{
		size = get_valid_input<int>("Enter size: ");
	} while (size < 1);
	return size;
}

// Fill up the array with user inputed values
void fill_array(int size, int array[])
{
	for (int i = 0; i < size; i++)
	{
		array[i] = get_valid_input<int>("Enter value: ");
	}
}

// Get from user to see max or min
char get_max_or_min()
{
	char answer = get_valid_input<char>("Max(1) or Min(2): ");
	return answer;
}

// Get the max element in the array
int max(int size, int array[])
{
	int max = array[0];
	for (int i = 1; i < size; i++)
	{
		if (max < array[i])
		{
			max = array[i];
		}
	}
	return max;
}

// Get the min element in the array
int min(int size, int array[])
{
	int min = array[0];
	for (int i = 1; i < size; i++)
	{
		if (min > array[i])
		{
			min = array[i];
		}
	}
	return min;
}

// Print the result depending on the answer in a switch case
void print_results(char answer, int size, int array[])
{
	switch (answer)
	{
		case'1':
		{
			cout << "Max is: " << max(size, array) << endl;
			break;
		}
		case'2':
		{
			cout << "Min is: " << min(size, array) << endl;
			break;
		}
		default:
		{
			cout << "Max is: " << max(size, array) << endl;
			cout << "Min is: " << min(size, array) << endl;
			break;
		}
	}
}