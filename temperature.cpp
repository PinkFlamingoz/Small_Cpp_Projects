#include <iostream>
#include <limits>
#include <string>

using namespace std;

struct Temperature
{
	string city = "";
	int temp = 0;
};

int get_size();
Temperature get_temperatures_and_names(string prompt);
void fill_temperatures_array(int size, Temperature temperatures[]);
void print_data(int size, Temperature temperatures[]);
void sort_data_bubble(int size, Temperature temperatures[]);

int main()
{
	int size = get_size();
	Temperature* temperatures = new Temperature[size];

	fill_temperatures_array(size, temperatures);

	sort_data_bubble(size, temperatures);

	print_data(size, temperatures);

	delete[] temperatures;

	return 0;
}

template <typename T>
T get_valid_input(const string& prompt)
{
	T input;
	while (true)
	{
		cout << prompt;
		cin >> input;
		if (cin.fail())
		{
			// Input is not valid
			cout << "Error: Please enter a valid input." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			// Input is valid
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}
	return input;
}

template<>
string get_valid_input<string>(const string& prompt)
{
	string input;
	while (true)
	{
		cout << prompt;
		getline(cin, input);
		if (cin.fail() || input.empty())
		{
			// Input is not valid
			cout << "Error: Please enter a valid input." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			// Input is valid
			break;
		}
	}
	return input;
}

int get_size()
{
	int size = 0;
	do
	{
		size = get_valid_input<int>("Enter size of database: ");
	} while (size < 1);
	return size;
}

Temperature get_temperatures_and_names(string prompt)
{
	cout << prompt << endl;

	Temperature temporary;

	temporary.city = get_valid_input<string>("Enter city: ");
	temporary.temp = get_valid_input<int>("Enter temperature: ");

	return temporary;
}

void fill_temperatures_array(int size, Temperature temperatures[])
{
	for (int i = 0; i < size; i++)
	{
		temperatures[i] = get_temperatures_and_names("Enter Data --------------");
	}
}

void print_data(int size, Temperature temperatures[])
{
	for (int i = 0; i < size; i++)
	{
		cout << temperatures[i].city << ": " << temperatures[i].temp << endl;
	}
}

void sort_data_bubble(int size, Temperature temperatures[])
{
	int swap_counter = -1;
	Temperature help;							//When copying one struct to another, no need to assign individual elements. The entire struct can be assigned in one statement
	while (swap_counter != 0)
	{
		swap_counter = 0;
		for (int i = 0; i < size - 1; i++)
		{
			if (temperatures[i].temp < temperatures[i + 1].temp)
			{
				help = temperatures[i];
				temperatures[i] = temperatures[i + 1];
				temperatures[i + 1] = help;
				swap_counter++;
			}
		}
	}
}