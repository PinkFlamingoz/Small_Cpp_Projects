#include <iostream>
#include "headers/basic_functions.h"

using namespace std;

// Functions
bool is_it_26(string text);
bool is_a_alpha(string text);
bool is_it_all_random(string text);
string get_user_text();
string encrypt_text(string key_string, string text);
int swap(char character, int upperOrlower);
void print_result(string text, string result);

// Global
const int MAX_LENGTH = 26;

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 2)
	{
		cerr << "Error 1: Enter only one argument! " << endl << "Usage: ./substitution_cipher [key]" << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}

	// Check if the key is 26 letters
	string key_string = argv[1];
	if (!is_it_26(key_string))
	{
		cerr << "Error 2: The key must be 26 characters long" << endl;
		return 2;
	}

	// Check if all the characters are alphabetical
	if (!is_a_alpha(key_string))
	{
		cerr << "Error 3: Enter alphabetic characters only" << endl;
		return 3;
	}

	// Check if all the characters are random
	if (!is_it_all_random(key_string))
	{
		cerr << "Error 4: Characters must not be the same" << endl;
		return 4;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	string text = get_user_text(); //----------------- Get user text

	string result = encrypt_text(key_string, text); // Encrypt result

	print_result(text, result);	//-------------------- Print result

	return 0; //-------------------------------------- Success
}

// Check if the key is 26 letters
bool is_it_26(string key_string)
{
	int length = key_string.length();
	if (length != MAX_LENGTH)
	{
		return false;
	}
	return true;
}

// Check if all the characters are alphabetical
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

// Check if all the characters are random
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

// Get the user text that we want to encrypt
string get_user_text()
{
	string text = get_valid_input<string>("Enter Text:");
	return text;
}

// Substitution algorithm
string encrypt_text(string key_string, string text)
{
	string cipher = "";
	int length = text.length();
	int upper = 65; //------------------------------------- This is the value of 'A' in the ASCII table
	int lower = 97; //------------------------------------- This is the value of 'a' in the ASCII table
	for (int i = 0; i < length; i++)
	{
		if (isalpha(text[i])) //--------------------------- Is the character a letter at location i
		{
			if (isupper(text[i])) //----------------------- If its a upper case do this for the upper case
			{
				cipher += key_string[swap(text[i], upper)];
				cipher[i] = toupper(cipher[i]);
			}
			else //---------------------------------------- If its a lower case do this for the lower case
			{
				cipher += key_string[swap(text[i], lower)];
				cipher[i] = tolower(cipher[i]);
			}
		}
		else //-------------------------------------------- Do nothing for none alphabetical characters
		{
			cipher += text[i];
		}
	}
	return cipher;
}
// Swap works in such a way where we get the value of the character we want to swap example H = 72 in the ASCII table,
// to get the position in the key of the corresponding letter to swap with we just subtract 72 with the upper 'A' or lower case 'a'
// 72 - 65 = 7, so in our key_string we swap it with that location key_string[7], why because our key_string is a 26 character string and it corresponds with each letter in the alphabet
int swap(char character, int upperOrlower)
{
	int alphaIndex = 0;
	alphaIndex = character - upperOrlower;
	return  alphaIndex;
}

// Print the result
void print_result(string text, string result)
{
	cout << "Plaintext:  " << text << endl;
	cout << "Ciphertext: " << result << endl;
}