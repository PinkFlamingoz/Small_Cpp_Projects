#include <iostream>
#include "basic_functions.h"

using namespace std;

// Functions
int system_linear_EQ(float &x, float &y, float a1, float a2, float b1, float b2, float c1, float c2);

main()
{
	// Variables in use
	float x = 0;
	float y = 0;
	float a1 = get_valid_input<float>("Enter coefficient a for equation 1: ");
	float b1 = get_valid_input<float>("Enter coefficient b for equation 1: ");
	float c1 = get_valid_input<float>("Enter coefficient c for equation 1: ");
	float a2 = get_valid_input<float>("Enter coefficient a for equation 2: ");
	float b2 = get_valid_input<float>("Enter coefficient b for equation 2: ");
	float c2 = get_valid_input<float>("Enter coefficient c for equation 2: ");

	// Solutions check
	if (system_linear_EQ(x, y, a1, a2, b1, b2, c1, c2) == 0)
	{
		cout << "The system has no solutions" << endl;
	}
	else if (system_linear_EQ(x, y, a1, a2, b1, b2, c1, c2) == -1)
	{
		cout << "The system has infinite solutions" << endl;
	}
	else
	{
		cout << "Solution of the system: " << endl;
		cout << "x = " << x << endl;
		cout << "y = " << y << endl;
	}

	// Success
	return 0;
}

// Linear equation
int system_linear_EQ(float &x, float &y, float a1, float a2, float b1, float b2, float c1, float c2)
{
	float D, Dx, Dy;
	int solutions = 0;
	D = a1 * b2 - a2 * b1;
	Dx = c1 * b2 - c2 * b1;
	Dy = a1 * c2 - a2 * c1;

	if (D != 0)
	{
		x = Dx / D;
		y = Dy / D;
		solutions = 1;
	}
	else if (Dx == 0 && Dy == 0)
	{
		solutions = -1;
	}
	return solutions;
}