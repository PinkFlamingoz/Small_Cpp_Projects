#include <iostream>
#include <D:\Xixijan\repos\Small_C++_Projects\basic_get_functions.h>

using namespace std;

double get_bill();
double get_tax();
double get_tip();
double calculate_grandTotal(double bill, double tax, double tip);
double calculate_half(double grandTotal);
void print_grandTotal(double grandTotal, double half);

int main()
{
	// Get the bill, tax, tip
	double bill = get_bill();
	double tax = get_tax();
	double tip = get_tip();
	// Calculate the half price
	double grandTotal = calculate_grandTotal(bill, tax, tip);
	double half = calculate_half(grandTotal);
	// Print the price
	print_grandTotal(grandTotal, half);

	return 0;
}

double get_bill()
{
	double bill;
	do
	{
		bill = get_valid_input<double>("Bill: ");
	} while (bill < 1);

	return bill;
}

double get_tax()
{
	double tax;
	do
	{
		tax = get_valid_input<double>("Tax percent %: ");
	} while (tax < 1);
	return tax;
}

double get_tip()
{
	double tip;
	do
	{
		tip = get_valid_input<double>("Tip percent %: ");
	} while (tip < 1);
	return tip;
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