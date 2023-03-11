#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

int get_cents();
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main()
{
	// Ask how many cents the customer is owed
	int cents = get_cents();

	// Calculate the number of quarters to give the customer
	int quarters = calculate_quarters(cents);
	cents = cents - quarters * 25;

	// Calculate the number of dimes to give the customer
	int dimes = calculate_dimes(cents);
	cents = cents - dimes * 10;

	// Calculate the number of nickels to give the customer
	int nickels = calculate_nickels(cents);
	cents = cents - nickels * 5;

	// Calculate the number of pennies to give the customer
	int pennies = calculate_pennies(cents);
	cents = cents - pennies * 1;

	// Sum coins
	int coins = quarters + dimes + nickels + pennies;

	// Print total number of coins to give the customer
	cout << "Total coins: " << coins << endl;
	cout << "Quarters: " << quarters << ", Dimes: " << dimes << ", Nickels: " << nickels << ", Pennies: " << pennies << endl;

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

int get_cents()
{
	int cents;
	do
	{
		cents = get_valid_input<int>("Change owed: ");
	} while (cents < 1);
	return cents;
}

int calculate_quarters(int cents)
{
	return cents / 25;
}

int calculate_dimes(int cents)
{
	return cents / 10;
}

int calculate_nickels(int cents)
{
	return cents / 5;
}

int calculate_pennies(int cents)
{
	return cents / 1;
}