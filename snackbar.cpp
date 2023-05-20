#include <iostream>
#include <iomanip>
#include <cstring>
#include "basic_functions.h"

using namespace std;

// Structures
struct Menu
{
	string item = "";
	float price = 0;
};

// Globals
const int DEFAULT = 10;

// Functions
void get_menu(Menu menu[]);
int get_size_of_menu(Menu menu[]);
void print_menu(int size, Menu menu[]);
void print_options();
void modify_array(int &size, Menu *&menu);
int get_choice();
void add_element(int &size, Menu *&menu);
Menu get_new_item(string prompt);
void edit_element(int size, Menu menu[]);
void delete_element(int &size, Menu *&menu);
float get_total(int size, Menu menu[]);
float get_cost(string item, int size, Menu menu[]);
void print_total(float total);

int main()
{
	Menu *menu = new Menu[DEFAULT]; //--- Make a dynamic array with DEFAULT

	get_menu(menu); //------------------- Initialize the menu dynamic array

	int size = get_size_of_menu(menu); // Get the size of the menu so we can modify and edit it
	print_menu(size, menu); //----------- Print the current menu

	modify_array(size, menu); //--------- Modify the menu

	delete[] menu; //-------------------- Free up the allocated memory

	return 0; //------------------------- Success
}

// Initialize the menu dynamic array
void get_menu(Menu menu[])
{
	menu[0].item = "Burger";
	menu[0].price = 9.5;

	menu[1].item = "Vegan Burger";
	menu[1].price = 11;

	menu[2].item = "Hot Dog";
	menu[2].price = 5;

	menu[3].item = "Cheese Dog";
	menu[3].price = 7;

	menu[4].item = "Fries";
	menu[4].price = 5;

	menu[5].item = "Cheese Fries";
	menu[5].price = 6;

	menu[6].item = "Cold Pressed Juice";
	menu[6].price = 7;

	menu[7].item = "Cold Brew";
	menu[7].price = 3;

	menu[8].item = "Water";
	menu[8].price = 2;

	menu[9].item = "Soda";
	menu[9].price = 2;
}

// Get the size of the menu so we can modify and edit it, by counting till we reach a empty string
int get_size_of_menu(Menu menu[])
{
	int size = 0;
	while (menu[size].item != "" && menu[size].price != 0)
	{
		size++;
	}
	return size;
}

// Print the current menu
void print_menu(int size, Menu menu[])
{
	cout << " .-.-.  .-.-.  .-.-.     .-.-.  .-.-.  .-.-.  .-.-.     .-.-.  .-.-.  .-.-.\n"
		"=`. .'==`. .'==`. .'== Welcome to Beach Burger Shack! ==`. .'==`. .'==`. .'=\n"
		"   .      .      .         .      .      .      .         .      .      .   \n\n";
	cout << "  Choose from the following menu to order. Enter GET then enter when done.\n\n";
	for (int i = 0; i < size; i++)
	{
		cout << "            |__*__|      " << menu[i].item << ": "
			<< "$" << fixed << setprecision(2) << menu[i].price << endl;
	}
	cout << endl;
	cout << " .-.-.  .-.-.  .-.-.     .-.-.  .-.-.  .-.-.  .-.-.     .-.-.  .-.-.  .-.-.\n"
		"=`. .'==`. .'==`. .'== ==`. .'==`. .'==`. .'==`. .'== ==`. .'==`. .'==`. .'=\n"
		"   .      .      .         .      .      .      .         .      .      .   \n\n";
}

void print_options()
{
	cout << "            |__*__|      1) Edit an item        |__*__|" << endl;
	cout << "            |__*__|      2) Add an item         |__*__|" << endl;
	cout << "            |__*__|      3) Delete an item      |__*__|" << endl;
	cout << "            |__*__|      4) Get total price     |__*__|" << endl;
	cout << "            |__*__|      5) Clear screen        |__*__|" << endl;
	cout << "            |__*__|      6) Done editing        |__*__|" << endl;
}

// Modify the array by the set of options we are giving to the user
void modify_array(int &size, Menu *&menu)
{
	bool done = false;
	while (!done)
	{
		cout << endl;
		print_menu(size, menu);
		cout << endl;
		print_options();
		int answer = get_choice();
		switch (answer)
		{
			case 1:
			{
				cout << endl;
				edit_element(size, menu);
				cout << endl;
				break;
			}
			case 2:
			{
				cout << endl;
				add_element(size, menu);
				cout << endl;
				break;
			}
			case 3:
			{
				cout << endl;
				delete_element(size, menu);
				cout << endl;
				break;
			}
			case 4:
			{
				cout << endl;
				float total = get_total(size, menu);
				print_total(total);
				cout << endl;
				break;
			}
			case 5:
			{
				system("cls");
				break;
			}
			case 6:
			{
				done = true;
				break;
			}
			default:
			{
				cout << endl;
				cerr << "                         Invalid choice. Please try again." << endl;
				cout << endl;
				break;
			}
		}
		cout << "\n\t\t"; system("pause"); // or cin.get(); // For a pause every new operation
	}
}

// Get the choice of the user what to do
int get_choice()
{
	int answer = 0;
	do
	{
		cout << endl;
		answer = get_valid_input<int>("                         Enter your choice: ");
	} while (answer < 1 || answer > 6);
	return answer;
}

//* Add element -------------------------------------------------------------------------------------------------------------------------------------------
// Add a new item by creating a temporary structure array + 1 size,
// adding all the items to it and then adding the new item, we also increase the size ++;
// Once done we delete the old allocated memory and allocate a new memory with the new size,
// copy all the contents of the temp structure array into the original menu array with the new size, finally we delete the temp array.
// We can use memcpy(new_menu, menu, size * sizeof(Menu)); here as well but i wanted to do it manually.
void add_element(int &size, Menu *&menu)
{
	Menu *temp = new Menu[size + 1];
	for (int i = 0; i < size; i++)
	{
		temp[i] = menu[i];
	}
	temp[size] = get_new_item("                         Enter Menu item: ");
	size++;
	delete[] menu;

	menu = new Menu[size];
	for (int i = 0; i < size; i++)
	{
		menu[i] = temp[i];
	}
	delete[] temp;
	cout << "     ->->-> Item added successfully." << endl;
}

// Get a new item we want to enter in our dynamic array
Menu get_new_item(string prompt)
{
	cout << prompt << endl;

	Menu temp;
	temp.item = get_valid_input<string>("                         Enter item name: ");
	temp.price = get_valid_input<float>("                         Enter price of item: ");
	return temp;
}
//* Add element -------------------------------------------------------------------------------------------------------------------------------------------

// Get the item we want to edit by comparing the entered name and the names in the structure array, do nothing if the item is not found
void edit_element(int size, Menu menu[])
{
	bool found = false;
	string item = get_valid_input<string>("     ->->-> Enter the name of the item you want to edit: ");
	for (int i = 0; i < size; i++)
	{
		if (_stricmp(menu[i].item.c_str(), item.c_str()) == 0)
		{
			cout << "     ->->-> Enter the new name and price for " << item << ":" << endl;
			menu[i].item = get_valid_input<string>("                         New name: ");
			menu[i].price = get_valid_input<float>("                         New price: ");
			cout << "     ->->-> " << item << " changed successfully." << endl;
			found = true;
			break;
		}
	}
	if (!found)
	{
		cerr << "     ->->-> " << item << " not found." << endl;
	}
}

// Delete an item by shifting all the elements in the array by 1 starting from the item we want to delete  + 1, do nothing if the item is not found.
// Note for the last element we don't delete it we just reduce the size so we don't see it, but when we remake the menu array we don't copy the last element
void delete_element(int &size, Menu *&menu)
{
	bool found = false;
	string item = get_valid_input<string>("     ->->-> Enter the name of the item you want to delete: ");
	for (int i = 0; i < size; i++)
	{
		if (_stricmp(menu[i].item.c_str(), item.c_str()) == 0)
		{
			for (int j = i + 1; j < size; j++) // Shift the elements by 1
			{
				menu[j - 1] = menu[j];
			}
			size--;
			cout << "     ->->-> " << item << " deleted successfully." << endl;
			found = true;
			break;
		}
	}
	if (!found)
	{
		cerr << "     ->->-> " << item << " not found." << endl;
	}
	else // Allocate proper memory for the new array
	{
		Menu *temp = new Menu[size];
		for (int i = 0; i < size; i++)
		{
			temp[i] = menu[i];
		}
		delete[] menu;

		menu = new Menu[size];
		for (int i = 0; i < size; i++)
		{
			menu[i] = temp[i];
		}
		delete[] temp;
	}
}

//* Get total ---------------------------------------------------------------------------------------------------------------------------------------------
// We get the total by summing up all the costs of the selected items, if we enter GET we are done getting the total
float get_total(int size, Menu menu[])
{
	float total = 0;
	while (true)
	{
		string item = get_valid_input<string>("                         Buy food item: ");
		if (item == "GET")
		{
			cout << endl;
			break;
		}
		total += get_cost(item, size, menu);
	}
	return total;
}

// We get the cost of a item by comparing the entered name with the menu item names, do nothing if the item is not found
float get_cost(string item, int size, Menu menu[])
{
	bool found = false;
	float cost = 0;
	for (int i = 0; i < size; i++)
	{
		if (_stricmp(menu[i].item.c_str(), item.c_str()) == 0)
		{
			cost = menu[i].price;
			found = true;
			break;
		}
	}
	if (!found)
	{
		cerr << "     ->->-> " << item << " not found." << endl;
	}
	return cost;
}
//* Get total ---------------------------------------------------------------------------------------------------------------------------------------------

// Print out the total with a decimal precision of 2, 0.00
void print_total(float total)
{
	cout << "                         Total is: " << "$" << fixed << setprecision(2) << total << endl;
}