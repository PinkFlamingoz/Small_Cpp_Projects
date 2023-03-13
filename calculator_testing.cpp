#include <iostream>
#include <iomanip>
#include <D:\Xixijan\repos\Small_C++_Projects\basic_get_functions.h>

using namespace std;

int main()
{
	// catch integer overflow(32 bits is split half for positive half for negative numbers) - make integers to long
	// catch truncation(lose everything after the decimal point) - convert the variables to the proper type (type casting)
	// floating-point imprecision - can try to change from float to double

	int x = get_valid_input<int>("x: ");
	int y = get_valid_input<int>("y: ");

	float float1 = (float)x / (float)y;
	double double1 = (double)x / (double)y;
	float float2 = x / y;
	int int1 = x / y;
	int int2 = x % y;
	int int3 = (float)x / y;
	int int4 = x / 10;
	int int5 = y / 10;
	int int6 = x % 10;
	int int7 = y % 10;
	int int8 = x / 100;
	int int9 = y / 100;
	int int10 = x % 100;
	int int11 = y % 100;
	int int12 = x + y;

	cout << "all float:            " << float1 << endl;
	cout << "all float %.20f:      " << fixed << setprecision(20) << float1 << endl;
	cout << "all double:           " << double1 << endl;
	cout << "float only int1:      " << float2 << endl;
	cout << "integer:              " << int1 << endl;
	cout << "mod:                  " << int2 << endl;
	cout << "float only x:         " << int3 << endl;
	cout << "remove last digit x:  " << int4 << endl;
	cout << "remove last digit y:  " << int5 << endl;
	cout << "get last digit x:     " << int6 << endl;
	cout << "get last digit y:     " << int7 << endl;
	cout << "remove 2last digit x: " << int8 << endl;
	cout << "remove 2last digit y: " << int9 << endl;
	cout << "get 2last digit x:    " << int10 << endl;
	cout << "get 2last digit y:    " << int11 << endl;
	cout << "integer-overflow:     " << int12 << endl;

	return 0;
}