#include <iostream>
#include "basic_functions.h"

using namespace std;

// Globals
const int EIGHT_BITS = 8;

// Functions
string get_user_text();
void convert_decimal_to_binary(string text);
void reverse_the_bits(int size, int structure[]);
void print_bulb(int bit);

int main()
{
	system("chcp 65001"); //----------- Set the console output to use UTF-8 encoding

	string text = get_user_text(); //-- Get user text

	convert_decimal_to_binary(text); // Convert the decimal to binary

	return 0; //----------------------- Success
}

// Get the text to convert
string get_user_text()
{
	string text = get_valid_input<string>("Enter Text: ");
	return text;
}

// Converting Algorithm
void convert_decimal_to_binary(string text)
{
	int divide = 0;
	int structure[EIGHT_BITS]{};
	int length = text.length();
	for (int i = 0; i < length; i++)
	{
		divide = text[i]; //----------------------- Put the first character in this divide aka its ASCII value
		for (int j = 0; j < EIGHT_BITS; j++)
		{
			if (divide % 2 == 0) //---------------- Check if that value has a mod of 0
			{
				structure[j] = 0;
			}
			else //-------------------------------- Else that mod is 1
			{
				structure[j] = 1;
			}
			divide = divide / 2; //---------------- Get the new value to check the mod
		}

		reverse_the_bits(EIGHT_BITS, structure); // Reverse the bits because we get the opposite way

		for (int c = 0; c < EIGHT_BITS; c++) //---- Print a set of 8 bits
		{
			print_bulb(structure[c]); //----------- Print either 0 or 1;
		}
		cout << endl; //--------------------------- Print a new line after each set of 8 bits
	}
}

// In programming, the operator % (modulo) returns the remainder of dividing one number by another.
// So, a number % 2 means the remainder when that number is divided by 2.
// When dividing by 2, there are only two possible remainders : 0 and 1.
// If the result of the operation is 0, it means that the number is even, and if the result is 1, it means that the number is odd.
// For example, if we take the number 5 % 2, the result would be 1 because when we divide 5 by 2, we get a quotient of 2 with a remainder of 1.
// Similarly, 6 % 2 would be 0, because 6 is evenly divisible by 2 with no remainder, making it an even number.
//
// Example H = 72;
//
// 72 % 2 = 0; 72 / 2 = 36;
// 36 % 2 = 0; 36 / 2 = 18;
// 18 % 2 = 0; 18 / 2 = 9;
// 9 % 2 =  1; 9 / 2 = 4; We get 4.5 but we truncate the value
// 4 % 2 =  0; 4 / 2 = 2;
// 2 % 2 =  0; 2 / 2 = 1;
// 1 % 2 =  1; 1 / 2 = 0; Again 0.5
// 0 % 2 =  0; 0 / 2 = 0; STOP
//
// We got in structure = { 0, 0, 0, 1, 0, 0, 1, 0}
// We simply reverse this and we have it in binary form
//
// To convert a decimal number to binary, we can repeatedly divide the decimal number by 2 and keep track of the remainders.
// The remainders will give us the binary digits, with the least significant bit (rightmost bit) being the first remainder we calculate,
// and the most significant bit (leftmost bit) being the last remainder we calculate.

// Reverse the order of the values in array
void reverse_the_bits(int size, int structure[])
{
	int help = 0; //------------------------------ This is only used to hold the value of the of the current i in the array, so we don't lose it when we swap it
	for (int i = 0; i < size / 2; i++) //--------- Why half the size? Well because we are swapping first and last, second and second to last , third and third to last, they meet in the middle where we don't swap at all
	{
		help = structure[i];
		structure[i] = structure[size - i - 1]; // Swap the last value to the first structure[0] = structure[8-0-1], we need size-i-1 because to go down the order, example here [8-0-1] = 7 then we go to [8-1-1] = 6 and so on. we must have that initial -1 because the int i is set to 0, and we must have it set to 0 to get access to the first value or 0th
		structure[size - i - 1] = help;
	}
}

// Print the bits
void print_bulb(int bit)
{
	if (bit == 0)
	{
		// Dark emoji
		cout << "\u26AB";
	 // cout << '0';
	}
	else if (bit == 1)
	{
		// Light emoji
		cout << "\U0001F7E1";
	 // cout << "1";
	}
}