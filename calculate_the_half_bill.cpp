#include <iostream>
#include "headers/basic_functions.h"

using namespace std;

// Functions
double get_input(string prompt);
double calculate_grandTotal(double bill, double tax, double tip);
double calculate_half(double grandTotal);
void print_grandTotal(double grandTotal, double half);

int main()
{
	double bill = get_input("Bill"); //------------------------- Get the bill
	double tax = get_input("Tax"); //--------------------------- Get the tax
	double tip = get_input("Tip"); //--------------------------- Get the tip

	double grandTotal = calculate_grandTotal(bill, tax, tip); // Calculate the grand total
	double half = calculate_half(grandTotal); //---------------- Calculate the split between some number of people

	print_grandTotal(grandTotal, half); //---------------------- Print the results

	return 0; //------------------------------------------------ Success
}

// Get the values for the Bill, Tax and Tip
double get_input(string prompt)
{
	cout << prompt;

	double input = 0;
	do
	{
		input = get_valid_input<double>(": ");
	} while (input < 1);
	return input;
}

// Calculate the grand total
double calculate_grandTotal(double bill, double tax, double tip)
{
	double total = bill + (bill * (tax * 0.01));
	double grandTotal = total + (total * (tip * 0.01));
	return grandTotal;
}

// Calculate the split between some number of people
double calculate_half(double grandTotal)
{
	double people = 0;
	do
	{
		people = get_valid_input<double>("Number of people: ");
	} while (people < 2);
	double half = grandTotal / people;
	return half;
}

// Print the results
void print_grandTotal(double grandTotal, double half)
{
	cout << "Grand total is: " << grandTotal << "!" << endl;
	cout << "Each owes: " << half << " $" << endl;
}