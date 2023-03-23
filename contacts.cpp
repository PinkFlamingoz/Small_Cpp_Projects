#include <iostream>
#include "basic_functions.h"

using namespace std;

string get_input_name();
int get_input_age();
long long get_input_number();
void print_confirmation(string name, int age, long long number);

int main()
{
	// Get input
	string name = get_input_name();
	int age = get_input_age();
	long long number = get_input_number();

	// Print input for confirmation
	print_confirmation(name, age, number);

	return 0;
}

string get_input_name()
{
	string name = get_valid_input<string>("Enter name: ");
	return name;
}

int get_input_age()
{
	int age;
	do
	{
		age = get_valid_input<int>("Enter age: ");
	} while (age < 1);
	return age;
}

long long get_input_number()
{
	long long number;
	do
	{
		number = get_valid_input<long long>("Enter number: ");
	} while (number < 1);
	return number;
}

void print_confirmation(string name, int age, long long number)
{
	cout << "Name: " << name << endl << "Age: " << age << endl << "Number: " << number << endl;
}