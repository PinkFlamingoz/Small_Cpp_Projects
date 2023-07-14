#include <iostream>
#include "headers/basic_functions.h"

using namespace std;

// Functions
int get_populationStart();
int get_populationEnd(int n);
int calculate_years(int start, int end);
void print_years(int years);

int main()
{
	int start = get_populationStart(); //------ Get size of the population at start
	int end = get_populationEnd(start); //----- Get size of the population at the end make sure it does not go under start

	int years = calculate_years(start, end); // Calculate how many years it will take to reach that population

	print_years(years); //--------------------- Print the years

	return 0; //------------------------------- Success
}

//Get the size of the population at start
int get_populationStart()
{
	int start = 0;
	do
	{
		start = get_valid_input<int>("Enter size of start population: ");
	} while (start < 9);
	return start;
}

// Get size of the population at the end make sure it does not go under start
int get_populationEnd(int n)
{
	int end = 0;
	do
	{
		end = get_valid_input<int>("Enter size of end population: ");
	} while (end < n);
	return end;
}

// Calculate how many years it will take to reach that population
int calculate_years(int start, int end)
{
	int years = 0;
	while (start < end)
	{
		start = start + start / 3 - start / 4;
		years++;
	}
	return years;
}

// Print the years
void print_years(int years)
{
	cout << "It will take (year/s): " << years << "!" << endl;
}