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
		getline(cin, input);

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
