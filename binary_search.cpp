#include <iostream>
#include <chrono>
#include "basic_functions.h"

using namespace std;

// Globals
const int MAXSIZE = 1000000;
int SORTED_ARRAY[MAXSIZE];

// Functions
int get_number();
void sorted_array();
bool binary_search(int number);

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
	} while (number < 0 || number > MAXSIZE);
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
	int start = 0;
	int end = MAXSIZE - 1;

	while (start <= end) //---------------------------------------------------------- Repeat until the (sub)array is of size 0
	{
		int mid = start + (end - start) / 2; //-------------------------------------- Calculate the middle point of the current (sub)array

		if (SORTED_ARRAY[mid] == number) //------------------------------------------ If the target is at the middle, stop
		{
			cout << "Found: " << SORTED_ARRAY[mid] << " at location " << mid << endl;
			return true;
		}
		else if (SORTED_ARRAY[mid] < number) //-------------------------------------- Otherwise, if the target is greater than what's at the middle, repeat, changing the start point to be just to the right of the middle
		{
			start = mid + 1;
		}
		else if (SORTED_ARRAY[mid] > number) //-------------------------------------- Otherwise, if the target is less than whats at the middle, repeat, changing the end point to be just to the left of the middle
		{
			end = mid - 1;
		}
	}
	cout << "Not found! " << endl;
	return false;
}

// O(log n)
// Worst-case scenario: We have to divide a list of n elements in half repeatedly to find the target element, either because division or doesn't exist in the array at all

// Ω(1)
// Best-case scenario: The target element is at the midpoint of the full array, and so we can stop looking immediately after we start

// The reason people calculate the midpoint of an array as mid = start + (end - start) / 2 instead of mid = (start + end) / 2 is to avoid potential integer overflow when adding start and end together.
// When adding two integers together, there is a risk that the result may be larger than the maximum value that can be represented by an integer data type.
// This is called integer overflow, and it can result in unexpected behavior in your program.
// To avoid integer overflow when calculating the midpoint of an array, the expression end - start is first evaluated.
// This calculates the distance between the end and start indices of the array, which is always a non - negative integer.
// Then, this value is divided by 2 and added to the start index to obtain the midpoint.
// By using this formula, you can ensure that the midpoint of the array is always calculated correctly, regardless of the size of the array or the values of the start and end indices.