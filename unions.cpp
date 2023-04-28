#include <iostream>

using namespace std;
// NOTE: Unions
// -Unions allow different data types to be placed on the same place from memory.
// - The memory size corresponds to the size of the largest term of the union.
// - Changing a member of the union affects the rest of the members and you cannot store values for the members independently of each other.

// Unions
union Union1
{
	char id;
	float salary;
	short int years;
	//- char (1B), float (4B), short int (2B).
};

int main()
{
	Union1 U;

	cout << sizeof(U) << " B \n";
	system("pause");

	U.id = 'x';
	U.salary = 17500.50;
	U.years = 30;

	cout << "ID:" << U.id << " Salary: " << U.salary << " Years: " << U.years << "\n";
	cout << sizeof(U) << " B \n";
	// Printing correct value for last updated element (U.years=30)!
	system("pause");
	return 0;
}