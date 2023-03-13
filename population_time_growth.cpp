#include <iostream>
#include <D:\Xixijan\repos\Small_C++_Projects\basic_get_functions.h>

using namespace std;

int get_populationStart();
int get_populationEnd(int n);
int calculate_years(int start, int end);
void print_years(int years);

int main()
{
	// Get the population input
	int start = get_populationStart();
	int end = get_populationEnd(start);

	// Calculate the start size and end size
	int years = calculate_years(start, end);

	// Print the results
	print_years(years);

	return 0;
}

int get_populationStart()
{
	int start;
	do
	{
		start = get_valid_input<int>("Enter size of start population: ");
	} while (start < 9);
	return start;
}

int get_populationEnd(int n)
{
	int end;
	do
	{
		end = get_valid_input<int>("Enter size of end population: ");
	} while (end < n);
	return end;
}

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

void print_years(int years)
{
	cout << "It will take (year/s): " << years << "!" << endl;
}