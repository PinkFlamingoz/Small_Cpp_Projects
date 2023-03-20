#include <iostream>
#include <iomanip>
#include <cstring>
#include "basic_get_functions.h"

using namespace std;

struct Menu
{
	string item = "";
	float price = 0;
};

// We use Menu* menu to read data only and Menu*& menu to modify data
// & is pointing it as a reference not a copy

void get_menu(Menu menu[]);
void print_menu(int size, Menu menu[]);
int get_size_of_menu(Menu *menu);
float get_cost(string item, int size, Menu menu[]);
float get_total(int size, Menu menu[]);
void print_total(float total);
void modify_array(int &size, Menu *&menu);
void add_element(int &size, Menu *&menu);
void edit_element(int size, Menu *&menu);
void delete_element(int &size, Menu *&menu);

int main()
{
	int DEFAULT = 10;
	Menu *menu = new Menu[DEFAULT];
	get_menu(menu);

	int size = get_size_of_menu(menu);
	print_menu(size, menu);

	modify_array(size, menu);

	delete[] menu;

	return 0;
}

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

void print_menu(int size, Menu menu[])
{
	cout << " .-.-.  .-.-.  .-.-.     .-.-.  .-.-.  .-.-.  .-.-.     .-.-.  .-.-.  .-.-.\n"
		"=`. .'==`. .'==`. .'== Welcome to Beach Burger Shack! ==`. .'==`. .'==`. .'=\n"
		"   .      .      .         .      .      .      .         .      .      .   \n\n";
	cout << " Choose from the following menu to order. Press space then enter when done.\n\n";
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

int get_size_of_menu(Menu *menu)
{
	int size = 0;
	while (menu[size].item != "" && menu[size].price != 0)
	{
		size++;
	}
	return size;
}

float get_cost(string item, int size, Menu menu[])
{
	float cost = 0;
	for (int i = 0; i < size; i++)
	{
		if (stricmp(menu[i].item.c_str(), item.c_str()) == 0)
		{
			cost += menu[i].price;
		}
	}
	return cost;
}

float get_total(int size, Menu menu[])
{
	float total = 0;
	while (true)
	{
		string item = get_valid_input<string>("                         Buy food item: ");
		if (item == " ")
		{
			cout << endl;
			break;
		}

		total += get_cost(item, size, menu);
	}
	return total;
}

void print_total(float total)
{
	cout << "                         Total is: "
		<< "$" << fixed << setprecision(2) << total << endl;
}

Menu get_new_item(string prompt)
{
	cout << prompt << endl;

	Menu temp;

	temp.item = get_valid_input<string>("                         Enter item name: ");
	temp.price = get_valid_input<float>("                         Enter price of item: ");

	return temp;
}

void modify_array(int &size, Menu *&menu)
{
	bool done = false;
	while (!done)
	{
		cout << "            |__*__|      1) Edit an item        |__*__|" << endl;
		cout << "            |__*__|      2) Add an item         |__*__|" << endl;
		cout << "            |__*__|      3) Delete an item      |__*__|" << endl;
		cout << "            |__*__|      4) Get total price     |__*__|" << endl;
		cout << "            |__*__|      5) Print Menu          |__*__|" << endl;
		cout << "            |__*__|      6) Done editing        |__*__|" << endl;
		int answer = 0;
		do
		{
			cout << endl;
			answer = get_valid_input<int>("                         Enter your choice: ");
		} while (answer < 1 || answer > 6);
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
				cout << endl;
				print_menu(size, menu);
				cout << endl;
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
				cout << "                         Invalid choice. Please try again." << endl;
				cout << endl;
				break;
			}
		}
	}
	// Allocate memory for the new array
	// Menu* new_menu = new Menu[size];
	// Copy the modified elements to the new array
	// memcpy(new_menu, menu, size * sizeof(Menu));
	// Free memory for the old array
	// delete[] menu;
	// Update the pointer to the new array
	// menu = new_menu;
}

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
	menu = temp;
	cout << "     ->->-> Item added successfully." << endl;
}

void edit_element(int size, Menu *&menu)
{
	bool found = false;
	string item = get_valid_input<string>("     ->->-> Enter the name of the item you want to edit: ");
	for (int i = 0; i < size; i++)
	{
		if (stricmp(menu[i].item.c_str(), item.c_str()) == 0)
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
		cout << "     ->->-> " << item << " not found." << endl;
	}
}

void delete_element(int &size, Menu *&menu)
{
	bool found = false;
	string item = get_valid_input<string>("     ->->-> Enter the name of the item you want to delete: ");
	for (int i = 0; i < size; i++)
	{
		if (stricmp(menu[i].item.c_str(), item.c_str()) == 0)
		{
			// Shift all elements after i to the left by 1
			for (int j = i + 1; j < size; j++)
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
		cout << "     ->->-> " << item << " not found." << endl;
	}
}