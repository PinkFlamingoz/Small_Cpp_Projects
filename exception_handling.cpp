#include <iostream>
#include "basic_functions.h"

using namespace std;

int main()
{
	float a = get_valid_input<float>("Enter Numerator: ");
	float b = get_valid_input<float>("Enter Denominator: ");
	float c = 0;

	try
	{
		if (b == 0)
		{
			throw b; // This is being sent to the catch block!
		}
		c = a / b;
	}
	catch (float b)
	{
		cerr << "Cant devide by 0! You entered: " << b << endl;
	}

	cout << "Result: " << c << endl;

	string d = get_valid_input<string>("Enter number to convert to integer: ");
	int number = 0;

	try
	{
		number = stoi(d);
	}
	catch (const invalid_argument &e)
	{
		cerr << "Cant convert letters or characters! " << e.what() << endl;
	}

	cout << "Concerted number: " << number << endl;

	return 0;
}