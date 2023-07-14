#include <iostream>
#include "headers/basic_functions.h"

using namespace std;

// Functions
int get_cents();
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main()
{
	int cents = get_cents(); //------------------------- Ask how many cents the customer is owed

	int quarters = calculate_quarters(cents); //-------- Calculate the number of quarters to give the customer
	cents = cents - quarters * 25;

	int dimes = calculate_dimes(cents);	//-------------- Calculate the number of dimes to give the customer
	cents = cents - dimes * 10;

	int nickels = calculate_nickels(cents);	//---------- Calculate the number of nickels to give the customer
	cents = cents - nickels * 5;

	int pennies = calculate_pennies(cents);	//---------- Calculate the number of pennies to give the customer
	cents = cents - pennies * 1;

	int coins = quarters + dimes + nickels + pennies; // Sum coins

	cout << "Total coins: " << coins << endl; //-------- Print total number of coins to give the customer
	cout << "Quarters: " << quarters << ", Dimes: " << dimes << ", Nickels: " << nickels << ", Pennies: " << pennies << endl;

	return 0; //---------------------------------------- Success
}

// Get the cents the customer is owed
int get_cents()
{
	int cents = 0;
	do
	{
		cents = get_valid_input<int>("Change owed: ");
	} while (cents < 1);
	return cents;
}

// Calculate quarters
int calculate_quarters(int cents)
{
	return cents / 25;
}

// Calculate dimes
int calculate_dimes(int cents)
{
	return cents / 10;
}

// Calculate nickels
int calculate_nickels(int cents)
{
	return cents / 5;
}

// Calculate pennies
int calculate_pennies(int cents)
{
	return cents / 1;
}