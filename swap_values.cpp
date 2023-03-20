#include <iostream>
#include "basic_get_functions.h"

using namespace std;

int get_value();
void swap1(int *a, int *b);
void swap2(int &a, int &b);
void print(int a, int b, string prompt);

int main()
{
	int x = get_value();
	int y = get_value();

	print(x, y, "Before swap1: ");
	swap1(&x, &y);
	print(x, y, "After swap1: ");
	swap2(x, y);
	print(x, y, "After swap2: ");

	return 0;
}

int get_value()
{
	int number = get_valid_input<int>("Enter number: ");
	return number;
}

void swap1(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap2(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void print(int a, int b, string prompt)
{
	cout << prompt << endl;
	cout << "A is: " << a << ", " << "B is: " << b << endl;
}