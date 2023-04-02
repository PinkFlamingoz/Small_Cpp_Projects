#include <iostream>
#include "basic_functions.h"

using namespace std;

// Functions
string get_number_string();
bool is_a_digit(string number);
long long convert(string input);

int main()
{
	string number_string = get_number_string(); //--------- Get the number form in string

	if (!is_a_digit(number_string)) //--------------------- Check if this string of numbers are all digits
	{
		cerr << "Error 1: Enter numbers only! " << endl;
		return 1;
	}

	long long converted_number = convert(number_string); // Convert the string of numbers to integers
	cout << converted_number << endl;

	return 0; //------------------------------------------- Success
}

// Get the number form in string
string get_number_string()
{
	string number = get_valid_input<string>("Enter number to convert: ");
	return number;
}

// Check if this string of numbers are all digits, if the first character is a '-' then skip it
bool is_a_digit(string number)
{
	int length = number.length();
	int i = 0;
	if (number[i] == '-')
	{
		i = i + 1;
	}
	for (i; i < length; i++)
	{
		if (!isdigit(number[i]))
		{
			return false;
		}
	}
	return true;
}

// Convert the string
long long convert(string input)
{
	int sign = 1;
	long long length = input.length();

	// Base case
	if (length == 0)
	{
		return 0;
	}

	if (input[0] == '-')
	{
		sign = -1; //-------- Take a note that its a negative number we are converting
		input.erase(0, 1); // Remove the negative sign from the input string
		length--; //--------- Because we removed the first character we must now lower the length
	}

	// Recursive case                             Start by getting the index of the last char in the string
	int num = input[length - 1] - '0'; //-------- Convert this char into its numeric value. Subtract '0' char to do this that is a '0' example '1' = 49 - ('0' = 48) = 1
	input.erase(length - 1, 1); //--------------- Remove the last char from the string by moving the null terminator one position to the left
	return sign * (num + 10 * convert(input)); // Return this value plus 10 times the integer value of the new shortened string
}