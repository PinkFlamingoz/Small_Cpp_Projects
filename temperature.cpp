#include <iostream>
#include "basic_functions.h"

using namespace std;

// Structures
struct Temperature
{
	string city = "";
	int temp = 0;
};

// Functions
int get_size();
void fill_temperatures_array(int size, Temperature temperatures[]);
Temperature get_temperatures_and_names(string prompt, int num);
void print_data(int size, Temperature temperatures[]);
void sort_data_bubble(int size, Temperature temperatures[]);

int main()
{
	int size = get_size(); //---------------------------- Get the size of the database
	Temperature *temperatures = new Temperature[size]; // Make a dynamic array with that size

	fill_temperatures_array(size, temperatures); //------ Set the values from the user in the temperatures structure array

	sort_data_bubble(size, temperatures); //------------- Sort the temperatures structure array using the bubble sort algoritam

	print_data(size, temperatures); //------------------- Print the sorted data

	delete[] temperatures; //---------------------------- Free up the allocated memory

	return 0; //----------------------------------------- Success
}

// Get the size of the database
int get_size()
{
	int size = 0;
	do
	{
		size = get_valid_input<int>("Enter size of database: ");
	} while (size < 1);
	return size;
}

//* Fill in the temperatures structure array --------------------------------------------------------------------------------------------------------------
void fill_temperatures_array(int size, Temperature temperatures[])
{
	for (int i = 0; i < size; i++)
	{
		temperatures[i] = get_temperatures_and_names("Enter Data --------------", i);
	}
}

// Get the values of each city aka their names and temperatures
Temperature get_temperatures_and_names(string prompt, int num)
{
	cout << prompt << " " << num << endl;

	Temperature temporary;
	temporary.city = get_valid_input<string>("Enter city: ");
	temporary.temp = get_valid_input<int>("Enter temperature: ");
	return temporary;
}
//* Fill in the temperatures structure array --------------------------------------------------------------------------------------------------------------

// Print the data
void print_data(int size, Temperature temperatures[])
{
	for (int i = 0; i < size; i++)
	{
		cout << temperatures[i].city << ": " << temperatures[i].temp << endl;
	}
}

// Bubble Sort
void sort_data_bubble(int size, Temperature temperatures[])
{
	int swap_counter = -1; //-------------------------------------- Set swap counter to a non-zero value
	Temperature help; //------------------------------------------- When copying one struct to another, no need to assign individual elements. The entire struct can be assigned in one statement
	while (swap_counter != 0) //----------------------------------- Repeat until the swap counter is 0
	{
		swap_counter = 0; //--------------------------------------- Reset swap counter to 0
		for (int i = 0; i < size - 1; i++)
		{
			if (temperatures[i].temp < temperatures[i + 1].temp) // Look at each adjacent pair, if two adjacent elements are not in order, swap them
			{
				help = temperatures[i];
				temperatures[i] = temperatures[i + 1];
				temperatures[i + 1] = help;
				swap_counter++; //--------------------------------- Add one to the swap counter
			}
		}
	}
}