#include <iostream>
#include <limits>
#include <string>

using namespace std;

string get_number_string();
bool is_a_digit(string number);
long long convert(string input);

int main()
{
	string number_string = get_number_string();

	if (!is_a_digit(number_string))
	{
		cout << "Error 1: Enter numbers only! " << endl;
		return 1;
	}

	long long converted_number = convert(number_string);
	cout << converted_number << endl;

	return 0;
}

template <typename T>
T get_valid_input(const string& prompt)
{
	T input;
	while (true)
	{
		cout << prompt;
		cin >> input;
		if (cin.fail())
		{
			// Input is not valid
			cout << "Error: Please enter a valid input." << endl;
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
string get_valid_input<string>(const string& prompt)
{
	string input;
	while (true)
	{
		cout << prompt;
		getline(cin, input);
		if (cin.fail() || input.empty())
		{
			// Input is not valid
			cout << "Error: Please enter a valid input." << endl;
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

string get_number_string()
{
	string number = get_valid_input<string>("Enter number to convert: ");
	return number;
}

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
		sign = -1;
		input.erase(0, 1);  // Remove the negative sign from the input string
		length--;
	}

	// Recursive case
	int num = input[length - 1] - '0';
	input.erase(length - 1, 1);
	return sign * (num + 10 * convert(input));
}