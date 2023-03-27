#include <iostream>
#include "basic_functions.h"

using namespace std;

// Functions
string get_input_name();
int get_input_age();
long long get_input_number();
void print_confirmation(string name, int age, long long number);

int main()
{
	string name = get_input_name(); //------- Get the name
	int age = get_input_age(); //------------ Get the age
	long long number = get_input_number(); // Get number

	print_confirmation(name, age, number); // Print the gotten input

	return 0; //----------------------------- Success
}

// Get the name
string get_input_name()
{
	string name = get_valid_input<string>("Enter name: ");
	return name;
}

// Get the age
int get_input_age()
{
	int age = 0;
	do
	{
		age = get_valid_input<int>("Enter age: ");
	} while (age < 1);
	return age;
}

// Get the number
long long get_input_number()
{
	long long number = 0;
	do
	{
		number = get_valid_input<long long>("Enter number: ");
	} while (number < 1);
	return number;
}

// Print the gotten input
void print_confirmation(string name, int age, long long number)
{
	cout << "Name: " << name << endl << "Age: " << age << endl << "Number: " << number << endl;
}