#include <iostream>
#include <limits>

using namespace std;

string correct_text(string text);
void print_result(string result);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Error 1: Enter only one argument! " << endl;
		return 1;
	}
	else
	{
		// Check for vowels and replace them
		string  result = correct_text(argv[1]);
		// Print result
		print_result(result);

		return 0;
	}
}

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

void print_result(string result)
{
	cout << result << endl;
}