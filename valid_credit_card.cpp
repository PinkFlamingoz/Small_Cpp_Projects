#include <iostream>
#include <limits>

using namespace std;

long long get_credit_input(void);
int calculate_checksum(long long card);
void get_individual_numbers_from_string(long long number);
void get_individual_every_other_number_from_string(long long number);
void get_individual_every_other_number_from_string_twisted(long long number);
int get_lenght(long long card);
int get_first_two_digits(long long card);
void print_card(long long card);

int main()
{
	// Get input
	long long card = get_credit_input();
	// Calculate checksum
	// Check for card length and starting digits
	// Print AMEX, MASTERCARD, VISA, INVALID
	print_card(card);

	return 0;
}

template <typename T>
T get_valid_input(const string& prompt) {
	T input;
	while (true) {
		cout << prompt;
		if (cin >> input) {
			// The user entered a valid number
			break;
		}
		else {
			// The user did not enter a valid number
			cout << "Error: Please enter a valid input." << endl;
			cin.clear(); // Clear the error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any input in the buffer
		}
	}
	return input;
}

long long get_credit_input(void)
{
	long long card;
	do
	{
		card = get_valid_input<long long>("Enter credit card number: ");
	} while (card < 1);
	return card;
}

//                   4003600000000014
// 1.digit= 4, card= 400360000000001,                                              sum= 0 + 4 = 4
// 2.digit= 1, card= 40036000000000,  if{digit= 1 * 2 = 2},                        sum= 4 + 2 = 6
// 3.digit= 0, card= 4003600000000,                                                sum= 6 + 0 = 6
// 4.digit= 0, card= 400360000000,    if{digit= 0 * 2 = 0},                        sum= 6 + 0 = 6
// 5.digit= 0, card= 40036000000,                                                  sum= 6 + 0 = 6
// 6.digit= 0, card= 4003600000,      if{digit= 0 * 2 = 0},                        sum= 6 + 0 = 6
// 7.digit= 0, card= 400360000,                                                    sum= 6 + 0 = 6
// 8.digit= 0, card= 40036000,        if{digit= 0 * 2 = 0},                        sum= 6 + 0 = 6
// 9.digit= 0, card= 4003600,                                                      sum= 6 + 0 = 6
//10.digit= 0, card= 400360,          if{digit= 0 * 2 = 0},                        sum= 6 + 0 = 6
//11.digit= 0, card= 40036,                                                        sum= 6 + 0 = 6
//12.digit= 6, card= 4003,            if{digit= 6 * 2 = 12; if{digit= 12-9 = 3}},  sum= 6 + 3 = 9
//13.digit= 3, card= 400,                                                          sum= 9 + 3 = 12
//14.digit= 0, card= 40,              if{digit= 0 * 2 = 0},                        sum= 12 + 0 = 12
//15.digit= 0, card= 4,                                                            sum= 12 + 0 = 12
//16.digit= 4, card= ,                if{digit= 4 * 2 = 8},                        sum= 12 + 8 = 20
int calculate_checksum(long long card)
{
	int digit;
	int sum = 0;
	int i = 0;
	while (card > 0)
	{
		digit = card % 10;   // gets and resets the last digit
		card = card / 10;    // removes the last number setp by step
		if (i % 2 == 1)
		{
			digit = digit * 2;
			if (digit > 9)            // equivelent of adding the 2 digits
			{                         // of a double integer number
				digit = digit - 9;    // 12 - 9 = 3, 1 + 2 = 3
			}
		}
		sum += digit;
		i++;
	}
	return sum % 10;
}

int get_lenght(long long card)
{
	int count = 0;
	while (card > 0)
	{
		card = card / 10;
		count++;
	}
	return count;
}

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

void print_card(long long card)
{
	int check = calculate_checksum(card);
	int i = get_lenght(card);
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

void get_individual_numbers_from_string(long long number) {
	int digit;
	while (number > 0) {
		digit = number % 10;
		number = number / 10;
		cout << digit << " ";
	}
	cout << endl;
}

void get_individual_every_other_number_from_string(long long number) {
	int digit;
	int i = 0;
	while (number > 0) {
		digit = number % 10;
		number = number / 10;
		if (i % 2 == 0) {
			cout << digit << " ";
		}
		i++;
	}
	cout << endl;
}

void get_individual_every_other_number_from_string_twisted(long long number) {
	int digit;
	int i = 0;
	while (number > 0) {
		digit = number % 10;
		number = number / 10;
		if (i % 2 == 1) {
			cout << digit << " ";
		}
		i++;
	}
	cout << endl;
}