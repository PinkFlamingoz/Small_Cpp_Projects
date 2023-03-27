#include <iostream>
#include "basic_functions.h"

using namespace std;

// Functions
string get_user_password();
bool check_password(string password);
void print_error(bool uppercase, bool lowercase, bool number, bool symbol, bool length);

int main()
{
	string password = get_user_password(); // Get password input

	return 0; //----------------------------- Success
}

// Get a password from the user keep prompting the same thing unitl he enters the correct information
string get_user_password()
{
	string password = "";
	do
	{
		password = get_valid_input<string>("Enter password: ");
	} while (!check_password(password));
	return password;
}

// Check if the passowrd is a valid one
bool check_password(string password)
{
	bool uppercase = false;
	bool lowercase = false;
	bool number = false;
	bool symbol = false;
	bool length = false;
	bool valid = false;

	int password_length = password.length();
	for (int i = 0; i < password_length; i++)
	{
		if (isupper(password[i]))
		{
			uppercase = true;
		}
		if (islower(password[i]))
		{
			lowercase = true;
		}
		if (isdigit(password[i]))
		{
			number = true;
		}
		if (!isalnum(password[i]))
		{
			symbol = true;
		}
		if (password_length >= 8)
		{
			length = true;
		}
	}
	print_error(uppercase, lowercase, number, symbol, length);
	if (uppercase && lowercase && number && symbol && length)
	{
		valid = true;
		cout << "Password is valid!" << endl;
	}

	return valid;
}

// Print if something is missing from the users inputed password
void print_error(bool uppercase, bool lowercase, bool number, bool symbol, bool length)
{
	if (!uppercase)
	{
		cerr << "Password needs one upper case!" << endl;
	}
	if (!lowercase)
	{
		cerr << "Password needs one lower case!" << endl;
	}
	if (!number)
	{
		cerr << "Password needs one number!" << endl;
	}
	if (!symbol)
	{
		cerr << "Password needs one symbol!" << endl;
	}
	if (!length)
	{
		cerr << "Password needs to be at least 8 characters!" << endl;
	}
}