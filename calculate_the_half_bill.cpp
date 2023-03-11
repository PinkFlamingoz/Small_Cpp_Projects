#include <iostream>
#include <string>
#include <limits>

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