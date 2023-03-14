#include <iostream>
#include <cmath>
#include "basic_get_functions.h"

using namespace std;

int get_from();
int get_to(int n);
bool check_prime(int n);
void print_prime(int from, int to);

int main()
{
	// Get from, too
	int from = get_from();
	int to = get_to(from);

	// Check and print
	print_prime(from, to);

	return 0;
}

int get_from()
{
	int start;
	do
	{
		start = get_valid_input<int>("From: ");
	} while (start < 2);
	return start;
}

int get_to(int n)
{
	int end;
	do
	{
		end = get_valid_input<int>("To: ");
	} while (end < n);
	return end;
}

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