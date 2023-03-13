#include <iostream>
#include <D:\Xixijan\repos\Small_C++_Projects\basic_get_functions.h>

using namespace std;

string get_user_input();
bool check_alphabetic_order(string text);
string convert_to_uppercase(string text);
void print_result(bool result);

int main()
{
	// Get user string
	string text = get_user_input();
	// Convert all to upper
	string formated = convert_to_uppercase(text);
	// Check if it is in alphabetical order
	bool result = check_alphabetic_order(formated);
	// Print true or false
	print_result(result);

	return 0;
}

string get_user_input()
{
	string text = get_valid_input<string>("Enter string of text: ");
	return text;
}

string convert_to_uppercase(string text)
{
	int length = text.length();
	for (int i = 0; i < length; i++)
	{
		text[i] = toupper(text[i]);
	}
	return text;
}

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