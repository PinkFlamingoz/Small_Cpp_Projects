#include <iostream>
#include <limits>
#include <math.h>

using namespace std;

double long get_input_a(void);
double long get_input_b(void);
double long get_input_c(void);
bool check_triangle_method1(double long a, double long b, double long c);
bool check_triangle_method2(double long a, double long b, double long c);
void print_triangle_check(bool meth1, bool meth2);

int main(void)
{
	// Get the 3 sides input
	double long a = get_input_a();
	double long b = get_input_b();
	double long c = get_input_c();
	// Check for triangle
	bool meth1 = check_triangle_method1(a, b, c);
	bool meth2 = check_triangle_method2(a, b, c);
	// Print results
	print_triangle_check(meth1, meth2);
}

template <typename T>
T get_valid_input(const string& prompt) {
	T input;
	while (true) {
		cout << prompt;
		if (cin >> input) {
			// The user entered a valid number
			break;
		}
		else {
			// The user did not enter a valid number
			cout << "Error: Please enter a valid input." << endl;
			cin.clear(); // Clear the error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any input in the buffer
		}
	}
	return input;
}

double long get_input_a(void)
{
	double long a;
	do
	{
		a = get_valid_input<double long>("Enter a: ");
	} while (a < 1);
	return a;
}

double long get_input_b(void)
{
	double long b;
	do
	{
		b = get_valid_input<double long>("Enter b: ");
	} while (b < 1);
	return b;
}

double long get_input_c(void)
{
	double long c;
	do
	{
		c = get_valid_input<double long>("Enter c: ");
	} while (c < 1);
	return c;
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