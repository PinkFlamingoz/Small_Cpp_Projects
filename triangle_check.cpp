#include <iostream>
#include <math.h>
#include "basic_functions.h"

using namespace std;

//Functions
double long get_input(string prompt);
bool check_triangle_method1(double long a, double long b, double long c);
bool check_triangle_method2(double long a, double long b, double long c);
void print_triangle_check(bool meth1, bool meth2);
void area_of_triangle(double long  a, double long  b, double long  c, bool meth1);

int main(void)
{
	double long a = get_input("Side a"); //--------- Get the a side input
	double long b = get_input("Side b"); //--------- Get the b side input
	double long c = get_input("Side c"); //--------- Get the c side input

	bool meth1 = check_triangle_method1(a, b, c); // Check for triangle
	bool meth2 = check_triangle_method2(a, b, c); // Check for 90° triangle

	print_triangle_check(meth1, meth2); //---------- Print results

	area_of_triangle(a, b, c, meth1); //------------ Calculate area

	return 0; //------------------------------------ Success
}

// Get the user sides input
double long get_input(string prompt)
{
	cout << prompt;

	double long n = 0;
	do
	{
		n = get_valid_input<double long>(": ");
	} while (n < 1);
	return n;
}

// Check for triangle with the triangle inequality or triangle inequality theorem
bool check_triangle_method1(double long a, double long b, double long c)
{
	if ((a + b <= c) || (b + c <= a) || (c + a <= b))
	{
		return false;
	}
	return true;
}

// Check for triangle with the pythagorean theorem
bool check_triangle_method2(double long a, double long b, double long c)
{
	if ((a * a + b * b == c * c) || (b * b + c * c == a * a) || (c * c + a * a == b * b))
	{
		return true;
	}
	return false;
}

// Print the results
void print_triangle_check(bool meth1, bool meth2)
{
	cout << "Method 1: " << (meth1 ? "True" : "False") << endl;
	cout << "Method 2 90" << char(248) << ": " << (meth2 ? "True" : "False") << endl;
}

// Calculate area if its a triangle
void area_of_triangle(double long  a, double long  b, double long  c, bool meth1)
{
	double long area = 0;
	double long s = 0;

	if (meth1)
	{
		s = (a + b + c) / 2;

		area = sqrt(s * (s - a) * (s - b) * (s - c));

		cout << "The area is: " << area << endl;
	}
}