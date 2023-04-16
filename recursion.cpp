#include <iostream>
#include "basic_functions.h"

using namespace std;

// Functions
long long get_number();
long long factorial(long long number);
long long fibonacci(long long number);
long long collatz(long long number);
long long power(long long number, long long k);
long long gcd(long long a, long long b);
long long count_divisible_digits(long long number);

void print_results(long long fa, long long fi, long long co, long long po, long long gcd, long long digits, long long number, long long k);

int main()
{
	long long number = get_number(); //----------------- Get the a number from the user
	long long k = get_number(); //---------------------- Get the a number from the user

	long long fa = factorial(number); //---------------- Get whats the factorial of that number
	long long fi = fibonacci(number); //---------------- Get the Fibonacci number at that interval
	long long co = collatz(number); //------------------ Get the total steps to get to one from that number
	long long po = power(number, k); //----------------- Calculate the power of
	long long gc = gcd(number, k); //------------------- Calculate the gcd of two numbers
	long long di = count_divisible_digits(number); //--- Count if a digit is divisible in a number

	print_results(fa, fi, co, po, gc, di, number, k); // Print the results

	return 0; //---------------------------------------- Success
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

// Get the Fibonacci number at that interval
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

// Number to the power of k
long long power(long long number, long long k)
{
	// Base case
	if (k == 0)
	{
		return 1;
	}
	// Recursive case
	else
	{
		return number * power(number, k - 1);
	}
}

// GCD
long long gcd(long long a, long long b)
{
	// Base case
	if (b == 0)
	{
		return a;
	}
	// Recursive case
	else
	{
		return gcd(b, a % b);
	}
}

// Count divisible digits, if the input is 12345, it will check if 1 is divisible by 2, if 2 is divisible by 3, if 3 is divisible by 4, and if 4 is divisible by 5
long long count_divisible_digits(long long number)
{
	// Base case
	if (number < 10)
	{
		return 0;
	}
	// recursive case
	else
	{
		int next_digit = number % 10;
		int remainder = number / 10;
		int count = count_divisible_digits(remainder);
		if (remainder % next_digit == 0)
		{
			count++;
		}
		return count;
	}
}

// Print the results
void print_results(long long fa, long long fi, long long co, long long po, long long gcd, long long digits, long long number, long long k)
{
	cout << "Factorial of " << number << " is: " << fa << endl;
	cout << "Fibonacci at interval " << number << " is: " << fi << endl;
	cout << "Total steps to get to one from " << number << " is: " << co << endl;
	cout << number << " to the power of " << k << " is: " << po << endl;
	cout << "GCD of " << number << " and " << k << " is " << gcd << endl;
	cout << "Number of digits that are divisible by the previous digit: " << digits << endl;
}