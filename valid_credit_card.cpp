#include <iostream>
#include "headers/basic_functions.h"

using namespace std;

// Functions
long long get_credit_input(void);
void print_card(long long card);
int calculate_checksum(long long card);
int get_length(long long card);
int get_first_two_digits(long long card);
void get_individual_numbers_from_string(long long number);
void get_individual_every_other_number_from_string(long long number);
void get_individual_every_other_number_from_string_twisted(long long number);

int main()
{
	long long card = get_credit_input(); // Get the credit card

	print_card(card); //------------------- Calculate checksum and print the correct response

	return 0; //--------------------------- Success
}

// Get the credit card
long long get_credit_input(void)
{
	long long card = 0;
	do
	{
		card = get_valid_input<long long>("Enter credit card number: ");
	} while (card < 1);
	return card;
}

// Print the correct type of card
void print_card(long long card)
{
	int check = calculate_checksum(card);
	int i = get_length(card);
	int b = get_first_two_digits(card);
	if (check == 0)
	{
		if (i == 15 && (b == 34 || b == 37))
		{
			cout << "Card is: AMEX" << endl;
		}
		else if (i == 16 && (b == 51 || b == 52 || b == 53 || b == 54 || b == 55))
		{
			cout << "Card is: MASTERCARD" << endl;
		}
		else if ((i == 13 || i == 16) && (b == 4))
		{
			cout << "Card is: VISA" << endl;
		}
		else
		{
			cout << "Card is: INVALID" << endl;
		}
	}
	else
	{
		cout << "Card is: INVALID" << endl;
	}
}

//                   4003600000000014
// 1. digit = 4, card= 400360000000001,                                              sum = 0 + 4 = 4
// 2. digit = 1, card= 40036000000000,  if{digit= 1 * 2 = 2},                        sum = 4 + 2 = 6
// 3. digit = 0, card= 4003600000000,                                                sum = 6 + 0 = 6
// 4. digit = 0, card= 400360000000,    if{digit= 0 * 2 = 0},                        sum = 6 + 0 = 6
// 5. digit = 0, card= 40036000000,                                                  sum = 6 + 0 = 6
// 6. digit = 0, card= 4003600000,      if{digit= 0 * 2 = 0},                        sum = 6 + 0 = 6
// 7. digit = 0, card= 400360000,                                                    sum = 6 + 0 = 6
// 8. digit = 0, card= 40036000,        if{digit= 0 * 2 = 0},                        sum = 6 + 0 = 6
// 9. digit = 0, card= 4003600,                                                      sum = 6 + 0 = 6
//10. digit = 0, card= 400360,          if{digit= 0 * 2 = 0},                        sum = 6 + 0 = 6
//11. digit = 0, card= 40036,                                                        sum = 6 + 0 = 6
//12. digit = 6, card= 4003,            if{digit= 6 * 2 = 12; if{digit= 12-9 = 3}},  sum = 6 + 3 = 9
//13. digit = 3, card= 400,                                                          sum = 9 + 3 = 12
//14. digit = 0, card= 40,              if{digit= 0 * 2 = 0},                        sum = 12 + 0 = 12
//15. digit = 0, card= 4,                                                            sum = 12 + 0 = 12
//16. digit = 4, card= ,                if{digit= 4 * 2 = 8},                        sum = 12 + 8 = 20
int calculate_checksum(long long card)
{
	int digit = 0;
	int sum = 0;
	int i = 0;
	while (card > 0)
	{
		digit = card % 10; //-------- Gets and resets the last digit
		card = card / 10; //--------- Removes the last number step by step
		if (i % 2 == 1)
		{
			digit = digit * 2;
			if (digit > 9)         // Equivalent of adding the 2 digits
			{                      // Of a double integer number
				digit = digit - 9; // 12 - 9 = 3, 1 + 2 = 3
			}
		}
		sum += digit;
		i++;
	}
	return sum % 10;
}
// When you use the modulo operator % with 10, it returns the remainder when the number is divided by 10.
// This means that it gives you the last digit of the number.
// For example, if you have the number 123, then 123 % 10 would give you 3.
// This is because 123 divided by 10 gives you a quotient of 12 with a remainder of 3, so the remainder is 3, which is the last digit of the number.
// Similarly, if you have the number 456, then 456 % 10 would give you 6, because 456 divided by 10 gives you a quotient of 45 with a remainder of 6.
// Using the modulo operator with 10 can be helpful when you want to extract the last digit of a number,
// or when you want to determine if a number is divisible by 10 (if the result is 0).

// Get the length of the credit card
int get_length(long long card)
{
	int count = 0;
	while (card > 0)
	{
		card = card / 10;
		count++;
	}
	return count;
}

// Get the first two digits of a number or the first digit
int get_first_two_digits(long long card)
{
	int two_digits = 0;
	int first_digit = 0;
	while (card >= 100)
	{
		card = card / 10;
	}
	two_digits = card;
	first_digit = two_digits / 10;
	if (first_digit == 4)
	{
		return first_digit;
	}
	else
	{
		return two_digits;
	}
}

void get_individual_numbers_from_string(long long number)
{
	int digit = 0;
	while (number > 0)
	{
		digit = number % 10; //- Gets and resets the last digit
		number = number / 10; // Removes the last digit of the number step by step
		cout << digit << " ";
	}
	cout << endl;
}

void get_individual_every_other_number_from_string(long long number)
{
	int digit = 0;
	int i = 0;
	while (number > 0)
	{
		digit = number % 10; //- Gets and resets the last digit
		number = number / 10; // Removes the last digit of the number step by step
		if (i % 2 == 0) //------ Even position numbers
		{
			cout << digit << " ";
		}
		i++;
	}
	cout << endl;
}

void get_individual_every_other_number_from_string_twisted(long long number)
{
	int digit = 0;
	int i = 0;
	while (number > 0)
	{
		digit = number % 10; //- Gets and resets the last digit
		number = number / 10; // Removes the last digit of the number step by step
		if (i % 2 == 1) //------ Odd position numbers
		{
			cout << digit << " ";
		}
		i++;
	}
	cout << endl;
}