#include <iostream>
#include <limits>
#include <string>

using namespace std;

string get_user_text();
void convert_decimal_to_binary(string text);
void reverse_the_bits(int size, int structure[]);
void print_bulb(int bit);

const int EIGHT_BITS = 8;

int main()
{
	// Get user text
	string text = get_user_text();
	// Conver the decimal to binary
	convert_decimal_to_binary(text);

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

string get_user_text()
{
	string text = get_valid_input<string>("Enter Text:");
	return text;
}

void convert_decimal_to_binary(string text)
{
	int devide;
	int structure[EIGHT_BITS];
	int length = text.length();
	for (int i = 0; i < length; i++)
	{
		devide = text[i]; // We simply get the number of the first character in this devide
		for (int j = 0; j < EIGHT_BITS; j++)
		{
			if (devide % 2 == 0)
			{ // Check the mod and store it in a structure
				structure[j] = 0;
			}
			else if (devide % 2 == 1)
			{
				structure[j] = 1;
			}
			devide = devide / 2; // We get the new value to check the mod
		}
		reverse_the_bits(EIGHT_BITS, structure);
		for (int c = 0; c < EIGHT_BITS; c++)
		{
			print_bulb(structure[c]);
		}
		cout << endl; // Print a new line after each set of 8 bits
	}
}

void reverse_the_bits(int size, int structure[])
{ // We use this to reverse the order of the valuse in a array
	int help; // This is only used to hold the value of the of the current i in the array, so we dont lose it when we swap it
	for (int i = 0; i < size / 2; i++) // Why half the size? Well because we are swapping first and last, second and secont to last , third and third to last, they meet in the middel where we dont swap at all
	{
		help = structure[i];
		structure[i] = structure[size - i - 1];  // Swap the last value to the first structure[0] = structure[8-0-1], we need size-i-1 becuase to go down the order, example here [8-0-1]= 7 then we go to [8-1-1]= 6 and so on. we must have that initial -1 because the int i is set to 0, and we must have it set to 0 to get access to the first value or 0th
		structure[size - i - 1] = help;
	}
}

void print_bulb(int bit)
{
	if (bit == 0)
	{
		// Dark emoji
		//cout << u8"\u26AB";
		cout << '0';
	}
	else if (bit == 1)
	{
		// Light emoji
		cout << "1";//cout << u8"\U0001F7E1";
	}
}