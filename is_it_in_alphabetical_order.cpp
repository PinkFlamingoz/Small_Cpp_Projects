#include <iostream>
#include "headers/basic_functions.h"

using namespace std;

// Functions
string get_user_input();
string convert_to_uppercase(string text);
bool check_alphabetic_order(string text);
void print_result(bool result);

int main()
{
	string text = get_user_input(); //---------------- Get user string

	string formated = convert_to_uppercase(text); //-- Convert all to upper

	bool result = check_alphabetic_order(formated); // Check if it is in alphabetical order

	print_result(result); //-------------------------- Print true or false

	return 0; //-------------------------------------- Success
}

// Get the user text
string get_user_input()
{
	string text = get_valid_input<string>("Enter string of text: ");
	return text;
}

// Concert the text to uppercase
string convert_to_uppercase(string text)
{
	int length = text.length();
	for (int i = 0; i < length; i++)
	{
		text[i] = toupper(text[i]);
	}
	return text;
}

// Check if the ASCII value of the first character is bigger than the next, if it is, its not in alphabetical order
bool check_alphabetic_order(string text)
{
	int length = text.length();
	for (int i = 0; i < length - 1; i++)
	{
		if (text[i] > text[i + 1])
		{
			return false;
		}
	}
	return true;
}

// Print the result
void print_result(bool result)
{
	if (result)
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
}