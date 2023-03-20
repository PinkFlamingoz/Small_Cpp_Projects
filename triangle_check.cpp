#include <iostream>
#include <math.h>
#include "basic_get_functions.h"

using namespace std;

double long get_input(string prompt);
bool check_triangle_method1(double long a, double long b, double long c);
bool check_triangle_method2(double long a, double long b, double long c);
void print_triangle_check(bool meth1, bool meth2);

int main(void)
{
	// Get the 3 sides input
	double long a = get_input("Side a");
	double long b = get_input("Side b");
	double long c = get_input("Side c");
	// Check for triangle
	bool meth1 = check_triangle_method1(a, b, c);
	bool meth2 = check_triangle_method2(a, b, c);
	// Print results
	print_triangle_check(meth1, meth2);

	return 0;
}

double long get_input(string prompt)
{
	cout << prompt;
	double long n;
	do
	{
		n = get_valid_input<double long>(": ");
	} while (n < 1);
	return n;
}

bool check_triangle_method1(double long a, double long b, double long c)
{
	if ((a + b <= c) || (b + c <= a) || (c + a <= b))
	{
		return false;
	}
	return true;
}

bool check_triangle_method2(double long a, double long b, double long c)
{
	if ((a * a + b * b == c * c) || (b * b + c * c == a * a) || (c * c + a * a == b * b))
	{
		return true;
	}
	return false;
}

void print_triangle_check(bool meth1, bool meth2)
{
	meth1 ? printf("Method 1: True \n") : printf("Method 1: False \n");
	meth2 ? printf("Method 2 90°: True \n") : printf("Method 2 90°: False \n");
}