#include <iostream>
#include "basic_functions.h"

using namespace std;

// Classes
class Complex_Numbers
{
	private:
	// Member variables
	int real_part;
	float imaginary_part;

	public:
	//Member functions

	// Constructor
	Complex_Numbers()
	{
		real_part = 0;
		imaginary_part = 0;
	}

	// Parameter Constructor
	Complex_Numbers(int real_part, float imaginary_part)
	{
		this->real_part = real_part;
		this->imaginary_part = imaginary_part;
	}

	// Destructor
	~Complex_Numbers()
	{
	}

	// Display the number
	void display_number()
	{
		cout << "Complex number: " << real_part << " + " << imaginary_part << "i" << endl;
	}

	// Get real_part
	int get_real_part()
	{
		return real_part;
	}

	// Get imaginary_part
	float get_imaginary_part()
	{
		return imaginary_part;
	}
};

// Functions
Complex_Numbers addition(Complex_Numbers c1, Complex_Numbers c2);
bool is_a_digit(string digit);

int main(int argc, char *argv[])
{	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 5)
	{
		cerr << "Error 1: Too many or none arguments " << endl << "Usage: ./complex_numbers [real 1] [imaginary 1] [real 2] [imaginary 2]" << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}

	// Ensure all the characters in the numbers are digits
	if (!is_a_digit(argv[1]) || !is_a_digit(argv[2]) || !is_a_digit(argv[3]) || !is_a_digit(argv[4]))
	{
		cerr << "Error 2: Enter a digit " << endl;
		return 2;
	}

	// Convert the user inputed values
	int c1r = stoi(argv[1]);
	float c1i = stof(argv[2]);
	int c2r = stoi(argv[3]);
	float c2i = stof(argv[4]);
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	Complex_Numbers c1(c1r, c1i), c2(c2r, c2i), c3; // Create the compex numbers two with the parameter constructor and one with the default constructor

	c3 = addition(c1, c2); //------------------------- In the third complex number store the addition by returning a complex number

	c1.display_number(); //--------------------------- Display the information
	c2.display_number(); //--------------------------- Display the information
	c3.display_number(); //--------------------------- Display the information

	return 0; //-------------------------------------- Success
}

// Add two complex numbers
Complex_Numbers addition(Complex_Numbers c1, Complex_Numbers c2)
{
	int real = 0;
	float imaginar = 0;

	real = c1.get_real_part() + c2.get_real_part();
	imaginar = c1.get_imaginary_part() + c2.get_imaginary_part();

	Complex_Numbers temp(real, imaginar);

	return temp;
}

// Check if all the characters are digits from argv[]
bool is_a_digit(string digit)
{
	int length = digit.length();
	for (int i = 0; i < length; i++)
	{
		if (!isdigit(digit[i]))
		{
			return false;
		}
	}
	return true;
}