#include <iostream>
#include "basic_functions.h"

using namespace std;

// Functions
long long get_number();
long long factorial(long long number);
long long fibonacci(long long number);
long long collatz(long long number);
void print_results(long long fa, long long fi, long long co, long long number);

int main()
{
	long long number = get_number(); //-- Get the a number from the user

	long long fa = factorial(number); //- Get whats the factorial of that number
	long long fi = fibonacci(number); //- Get the fibonacci number at that interval
	long long co = collatz(number); //--- Get the total steps to get to one from that number

	print_results(fa, fi, co, number); // Print the results

	return 0; //------------------------- Success
}

// Get the a number from the user
long long get_number()
{
	long long number = 0;
	do
	{
		number = get_valid_input<long long>("Enter number: ");
	} while (number < 1);
	return number;
}

// Get whats the factorial of that number
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

// Get the fibonacci number at that interval
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

// Get the total steps to get to one from that number
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

// Print the results
void print_results(long long fa, long long fi, long long co, long long number)
{
	cout << "Factorial of " << number << " is: " << fa << endl << "Fibonacci at interval " << number << " is: " << fi << endl << "Total steps to get to one from " << number << " is: " << co << endl;
}