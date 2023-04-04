#include <iostream>
#include <chrono>
#include "basic_functions.h"

using namespace std;

// Functions
int get_number();
void sorted_array();
bool binary_search(int number);

// Globals
const int MAXSIZE = 1000000;
int SORTED_ARRAY[MAXSIZE];

int main()
{
	sorted_array(); //----------------------------------- Initialize a sorted array with values from 0 to MAXSIZE - 1

	int number = get_number(); //------------------------ Get a number to find in this array

	auto start = chrono::high_resolution_clock::now(); // We use a clock to time how fast the search completes

	binary_search(number); //---------------------------- We use binary search for the number we want to find

	auto end = chrono::high_resolution_clock::now();
	auto elapsed_seconds = chrono::duration_cast<chrono::duration<double>>(end - start).count();
	cout << "Time took: " << elapsed_seconds << endl;

	return 0; //----------------------------------------- Success
}

// Get the number to find in the array
int get_number()
{
	int number = 0;
	do
	{
		number = get_valid_input<int>("Enter number: ");
	} while (number < 1 || number > MAXSIZE);
	return number;
}

// Initialize the array from 0 to MAXSIZE - 1
void sorted_array()
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		SORTED_ARRAY[i] = i;
	}
}

// Binary search algorithm (Divide and Conquer)
bool binary_search(int number)
{
	int start_point = 0;
	int end_point = MAXSIZE - 1;

	while (start_point <= end_point) //----------------------------- Repeat until the (sub)array is of size 0
	{
		int middle_point = (start_point + end_point) / 2; //-------- Calculate the middle point of the current (sub)array

		if (SORTED_ARRAY[middle_point] == number) //---------------- If the target is at the middle, stop
		{
			cout << "Found: " << SORTED_ARRAY[middle_point] << endl;
			return true;
		}
		else if (SORTED_ARRAY[middle_point] < number) //------------ Otherwise, if the target is greater than what's at the middle, repeat, changing the start point to be just to the right of the middle
		{
			start_point = middle_point + 1;
		}
		else if (SORTED_ARRAY[middle_point] > number) //------------ Otherwise, if the target is less than whats at the middle, repeat, changing the end point to be just to the left of the middle
		{
			end_point = middle_point - 1;
		}
	}
	cout << "Not found! " << endl;
	return false;
}

// O(log n)
// Worst-case scenario: We have to divide a list of n elementsin half repeatedly to find the target element, either because division or doesnt exist in the array at all

// Ω(1)
// Best-case scenario: The target element is at the midpoint of the full array, and so we can stop looking immediately after we start