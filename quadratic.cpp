#include <iostream>
#include "basic_functions.h"
#include <math.h>

using namespace std;

// Classes
class Quadratic_EQ
{
	private:
	//Member variables
	float a;
	float b;
	float c;
	public:
	// Member functions

	//Constructor
	Quadratic_EQ()
	{
		a = 0;
		b = 0;
		c = 0;
	}

	// Parameter constructor
	Quadratic_EQ(float a, float b, float c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}

	// Member functions
	void set();
	void print() const;
	void roots() const;

	friend Quadratic_EQ double_quadratic(Quadratic_EQ t);
};

// Functions

// Set the coefficients of the quadratic
void Quadratic_EQ::set()
{
	a = get_valid_input<float>("Enter coefficient a: ");
	b = get_valid_input<float>("Enter coefficient b: ");
	c = get_valid_input<float>("Enter coefficient c: ");
}

// Print the quadratic equation
void Quadratic_EQ::print() const
{
	if (a != 0) cout << a << "*x^2";
	if (b > 0) cout << "+" << b << "*x";
	if (b < 0) cout << b << "*x";
	if (c > 0) cout << "+" << c;
	if (c < 0) cout << c;
	cout << "=0" << endl;
}

// Calculate the roots of the quadratic
void Quadratic_EQ::roots() const
{
	float D;
	D = b * b - 4 * a * c;
	if (D > 0)
	{
		cout << "x1=" << -b + sqrt(D) / (2 * a) << endl;
		cout << "x2=" << -b - sqrt(D) / (2 * a) << endl;
	}
	else if (D == 0)
	{
		cout << "x=" << -b / (2 * a) << endl;
	}
	else
	{
		cout << "x1=" << -b / (2 * a) << "+i*(" << sqrt(abs(D)) / (2 * a) << ")\n";
		cout << "x2=" << -b / (2 * a) << "-i*(" << sqrt(abs(D)) / (2 * a) << ")\n";
	}
}

// Make the quadratic double
Quadratic_EQ double_quadratic(Quadratic_EQ t)
{
	Quadratic_EQ temp;
	temp.a = t.a * 2;
	temp.b = t.b * 2;
	temp.c = t.c * 2;
	return temp;
}

int main()
{
	Quadratic_EQ quadratic;
	Quadratic_EQ *ptr = &quadratic;

	ptr->set();
	ptr->print();
	ptr->roots();

	void (Quadratic_EQ:: * ptr_to_function) (); //--------- void (Quadratic_EQ::* ptr_to_function) (); defines a pointer to a member function of the Quadratic_EQ class that takes no arguments and returns void.
	void (Quadratic_EQ:: * ptr_to_function_const) () const;

	ptr_to_function = &Quadratic_EQ::set; //--------------- ptr_to_function = &Quadratic_EQ::set; sets the pointer to the member function set of the Quadratic_EQ class.
	(quadratic.*ptr_to_function)(); //--------------------- (quadratic.*ptr_to_function)(); calls the set member function on an instance of the Quadratic_EQ class named quadratic. The .* operator is used to call a member function through a pointer to that function.

	ptr_to_function_const = &Quadratic_EQ::print; //------- ptr_to_function_const = &Quadratic_EQ::print; sets the pointer to the member function print of the Quadratic_EQ class.
	(quadratic.*ptr_to_function_const)(); //--------------- (quadratic.*ptr_to_function_const)(); calls the print member function on the quadratic instance of the Quadratic_EQ class.

	ptr_to_function_const = &Quadratic_EQ::roots; //------- ptr_to_function_const = &Quadratic_EQ::roots; sets the pointer to the member function roots of the Quadratic_EQ class.
	(quadratic.*ptr_to_function_const)(); //--------------- (quadratic.*ptr_to_function_const)(); calls the roots member function on the quadratic instance of the Quadratic_EQ class.

	Quadratic_EQ new_quadratic;
	new_quadratic.set();
	new_quadratic = double_quadratic(quadratic);
	new_quadratic.print();
	new_quadratic.roots();

	return 0;
}