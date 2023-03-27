#include <iostream>
#include <cmath>
#include "basic_functions.h"

using namespace std;

// Functions
int get_from();
int get_to(int n);
void print_prime(int from, int to);
bool check_prime(int n);

int main()
{
	int from = get_from(); // Get from what number to start finding primes
	int to = get_to(from); // Get to what number to end finding primes

	print_prime(from, to); // Check and print the prime numbers

	return 0; //------------- Success
}

// Get from what number to start finding primes
int get_from()
{
	int start = 0;
	do
	{
		start = get_valid_input<int>("From: ");
	} while (start < 2);
	return start;
}

// Get to what number to end finding primes
int get_to(int n)
{
	int end = 0;
	do
	{
		end = get_valid_input<int>("To: ");
	} while (end < n);
	return end;
}

//* Print the numbers if they are a prime -----------------------------------------------------------------------------------------------------------------
void print_prime(int from, int to)
{
	for (int i = from; i <= to; i++)
	{
		if (check_prime(i))
		{
			cout << i << ", " << endl;
		}
	}
}

// Check if that number is a prime
bool check_prime(int n)
{
	int limit = sqrt(n);
	for (int i = 2; i <= limit; i++)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}
//* Print the numbers if they are a prime -----------------------------------------------------------------------------------------------------------------

// The reason the loop iterates up to the square root of n is that any factor of n that is greater than its square root must have a corresponding factor that is smaller than its square root.
// Therefore, it is sufficient to check only the factors up to the square root of n.
// For example, to check whether 17 is a prime number,
// the function will iterate through all the integers from 2 up to the square root of 17, which is 4 (rounded down).
// It will check if 2, 3, or 4 divide 17 without a remainder. Since none of these integers do, the function will return true to indicate that 17 is a prime number.