#include <iostream>
#include "basic_functions.h"

using namespace std;

// Functions
bool is_a_digit(string digit);
void palindrome_number_check(int number);
void palindrome_string_check(string words);

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 2)
	{
		cerr << "Error 1: Too many or none arguments " << endl << "Usage: ./palindrome [number_to_check] " << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}

	// Ensure all the characters in the numbers are digits
	if (!is_a_digit(argv[1]))
	{
		cerr << "Error 2: Enter a digit " << endl;
		return 2;
	}

	// Convert the user inputed values
	int number = stoi(argv[1]);
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	palindrome_number_check(number); //----------------------------------- Check if a number is a palindrome
	palindrome_string_check(get_valid_input<string>("Enter string: ")); // Check if a string is a palindrome

	return 0; //---------------------------------------------------------- Success
}

// Check if all the characters are digits from argv[1]
bool is_a_digit(string digit)
{
	int length = digit.length();
	for (int i = 0; i < length; i++)
	{
		if (!isdigit(digit[i]))
		{
			return false;
		}
	}
	return true;
}

// Check if its a palindrome
void palindrome_number_check(int number)
{
	int temp = number;
	int digit = 0;
	int reversed = 0;
	while (temp != 0)
	{
		digit = temp % 10; //----------------- Get the last digit of a number
		reversed = (reversed * 10) + digit; // Add that digit in reverse order in the appropriate location
		temp = temp / 10; //------------------ Remove the last digit so we can get the next one
	}

	if (number == reversed)
	{
		cout << number << " is a palindrome, reversed: " << reversed << endl;
	}
	else
	{
		cout << number << " is not a palindrome, reversed: " << reversed << endl;
	}
}
// Step 1: 121 % 10 = 1; (0 * 10)  + 1 = 1;     121 / 10 = 12;
// Step 2: 12  % 10 = 2; (1 * 10)  + 2 = 12;    12  / 10 = 1;
// Step 3: 1   % 10 = 1; (12 * 10) + 1 = 121;   1   / 10 = 0;
// STOP;

void palindrome_string_check(string words)
{
	string reversed = "";
	bool is = false;
	int length = words.length();
	for (int i = 0; i < length / 2; i++)
	{
		if (words[i] == words[length - i - 1])
		{
			is = true;
		}
	}

	for (int i = length - 1; i >= 0; i--)
	{
		reversed += words[i];
	}

	if (is)
	{
		cout << words << " is a palindrome, reversed: " << reversed << endl;
	}
	else
	{
		cout << words << " is not palindrome, reversed: " << reversed << endl;
	}
}