#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <D:\Xixijan\repos\Small_C++_Projects\basic_get_functions.h>

using namespace std;

int get_number();
void random_array();
bool linear_search(int number);

const int MAXSIZE = 1000000;
int RANDOM_ARRAY[MAXSIZE];

int main()
{
	random_array();
	int number = get_number();

	auto start = chrono::high_resolution_clock::now();

	linear_search(number);

	auto end = chrono::high_resolution_clock::now();

	auto elapsed_seconds = chrono::duration_cast<chrono::duration<double>>(end - start).count();

	cout << "Time took: " << elapsed_seconds << endl;

	return 0;
}

int get_number()
{
	int number;
	do
	{
		number = get_valid_input<int>("Enter number: ");
	} while (number < 1 || number > MAXSIZE);
	return number;
}

void random_array()
{
	srand(time(nullptr));
	for (int i = 0; i < MAXSIZE; i++)
	{
		RANDOM_ARRAY[i] = rand() % MAXSIZE;
	}
}

bool linear_search(int number)
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (RANDOM_ARRAY[i] == number)
		{
			cout << "Found: " << RANDOM_ARRAY[i] << endl;
			return 0;
		}
	}
	cout << "Not found! " << endl;
	return 1;
}

// O(n)
// Worst-case scenario: We have to look through the entire array of n elements, either because the target element is the last element of the array or doesn’t exist in the array at all

// Ω(1)
// Best-case scenario: The target element is the first element of the array, and so we can stop looking immediately after we start