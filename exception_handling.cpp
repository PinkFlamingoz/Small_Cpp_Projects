#include <iostream>
#include <exception>
#include "basic_functions.h"

using namespace std;
// NOTE: An exception is an unexpected problem that arises during the execution of a program.
// Exception handling mechanism provide a way to transfer control from one part of a program to another.
// This makes it easy to separate the error handling code from the code written to handle the actual functionality of the program.
// C++ exception handling is built upon three keywords : try, catch, and throw.
//
// try : A block of code which may cause an exception is typically placed inside the try block.
// It’s followed by one or more catch blocks.If an exception occurs, it is thrown from the try block.
//
// catch : this block catches the exception thrown from the try block.
// Code to handle the exception is written inside this catch block.
//
// throw : A program throws an exception when a problem shows up.
// This is done using a throw keyword.
//
// Every try catch should have a corresponding catch block. A single try block can have multiple catch blocks.
//
// Exceptions can be thrown anywhere within a code block using throw statements.
// The operand of the throw statements determines a type for the exception and can be any expression and the type of the result of the expression determines the type of exception thrown.
//
// double division(int a, int b)
// {
//	 if (b == 0)
//	 {
//		throw "Division by zero condition!";
//   }
//	 return (a / b);
// }
//
// The catch block following the try block catches any exception.
// We can specify what type of exception you want to catch and this is determined by the exception declaration that appears in parentheses following the keyword catch.
//
// try
// {
//	 protected code
// }
// catch (...)
// {
//	 code to handle any exception
// }
//
// If we want to specify that a catch block should handle any type of exception that is thrown in a try block, we must put an ellipsis, …, between the parentheses enclosing the exception.

// Classes
class MyException : public exception
{
	public:
	const char *what()
	{
		return  "C++ Exception";
	}
};

class OverSpeed : public exception
{
	int speed;
	public:
	const char *what()
	{
		return "TOP SPEED";
	}
};

int main()
{
	float a = get_valid_input<float>("Enter Numerator: ");
	float b = get_valid_input<float>("Enter Denominator: ");
	float c = 0;

	try
	{
		if (b == 0)
		{
			throw b; // This is being sent to the catch block! or throw "Division by zero condition!";
		}
		c = a / b;
	}
	catch (float b)
	{
		cerr << "Cant divide by 0! You entered: " << b << endl;
	}

	cout << "Result: " << c << endl;

	string d = get_valid_input<string>("Enter number to convert to integer: ");
	int number = 0;

	try
	{
		number = stoi(d);
	}
	catch (const invalid_argument &e)
	{
		cerr << "Cant convert letters or characters! " << e.what() << endl;
	}

	cout << "Concerted number: " << number << endl;

	// There maybe situations where you want to generate some user/program specific exceptions which are not pre-defined in C++.
	// In such cases C++ provided us with the mechanism to create our own exceptions by inheriting the exception class in C++ and overriding its functionality according to our needs.
	// Let us see an example of user-defined exception:
	try
	{
		throw MyException();
	}
	catch (MyException &e)
	{
		cout << "MyException caught" << endl;
		cout << e.what() << endl;
	}
	catch (exception &e)
	{
	//Other errors
	}

	// Let us see an example of user-defined exception:
	int carspeed = 0;
	try
	{
		while (1)
		{
			carspeed += 10;
			if (carspeed > 100)
			{
				OverSpeed s;
				throw s;
			}
			cout << "Carspeed: " << carspeed << endl;
		}
	}
	catch (OverSpeed &ex)
	{
		cout << ex.what();
	}

	return 0;
}
// Exception	         Description
// std::exception		 An exception and parent class of all the standard C++ exceptions.
// std::bad_alloc		 This can be thrown by new.
// std::bad_cast		 This can be thrown by dynamic_cast.
// std::bad_exception	 This is useful device to handle unexpected exceptions in a C++ program
// std::bad_typeid		 This can be thrown by typeid.
// std::logic_error		 An exception that theoretically can be detected by reading the code.
// std::domain_error	 This is an exception thrown when a mathematically invalid domain is used
// std::invalid_argument This is thrown due to invalid arguments.
// std::length_error	 This is thrown when a too big std::string is created
// std::out_of_range	 This can be thrown by the at method from for example a std::vector and std::bitset<>::operator[]().
// std::runtime_error	 An exception that theoretically can not be detected by reading the code.
// std::overflow_error	 This is thrown if a mathematical overflow occurs.
// std::range_error		 This is occurred when you try to store a value which is out of range.
// std::underflow_error	 This is thrown if a mathematical underflow occurs.