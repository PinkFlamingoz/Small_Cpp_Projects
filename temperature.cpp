#include <iostream>
#include "basic_functions.h"

using namespace std;

struct Temperature
{
	string city = "";
	int temp = 0;
};

int get_size();
Temperature get_temperatures_and_names(string prompt, int num);
void fill_temperatures_array(int size, Temperature temperatures[]);
void print_data(int size, Temperature temperatures[]);
void sort_data_bubble(int size, Temperature temperatures[]);

int main()
{
	int size = get_size();
	Temperature *temperatures = new Temperature[size];

	fill_temperatures_array(size, temperatures);

	sort_data_bubble(size, temperatures);

	print_data(size, temperatures);

	delete[] temperatures;

	return 0;
}

int get_size()
{
	int size = 0;
	do
	{
		size = get_valid_input<int>("Enter size of database: ");
	} while (size < 1);
	return size;
}

Temperature get_temperatures_and_names(string prompt, int num)
{
	cout << prompt << " " << num << endl;

	Temperature temporary;

	temporary.city = get_valid_input<string>("Enter city: ");
	temporary.temp = get_valid_input<int>("Enter temperature: ");

	return temporary;
}

void fill_temperatures_array(int size, Temperature temperatures[])
{
	for (int i = 0; i < size; i++)
	{
		temperatures[i] = get_temperatures_and_names("Enter Data --------------", i);
	}
}

void print_data(int size, Temperature temperatures[])
{
	for (int i = 0; i < size; i++)
	{
		cout << temperatures[i].city << ": " << temperatures[i].temp << endl;
	}
}

void sort_data_bubble(int size, Temperature temperatures[])
{
	int swap_counter = -1;
	Temperature help;							// When copying one struct to another, no need to assign individual elements. The entire struct can be assigned in one statement
	while (swap_counter != 0)
	{
		swap_counter = 0;
		for (int i = 0; i < size - 1; i++)
		{
			if (temperatures[i].temp < temperatures[i + 1].temp)
			{
				help = temperatures[i];
				temperatures[i] = temperatures[i + 1];
				temperatures[i + 1] = help;
				swap_counter++;
			}
		}
	}
}