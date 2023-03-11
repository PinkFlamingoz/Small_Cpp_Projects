#include <iostream>
#include <cmath>
#include <limits>

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

template <typename T>
T get_valid_input(const string& prompt)
{
	T input;
	while (true)
	{
		cout << prompt;
		if (cin >> input)
		{
			// The user entered a valid number
			break;
		}
		else
		{
			// The user did not enter a valid number
			cout << "Error: Please enter a valid input." << endl;
			cin.clear(); // Clear the error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any input in the buffer
		}
	}
	return input;
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