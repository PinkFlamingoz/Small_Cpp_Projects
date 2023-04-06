#pragma once

#include <string>
#include <limits>

using namespace std;

template <typename T>
T get_valid_input(const string &prompt, const string &helper_string1 = "", int num1 = -1, const string &helper_string2 = "", int num2 = -1)
{
	T input;
	string input_buffer;
	while (true)
	{
		cout << prompt;

		if (!helper_string1.empty())
		{
			cout << " " << helper_string1;
		}
		if (num1 != -1)
		{
			cout << " " << num1 << " ";
		}
		if (!helper_string2.empty())
		{
			cout << " " << helper_string2;
		}
		if (num2 != -1)
		{
			cout << " " << num2 << ": ";
		}

		cin >> input;

		if (cin.fail())
		{
			// Input is not valid
			cerr << "Error: Please enter a valid input." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			// Input is valid
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}
	return input;
}

template<>
string get_valid_input<string>(const string &prompt, const string &helper_string1, int num1, const string &helper_string2, int num2)
{
	string input;
	while (true)
	{
		cout << prompt;

		if (!helper_string1.empty())
		{
			cout << " " << helper_string1;
		}
		if (num1 != -1)
		{
			cout << " " << num1;
		}
		if (!helper_string2.empty())
		{
			cout << " " << helper_string2;
		}
		if (num2 != -1)
		{
			cout << " " << num2 << ": ";
		}

		// Remove leading white spaces with ws
		getline(cin >> ws, input);

		// Remove trailing white spaces
		size_t last_non_space = input.find_last_not_of(" \t\n\v\f\r"); // Find the last non-space character
		input = input.substr(0, last_non_space + 1); //------------------ Extract a substring from the input string starting from index 0 and ending at the index given by last_non_space + 1. The +1 is added to include the last non-space character in the resulting substring. This effectively removes any trailing whitespace from the input string, and the resulting substring is assigned back to the input variable.

		if (cin.fail() || input.empty())
		{
			// Input is not valid
			cerr << "Error: Please enter a valid input." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			// Input is valid
			break;
		}
	}
	return input;
}

template <typename T, typename R, typename C>
void allocate_memory_2D_array(T **&array, R rows, C cols)
{
	// Allocate memory for rows
	array = new T * [rows];
	for (int i = 0; i < rows; i++)
	{
		// Allocate memory for each column in each row
		array[i] = new T[cols];
	}
}

template <typename T, typename R>
void free_allocate_memory_2D_array(T **&array, R rows)
{
	// Deallocate memory for each column in each row
	for (int i = 0; i < rows; i++)
	{
		delete[] array[i];
	}
	// Deallocate memory for rows
	delete[] array;
}
