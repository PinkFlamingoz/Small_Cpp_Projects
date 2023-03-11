#include <iostream>
#include <limits>
#include <string>

using namespace std;

bool is_a_digit(string text);
string get_user_text();
string encrypt_text(string text, int key);
char rotate(char character, int upperOrlower, int key);
void print_result(string text, string result);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Error 1: Too many or none arguments " << endl << "Usage: ./caesar_cipher key" << endl;
		return 1;
	}
	string key_string = argv[1];
	if (!is_a_digit(key_string))
	{
		cout << "Error 2: Enter a digit " << endl;
		return 2;
	}
	int key = stoi(key_string);
	if (key < 1)
	{
		cout << "Error 3: Must be positive number" << endl;
		return 3;
	}
	else
	{
		// Get user text
		string text = get_user_text();
		// Encrypt result
		string  result = encrypt_text(text, key);
		// Print result
		print_result(text, result);

		return 0;
	}
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

bool is_a_digit(string key_string)
{
	int length = key_string.length();
	for (int i = 0; i < length; i++)
	{
		if (!isdigit(key_string[i]))
		{
			return false;
		}
	}
	return true;
}

string get_user_text()
{
	string text = get_valid_input<string>("Enter Text:");
	return text;
}

string encrypt_text(string text, int key)
{
	string cipher;
	int upper = 65;
	int lower = 97;
	int length = text.length();
	for (int i = 0; i < length; i++)
	{
		if (isalpha(text[i]))
		{
			if (isupper(text[i]))
			{
				cipher += rotate(text[i], upper, key);
			}
			else if (islower(text[i]))
			{
				cipher += rotate(text[i], lower, key);
			}
		}
		else
		{
			cipher += text[i];
		}
	}
	return cipher;
}

char rotate(char character, int upperOrlower, int key)
{
	int help = 0;
	int alphaIndex = 0;
	alphaIndex = character - upperOrlower;
	help = (alphaIndex + key) % 26;
	help += upperOrlower;
	return  help;
}

void print_result(string text, string result)
{
	cout << "Plaintext:  " << text << endl;
	cout << "Ciphertext: " << result << endl;
}