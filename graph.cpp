#include <iostream>
#include "basic_functions.h"

using namespace std;

template < typename T>
class Heap
{
	private:
	// Member variables

	public:
	// Member functions
};

template < typename T>
class Heap
{
	private:
	// Member variables

	public:
	// Member functions
};

template < typename T>
class Heap
{
	private:
	// Member variables

	public:
	// Member functions
};

// Functions
void print_menu();
int get_choice();

int main()
{
	int choice = 0;
	do
	{
		print_menu();
		choice = get_choice();
		switch (choice)
		{
			case 0:
				break;
			case 1:
				system("cls");
				break;
			default:
				cout << "Try again" << endl;
				break;
		}
		cout << "\n\t\t"; system("pause"); // or cin.get(); // For a pause every new operation
	} while (choice != 0);

	return 0;
}

// Print the menu
void print_menu()
{
	cout << "\nWhat operation do you want to perform? Select Option number. Enter 0 to exit." << endl;
}

// Get the choice for the menu
int get_choice()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 0 || choice > 1);
	return choice;
}