#include <iostream>
#include <chrono>
#include "headers/basic_functions.h"

using namespace std;

// Globals
const int MAXSIZE = 1000000;
int RANDOM_ARRAY[MAXSIZE];

// Functions
int get_number();
void random_array();
bool linear_search(int number);

int main()
{
	random_array(); //----------------------------------- Initialize a random array with values from 0 to MAXSIZE - 1

	int number = get_number(); //------------------------ Get the number we want to find in the random array

	auto start = chrono::high_resolution_clock::now(); // We use a clock to time how fast the search completes

	linear_search(number); //---------------------------- We use linear search for the number we want to find

	auto end = chrono::high_resolution_clock::now();
	auto elapsed_seconds = chrono::duration_cast<chrono::duration<double>>(end - start).count();
	cout << "Time took: " << elapsed_seconds << endl;

	return 0; //----------------------------------------- Success
}

// Get the number we want to find
int get_number()
{
	int number = 0;
	do
	{
		number = get_valid_input<int>("Enter number: ");
	} while (number < 0 || number > MAXSIZE);
	return number;
}

// Initialize the random array with values from 0 to MAXSIZE - 1
void random_array()
{
	srand(time(nullptr)); //--------------- Seeds the random number generator with a value based on the current time
	for (int i = 0; i < MAXSIZE; i++)
	{
		RANDOM_ARRAY[i] = rand() % MAXSIZE;
	}
}

// Linear search algorithm compare the number with each value in the array until found
bool linear_search(int number)
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (RANDOM_ARRAY[i] == number)
		{
			cout << "Found: " << RANDOM_ARRAY[i] << " at location " << i << endl;
			return true;
		}
	}
	cout << "Not found! " << endl;
	return false;
}

// O(n)
// Worst-case scenario: We have to look through the entire array of n elements, either because the target element is the last element of the array or doesn't exist in the array at all

// Ω(1)
// Best-case scenario: The target element is the first element of the array, and so we can stop looking immediately after we start