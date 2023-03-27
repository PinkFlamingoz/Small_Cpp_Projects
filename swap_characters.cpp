#include <iostream>

using namespace std;

// Functions
string correct_text(string text);
void print_result(string result);

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 2)
	{
		cerr << "Error 1: Enter only one argument! " << endl << "Usage: ./swap_characters [text]" << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	string  result = correct_text(argv[1]); // Check for vowels and replace them

	print_result(result); //------------------ Print result

	return 0; //------------------------------ Success
}

// Check for vowels and use the switch case to do a certain action when a certain letter appears
string correct_text(string text)
{
	int length = text.length();
	for (int i = 0; i < length; i++)
		switch (text[i])
		{
			case 'a':
			{
				text[i] = '6';
				break;
			}
			case 'e':
			{
				text[i] = '3';
				break;
			}
			case 'i':
			{
				text[i] = '1';
				break;
			}
			case 'o':
			{
				text[i] = '0';
				break;
			}
		}

	return text;
}

// Print the results
void print_result(string result)
{
	cout << result << endl;
}