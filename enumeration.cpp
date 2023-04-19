#include <iostream>

using namespace std;
// NOTE: An array of integers represented by symbolic values.
// Enumerated constants – similar to symbolic constants, whose values are automatically set:
// - values start at 0 and increase by 1 for each successive symbol.
// - values can be explicitly assigned with the = operator.
// - symbol names must be unique.
// The enumeration definition introduces a new data type.
// Variables of this type can only receive the values of the defined symbolic constants for that type.

int main()
{
	enum Days
	{
		Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
	};

	enum Months
	{
		JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
	};

	Days day_off;
	int x;

	cout << "What day would you like off (0-6)? ";
	cin >> x;
	day_off = Days(x);

	if (day_off == Sunday || day_off == Saturday)
		cout << "\nYou're already off on weekends!\n";
	else
		cout << "\nOkay, I'll put in the vacation day.\n";

	Months month{};
	string month_name[] = { "", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

	for (int i = JAN; i <= DEC; i++)
	{
		month = static_cast<Months>(i);
		cout << month << '\t' << month_name[month] << endl;
	}

	return 0;
}