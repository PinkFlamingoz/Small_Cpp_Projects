#include <iostream>
#include "basic_functions.h"

using namespace std;

// Functions
int multiply_two_numbers(int num1, int num2);
void swap_values(int &a, int &b);
void odd_or_even(int n);
void is_it_a_power_of_2(int n);
void count_set_bits(int n);

int main()
{
	int num1 = 0, num2 = 0, iand = 0, ior = 0, ixor = 0, shift1 = 0, shift2 = 0, complement = 0, mul = 0;

	num1 = get_valid_input<int>("Number 1: ");
	num2 = get_valid_input<int>("Number 2: ");
	iand = num1 & num2;
	ior = num1 | num2;
	ixor = num1 ^ num2;
	shift1 = num1 << 1; // Multiply
	shift2 = num1 >> 1; // Devide
	complement = ~num1; // NOT

	mul = multiply_two_numbers(num1, num2);

	cout << num1 << " AND " << num2 << " is " << iand << endl;
	cout << num1 << " OR " << num2 << " is " << ior << endl;
	cout << num1 << " XOR " << num2 << " is " << ixor << endl;
	cout << num1 << " Multiply by itself: " << shift1 << endl;
	cout << num1 << " Devide by itself: " << shift2 << endl;
	cout << num1 << " Complement " << complement << endl;
	cout << num1 << " * " << num2 << " is " << mul << endl;

	odd_or_even(num1);
	is_it_a_power_of_2(num1);
	count_set_bits(num1);
	swap_values(num1, num2);

	return 0;
}

// Multiply two numbers with bitwise operations
int multiply_two_numbers(int a, int b)
{
	int result = 0;
	while (a > 0)
	{
		if (b & 1)
		{
			result += a;
		}
		a = a << 1;
		b = b >> 1;
	}
	return result;
}
// The multiplication of two numbers x, y can be written as x * y = (x * 2) * (y / 2) if y is even, else it's equal to x * y = (x * y) * (y / 2) + x.

// Swap values
void swap_values(int &a, int &b)
{
	cout << a << " " << b << endl;
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	cout << a << " " << b << endl;
}

// Is it odd or even
void odd_or_even(int n)
{
	if (n & 1)
	{
		cout << "ODD" << endl;
	}
	else
	{
		cout << "EVEN" << endl;
	}
}

// Is it a power of 2
void is_it_a_power_of_2(int n)
{
	if (n && !(n & (n - 1)))
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
}

//Count set bits
void count_set_bits(int n)
{
	int count = 0;
	while (n)
	{
		count += n & 1;
		n >>= 1;
	}
	cout << "Bits: " << count << endl;
}