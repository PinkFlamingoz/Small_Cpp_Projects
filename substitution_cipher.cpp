#include <iostream>
#include <D:\Xixijan\repos\Small_C++_Projects\basic_get_functions.h>

using namespace std;

bool is_it_26(string text);
bool is_a_alpha(string text);
bool is_it_all_random(string text);
string get_user_text();
string encrypt_text(string key_string, string text);
int swap(char character, int upperOrlower);
void print_result(string text, string result);

const int MAX_LENGTH = 26;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Error 1: Too many or none arguments " << endl << "Usage: ./substitution_cipher key" << endl;
		return 1;
	}
	string key_string = argv[1];
	if (!is_it_26(key_string))
	{
		cout << "Error 2: The key must be 26 characters long" << endl;
		return 2;
	}
	else if (!is_a_alpha(key_string))
	{
		cout << "Error 3: Enter alphabetic characters only" << endl;
		return 3;
	}
	else if (!is_it_all_random(key_string))
	{
		cout << "Error 4: Characters must not be the same" << endl;
		return 4;
	}
	else
	{
		// Get user text
		string text = get_user_text();
		// Encrypt result
		string result = encrypt_text(key_string, text);
		// Print result
		print_result(text, result);

		return 0;
	}
}

bool is_it_26(string key_string)
{
	int length = key_string.length();
	if (length != MAX_LENGTH)
	{
		return false;
	}
	return true;
}

bool is_a_alpha(string key_string)
{
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		if (!isalpha(key_string[i]))
		{
			return false;
		}
	}
	return true;
}

bool is_it_all_random(string key_string)
{
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		for (int j = i + 1; j < MAX_LENGTH; j++)
		{
			if (key_string[i] == key_string[j])
			{
				return false;
			}
		}
	}
	return true;
}

string encrypt_text(string key_string, string text)
{
	string cipher;
	int length = text.length();
	int upper = 65;
	int lower = 97;
	for (int i = 0; i < length; i++)
	{
		if (isalpha(text[i]))
		{
			if (isupper(text[i]))
			{
				cipher += key_string[swap(text[i], upper)];
				cipher[i] = toupper(cipher[i]);
			}
			else if (islower(text[i]))
			{
				cipher += key_string[swap(text[i], lower)];
				cipher[i] = tolower(cipher[i]);
			}
		}
		else
		{
			cipher += text[i];
		}
	}
	return cipher;
}

int swap(char character, int upperOrlower)
{
	int alphaIndex = 0;
	alphaIndex = character - upperOrlower;
	return  alphaIndex;
}

string get_user_text()
{
	string text = get_valid_input<string>("Enter Text:");
	return text;
}

void print_result(string text, string result)
{
	cout << "Plaintext:  " << text << endl;
	cout << "Ciphertext: " << result << endl;
}