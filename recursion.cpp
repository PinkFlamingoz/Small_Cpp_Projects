#include <iostream>
#include <limits>
#include <string>

using namespace std;

long long get_number();
long long factorial(long long number);
long long fibonacci(long long number);
long long collatz(long long number);
void print_results(long long fa, long long fi, long long co, long long number);

int main()
{
	long long number = get_number();

	long long fa = factorial(number);
	long long fi = fibonacci(number);
	long long co = collatz(number);

	print_results(fa, fi, co, number);

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

long long get_number()
{
	long long number;
	do
	{
		number = get_valid_input<long long>("Enter number: ");
	} while (number < 1);
	return number;
}

long long factorial(long long number)
{
	// Base case
	if (number == 1)
	{
		return 1;
	}
	// Recursive case
	else
	{
		return number * factorial(number - 1);
	}
}

long long fibonacci(long long number)
{
	// Base case
	if (number == 0)
	{
		return 0;
	}
	else if (number == 1)
	{
		return 1;
	}
	// Recursive case
	else
	{
		return fibonacci(number - 1) + fibonacci(number - 2);
	}
}

long long collatz(long long number)
{
	// Base case
	if (number == 1)
	{
		return 0;
	}
	// Recursive case
	else if (number % 2 == 0)
	{
		return 1 + collatz(number / 2);
	}
	else
	{
		return 1 + collatz(3 * number + 1);
	}
}

void print_results(long long fa, long long fi, long long co, long long number)
{
	cout << "Factorial of " << number << " is: " << fa << endl << "Fibonacci at interval " << number << " is: " << fi << endl << "Total steps to get to one from " << number << " is: " << co << endl;
}