#include <iostream>

using namespace std;
// NOTE: The scope resolution operator "::" is used to access elements within a specific scope, such as a namespace or a class.
// It allows you to specify the namespace or class in which a particular identifier (variable, function, or class member) is defined, so that you can avoid naming conflicts and access the correct definition.
//
// When used with namespaces, the scope resolution operator allows you to access variables, functions, or classes that are defined in a namespace.
// For example, if you have a function called "print" in a namespace called "std", you can access it using the scope resolution operator as "std::print".
//
// When used with classes or structures, the scope resolution operator is used to access members of the class or structure that are defined outside of its declaration.
// For example, if you have a class called "Person" with a member function called "getName()", you can access it using the scope resolution operator as "Person::getName()".
//
// It's important to note that the scope resolution operator can only be used with static members of a class or namespace. Non-static members require an instance of the class or structure to be accessed.

//Classes
class OMEGA
{
	protected:
	// Member variables
	int value;

	public:
	// Member functions

	// Constructor
	OMEGA()
	{
		value = 0;
	}
};

class A : virtual public OMEGA
{
	public:
	// Member functions

	// Constructor
	A()
	{
		value = 1;
	}

	// Get value
	int get_value()
	{
		return value;
	}

	// Print message
	void print_message()
	{
		cout << "Class A function is called! " << endl;
	}
};

class B : virtual public OMEGA
{
	public:
	// Member functions

	B()
	{
		value = 2;
	}

	// Get value
	int get_value()
	{
		return value;
	}

	// Print message
	void print_message()
	{
		cout << "Class B function is called! " << endl;
	}
};

class AB : public A, public B
{
	public:
	// Member functions

	// Print message
	void print_message()
	{
		A::print_message(); // Call the function in the A base class
		B::print_message(); // Call the function in the B base class
		cout << "Class AB function is called! " << endl;

		cout << "The value of A is: " << A::get_value() << " ,if we just print the value: " << A::value << endl;
		cout << "The value of B is: " << B::get_value() << " ,if we just print the value: " << B::value << endl;
	}
	// If we don't use the scope resolution operator "::" the compiler will be confused to which function we are calling because we inherit the same function from two base classes.
	//
	// When we want only one copy of the variable to be inherited instead of two, in this example in A is 1, in B is 2.
	// We use the virtual inheritance method, and in the AB class the right most class value in this case the value in B is called.
	// If we want to get the value in A we just swap the order of inheritance of AB.
};

int main()
{
	AB object;

	object.print_message();

	return 0;
}