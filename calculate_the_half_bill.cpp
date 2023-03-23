#include <iostream>
#include "basic_functions.h"

using namespace std;

double get_input(string prompt);
double calculate_grandTotal(double bill, double tax, double tip);
double calculate_half(double grandTotal);
void print_grandTotal(double grandTotal, double half);

int main()
{
	// Get the bill, tax, tip
	double bill = get_input("Bill");
	double tax = get_input("Tax");
	double tip = get_input("Tip");
	// Calculate the half price
	double grandTotal = calculate_grandTotal(bill, tax, tip);
	double half = calculate_half(grandTotal);
	// Print the price
	print_grandTotal(grandTotal, half);

	return 0;
}

double get_input(string prompt)
{
	cout << prompt;
	double input;
	do
	{
		input = get_valid_input<double>(": ");
	} while (input < 1);

	return input;
}

double calculate_grandTotal(double bill, double tax, double tip)
{
	double total = bill + (bill * (tax * 0.01));
	double grandTotal = total + (total * (tip * 0.01));
	return grandTotal;
}

double calculate_half(double grandTotal)
{
	double people;
	do
	{
		people = get_valid_input<double>("Number of people: ");
	} while (people < 2);
	double half = grandTotal / people;
	return half;
}

void print_grandTotal(double grandTotal, double half)
{
	cout << "Grand total is: " << grandTotal << "!" << endl;
	cout << "Each owes: " << half << " $" << endl;
}