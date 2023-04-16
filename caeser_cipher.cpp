#include <iostream>
#include "basic_functions.h"

using namespace std;

// Functions
bool is_a_digit(string text);
string get_user_text();
string encrypt_text(string text, int key);
char rotate(char character, int upperOrlower, int key);
void print_result(string text, string result);

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 2)
	{
		cerr << "Error 1: Enter only one argument! " << endl << "Usage: ./caeser_cipher [key]" << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}

	// Ensure all the characters in the key are digits
	string key_string = argv[1];
	if (!is_a_digit(key_string))
	{
		cerr << "Error 2: Enter a digit " << endl;
		return 2;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	int key = stoi(key_string); //------------- Convert the key to an integer

	string text = get_user_text(); //---------- Get user text

	string result = encrypt_text(text, key); // Encrypt result with the key

	print_result(text, result); //------------- Print result

	return 0; //------------------------------- Success
}

// Check if all the characters are digits from argv[1]
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

// Get the user text that we want to encrypt
string get_user_text()
{
	string text = get_valid_input<string>("Enter Text: ");
	return text;
}

// Caesar algorithm
string encrypt_text(string text, int key)
{
	string cipher = "";
	int upper = 65; //-------------------------------- This is the value of 'A' in the ASCII table
	int lower = 97; //-------------------------------- This is the value of 'a' in the ASCII table
	int length = text.length();
	for (int i = 0; i < length; i++)
	{
		if (isalpha(text[i])) //---------------------- Is the character a letter at location i
		{
			if (isupper(text[i])) //------------------ If its a upper case do this for the upper case
			{
				cipher += rotate(text[i], upper, key);
			}
			else //----------------------------------- If its a lower case do this for the lower case
			{
				cipher += rotate(text[i], lower, key);
			}
		}
		else //--------------------------------------- Do nothing for none alphabetical characters
		{
			cipher += text[i];
		}
	}
	return cipher;
}

// More formally, Caesar's algorithm (i.e., cipher) encrypts messages by "rotating" each letter by k positions.
// More formally, if P is some plaintext(i.e., an unencrypted message),
// Pi is the i(th) character in P, and k is a secret key(i.e., a non - negative integer),
// then each letter, Ci, in the ciphertext, C, is computed as:
// Ci = (Pi + k ) % 26
// Why % 26 well if we have the example of letter H to encrypt with the shift of 42 then we would get,
// Pi = ( 72 - 65( this is the ASCII value of 'A' ) ) = 7 We calculate this to get the position of the H character in the alphabet, and we know H is the 7th letter in the alphabet.
// Now we can shift that letter by the key and know in which position it will end up in the alphabet.
// 7 + 42 = 49 but 49 is the character 1 in the ASCII table so we need to mod it by 26 because thats how many letters we have in the alphabet and we get
// 49 % 26 = 23 and we have it H becomes X but not so fast to get the ASCII value of X we need to add the character of 'A' which is 65 that we subtracted in the first place to get the position of H
// 23 + 65 = 88 and we finally have our answer.

// Rotate by the given KEY
char rotate(char character, int upperOrlower, int key)
{
	int help = 0;
	int alphaIndex = 0;
	alphaIndex = character - upperOrlower;
	help = (alphaIndex + key) % 26;
	help += upperOrlower;
	return help;
}

// Print the results
void print_result(string text, string result)
{
	cout << "Plaintext:  " << text << endl;
	cout << "Ciphertext: " << result << endl;
}