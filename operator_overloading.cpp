#include <iostream>
#include <math.h>
#include <unordered_map>
#include "headers/basic_functions.h"

using namespace std;
// NOTE: We can specify more than one definition for an operator in the same scope, which is called operator overloading.
// Its a type of polymorphism in which an operator is overloaded to give user defined meaning to it.
// Operators that cant be overloaded:
// scope operator ::
// size of
// member selector .
// member pointer selector *
// ternary operator ?:

// Classes
class Complex
{
	private:
	// Member variables
	double real;
	double imaginary;
	static int counter;

	public:
	// Member functions

	// Constructor
	Complex()
	{
		real = 0;
		imaginary = 0;
	}

	// Parameter constructor
	Complex(double real, double imaginary)
	{
		this->real = real;
		this->imaginary = imaginary;
	}

	// Static function get counter
	static int get_count()
	{
		return counter;
	}

	// Static function increment counter
	static int increment_counter()
	{
		return counter++;
	}

	// Display the number
	void display_number() const
	{
		cout << "Complex number: " << real << " , " << imaginary << "i" << endl;
	}

	// NOTE:We use const and pass by reference to improve the efficiency of our code and to ensure that we don't accidentally modify values that should not be modified.
	// Using const in a function declaration tells the compiler that the function will not modify any of the arguments passed to it.
	// This allows the compiler to optimize the code, since it can make certain assumptions about how the arguments are used.
	// For example, if a function takes a large object as an argument but doesn't modify it, passing the object by const reference instead of by value can be much faster, since it avoids making a copy of the object.
	//
	// The first const keyword after the function parameter list (const Complex &number) indicates that the function will not modify the number object passed in as an argument.
	// This is important because the operator+ overload is meant to perform a mathematical operation on two Complex objects without changing either of them.
	// The second const keyword after the function declaration indicates that the operator+ function is itself a const member function of the Complex class.
	// This means that the function can be called on a const object of the Complex class, and it will not modify the state of that object.
	// In other words, the const keyword in this position ensures that calling the operator+ function on a const Complex object will not modify the state of that object.
	// A const member function of a class can be called on both const and non-const objects of that class.

	// Addition
	Complex operator+(const Complex &number) const
	{
		Complex temp;
		temp.real = real + number.real;
		temp.imaginary = imaginary + number.imaginary;
		return temp;
	}

	// Subtraction
	Complex operator-(const Complex &number) const
	{
		Complex temp;
		temp.real = real - number.real;
		temp.imaginary = imaginary - number.imaginary;
		return temp;
	}

	// Multiplication
	Complex operator*(const Complex &number) const
	{
		Complex temp;
		temp.real = real * number.real - imaginary * number.imaginary;
		temp.imaginary = real * number.imaginary + imaginary * number.real;
		return temp;
	}

	// Division
	Complex operator/(const Complex &number) const
	{
		Complex temp;
		double denominator = number.real * number.real + number.imaginary * number.imaginary;
		temp.real = (real * number.real + imaginary * number.imaginary) / denominator;
		temp.imaginary = (imaginary * number.real - real * number.imaginary) / denominator;
		return temp;
	}

	// Mod
	Complex operator%(double modulus) const
	{
		Complex temp;
		temp.real = fmod(real, modulus);
		temp.imaginary = fmod(imaginary, modulus);
		return temp;
	}

	// NOTE: The operator= function returns a reference to the current Complex object, which is pointed to by the "this" pointer.
	// This allows for chaining of the assignment operator.
	// The "&" symbol before the operator= keyword indicates that the function returns a reference to a Complex object.
	// This is important because it allows for chaining of assignment operations, such as a = b = c, where a, b, and c are all Complex objects.

	// Assignment
	Complex &operator=(const Complex &number)
	{
		real = number.real;
		imaginary = number.imaginary;
		return *this;
	}

	// Addition Single
	Complex &operator+=(const Complex &number)
	{
		real = real + number.real;
		imaginary = imaginary + number.imaginary;
		return *this;
	}

	// Subtraction Single
	Complex &operator-=(const Complex &number)
	{
		real = real - number.real;
		imaginary = imaginary - number.imaginary;
		return *this;
	}

	// Multiplication Single
	Complex &operator*=(const Complex &number)
	{
		double temp_real = real;
		real = real * number.real - imaginary * number.imaginary;
		imaginary = temp_real * number.imaginary + imaginary * number.real;
		return *this;
	}

	// Division Single
	Complex &operator/=(const Complex &number)
	{
		double denominator = number.real * number.real + number.imaginary * number.imaginary;
		double temp_real = real;
		real = (real * number.real + imaginary * number.imaginary) / denominator;
		imaginary = (imaginary * number.real - temp_real * number.imaginary) / denominator;
		return *this;
	}

	// Mod Single
	Complex &operator%=(double modulus)
	{
		real = fmod(real, modulus);
		imaginary = fmod(imaginary, modulus);
		return *this;
	}

	// Compare
	bool operator==(const Complex &number) const
	{
		return (real == number.real) && (imaginary == number.imaginary);
	}

	// Compare NOT
	bool operator!=(const Complex &number) const
	{
		return (real != number.real) || (imaginary != number.imaginary);
	}

	// Greater than
	bool operator>(const Complex &number) const
	{
		return (real > number.real) || (real == number.real && imaginary > number.imaginary);
	}

	// Greater or equal than
	bool operator>=(const Complex &number) const
	{
		return (real >= number.real) && (imaginary >= number.imaginary);
	}

	// Less than
	bool operator<(const Complex &number) const
	{
		return (real < number.real) || (real == number.real && imaginary < number.imaginary);
	}

	// Less or equal than
	bool operator<=(const Complex &number) const
	{
		return (real <= number.real) && (imaginary <= number.imaginary);
	}

	// NOT
	bool operator!() const
	{
		return (real == 0) && (imaginary == 0);
	}

	// Print
	friend ostream &operator<<(ostream &os, const Complex &number)
	{
		os << number.real << " , " << number.imaginary << "i";
		return os;
	}
	// The << operator has been overloaded to print a Complex object to the output stream.
	// The overloaded << operator takes two arguments: an ostream object (e.g. cout) and a const Complex & object to be printed.
	// It returns the ostream object to enable chaining. In this function, the real and imaginary parts of the complex number are printed to the output stream using the << operator.

	// Insert
	friend istream &operator>>(istream &is, Complex &number)
	{
		is >> number.real >> number.imaginary;
		return is;
	}
	// The >> operator has been overloaded to read in a Complex object from the input stream.
	// The overloaded >> operator takes two arguments : an istream object(e.g.cin) and a Complex &object to be filled with the input.
	// It returns the istream object to enable chaining.In this function, the real and imaginary parts of the complex number are read from the input stream using the >> operator.

	// Pre increment, where we increment the value first then apply operations
	// Example: x = 0; y = ++x; y here will have 1;
	Complex &operator ++()
	{
		++real;
		++imaginary;
		return *this;
	}

	// Post increment, where we increment the value after the operations
	// Example: x = 0; y = x++; y here will have 0;
	Complex &operator ++(int)
	{
		real++;
		imaginary++;
		return *this;
	}

	// Pre decrement, where we decrement the value first then apply operations
	// Example: x = 0; y = --x; y here will have -1;
	Complex &operator --()
	{
		--real;
		--imaginary;
		return *this;
	}

	// Post decrement, where we decrement the value after the operations
	// Example: x = 0; y = x-- y here will have 0;
	Complex &operator --(int)
	{
		real--;
		imaginary--;
		return *this;
	}

	// Add function
	static Complex add(const Complex &a, const Complex &b)
	{
		return a + b;
	}

	// Sub function
	static Complex sub(const Complex &a, const Complex &b)
	{
		return a - b;
	}

	// Multiply function
	static Complex multiply(const Complex &a, const Complex &b)
	{
		return a * b;
	}

	// Divide function
	static Complex divide(const Complex &a, const Complex &b)
	{
		return a / b;
	}

	// Mod function
	static Complex mod(const Complex &a, double b)
	{
		return a % b;
	}

	// Assign function
	static Complex assign(Complex &a, const Complex &b)
	{
		return a = b;
	}

	// Add and assign function
	static Complex add_assign(Complex &a, const Complex &b)
	{
		return a += b;
	}

	// Sub and assign function
	static Complex sub_assign(Complex &a, const Complex &b)
	{
		return a -= b;
	}

	// Multiply and assign function
	static Complex multiply_assign(Complex &a, const Complex &b)
	{
		return a *= b;
	}

	// Divide and assign function
	static Complex divide_assign(Complex &a, const Complex &b)
	{
		return a /= b;
	}

	// Mod and assign function
	static Complex mod_assign(Complex &a, double b)
	{
		return a %= b;
	}

	// Compare two complex numbers function
	static bool compare(const Complex &a, const Complex &b)
	{
		if (a == b)
		{
			cout << a << " is equal to " << b << endl;
			return true;
		}
		else
		{
			cout << a << " is not equal to " << b << endl;
			return false;
		}
	}

	// Compare if they are not equal function
	static bool compare_NOT(const Complex &a, const Complex &b)
	{
		if (a != b)
		{
			cout << a << " is not equal to " << b << endl;
			return true;
		}
		else
		{
			cout << a << " is equal than " << b << endl;
			return false;
		}
	}

	// Greater than function
	static bool compare_greater(const Complex &a, const Complex &b)
	{
		if (a > b)
		{
			cout << a << " is greater than " << b << endl;
			return true;
		}
		else
		{
			cout << a << " is not greater than " << b << endl;
			return false;
		}
	}

	// Greater than or equal function
	static bool compare_greater_or_equal(const Complex &a, const Complex &b)
	{
		if (a >= b)
		{
			cout << a << " is greater or equal to " << b << endl;
			return true;
		}
		else
		{
			cout << a << " is not greater or equal than " << b << endl;
			return false;
		}
	}

	// Less than function
	static bool compare_less(const Complex &a, const Complex &b)
	{
		if (a < b)
		{
			cout << a << " is less than " << b << endl;
			return true;
		}
		else
		{
			cout << a << " is not less than " << b << endl;
			return false;
		}
	}

	// Less than or equal function
	static bool compare_less_or_equal(const Complex &a, const Complex &b)
	{
		if (a <= b)
		{
			cout << a << " is less or equal to " << b << endl;
			return true;
		}
		else
		{
			cout << a << " is not less or equal than " << b << endl;
			return false;
		}
	}

	// Function to tell if the complex number is 0
	static bool NOT(const Complex &n)
	{
		if (!n)
		{
			cout << n << " is 0" << endl;
			return true;
		}
		else
		{
			cout << n << " is not 0" << endl;
			return false;
		}
	}

	// Pre increment function
	static Complex pre_increment(Complex &n)
	{
		return ++n;
	}

	// Post increment function
	static Complex post_increment(Complex &n)
	{
		return n++;
	}

	// Pre decrement function
	static Complex pre_decrement(Complex &n)
	{
		return --n;
	}

	// Pre decrement function
	static Complex post_decrement(Complex &n)
	{
		return n--;
	}
};

// Globals
unordered_map<string, Complex> c_numbers;
Complex temp(0, 0);

// Initialize static member variables
int Complex::counter = 0;

// Functions
void create_complex_number();
void delete_complex_number();
Complex &select_from_hash_table();
void print_menu();
int get_choice();
void print_created_complex_numbers();
int get_choice_for_temp();
void add_or_clear_temp(Complex n);
void clear_temp();
void print_result(Complex n);
bool check_if_empty_hash_table();

int main()
{
	bool done = false;
	while (!done)
	{
		print_menu();
		int choice = get_choice();
		switch (choice)
		{
			case 1:
				create_complex_number();
				break;
			case 2:
				if (check_if_empty_hash_table())
				{
					break;
				}
				delete_complex_number();
				break;
			case 3:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Complex::add(select_from_hash_table(), select_from_hash_table()));
				break;
			case 4:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Complex::sub(select_from_hash_table(), select_from_hash_table()));
				break;
			case 5:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Complex::multiply(select_from_hash_table(), select_from_hash_table()));
				break;
			case 6:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Complex::divide(select_from_hash_table(), select_from_hash_table()));
				break;
			case 7:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Complex::mod(select_from_hash_table(), get_valid_input<double>("Enter Mod: ")));
				break;
			case 8:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Complex::assign(select_from_hash_table(), select_from_hash_table()));
				break;
			case 9:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Complex::add_assign(select_from_hash_table(), select_from_hash_table()));
				break;
			case 10:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Complex::sub_assign(select_from_hash_table(), select_from_hash_table()));
				break;
			case 11:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Complex::multiply_assign(select_from_hash_table(), select_from_hash_table()));
				break;
			case 12:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Complex::divide_assign(select_from_hash_table(), select_from_hash_table()));
				break;
			case 13:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Complex::mod_assign(select_from_hash_table(), get_valid_input<double>("Enter Mod: ")));
				break;
			case 14:
				if (check_if_empty_hash_table())
				{
					break;
				}
				Complex::compare(select_from_hash_table(), select_from_hash_table());
				break;
			case 15:
				if (check_if_empty_hash_table())
				{
					break;
				}
				Complex::compare_NOT(select_from_hash_table(), select_from_hash_table());
				break;
			case 16:
				if (check_if_empty_hash_table())
				{
					break;
				}
				Complex::compare_greater(select_from_hash_table(), select_from_hash_table());
				break;
			case 17:
				if (check_if_empty_hash_table())
				{
					break;
				}
				Complex::compare_greater_or_equal(select_from_hash_table(), select_from_hash_table());
				break;
			case 18:
				if (check_if_empty_hash_table())
				{
					break;
				}
				Complex::compare_less(select_from_hash_table(), select_from_hash_table());
				break;
			case 19:
				if (check_if_empty_hash_table())
				{
					break;
				}
				Complex::compare_less_or_equal(select_from_hash_table(), select_from_hash_table());
				break;
			case 20:
				if (check_if_empty_hash_table())
				{
					break;
				}
				Complex::NOT(select_from_hash_table());
				break;
			case 21:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Complex::pre_increment(select_from_hash_table()));
				break;
			case 22:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Complex::post_increment(select_from_hash_table()));
				break;
			case 23:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Complex::pre_decrement(select_from_hash_table()));
				break;
			case 24:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Complex::post_decrement(select_from_hash_table()));
				break;
			case 25:
				clear_temp();
				break;
			case 26:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_created_complex_numbers();
				break;
			case 27:
				system("cls");
				break;
			case 28:
				done = true;
				break;
			default:
				cout << "Try again!" << endl;
				break;
		}
		cout << "\n\t\t"; system("pause"); // or cin.get(); // For a pause every new operation
	}

	return 0;
}

// Create a complex number with increasing name, we will store them in a hash table, with the key being their name, and the value will be the actual complex number
void create_complex_number()
{
	string name = "c" + to_string(Complex::get_count()); //------------------------------------------------------- Get the name of the complex number

	Complex c(get_valid_input<double>("Enter real part: "), get_valid_input<double>("Enter imaginary part: ")); // Crate the complex number

	c_numbers[name] = c; //--------------------------------------------------------------------------------------- Add the complex number with the key name and the created complex number

	cout << "Complex number " << name << " has been created!" << endl;

	Complex::increment_counter(); //------------------------------------------------------------------------------ Increment the object counter so we increase the value of the next complex number name

	print_created_complex_numbers();
}

// Delete a complex number in the hash table
void delete_complex_number()
{
	string name = get_valid_input<string>("Enter the name of the complex number you want to delete: "); // Get the name we want to delete

	auto it = c_numbers.find(name); //-------------------------------------------------------------------- Get the name we want to find
	if (it != c_numbers.end())
	{
		c_numbers.erase(it); //--------------------------------------------------------------------------- Delete it
		cout << "Complex number " << name << " deleted." << endl;
		print_created_complex_numbers();
	}
	else
	{
		cerr << "Invalid complex number name: " + name << endl;
		return;
	}
}

// Select a complex number from the hash table
Complex &select_from_hash_table()
{
	string name = get_valid_input<string>("Select a complex number: ");

	auto it = c_numbers.find(name); //--------------------------------- Get the key aka name
	if (it != c_numbers.end())
	{
		return it->second; //------------------------------------------ Return a reference to the value in the map
	}
	else
	{
		cerr << "Invalid complex number name: " + name << endl;
		static Complex dummy; //--------------------------------------- Return a static dummy Complex object as a reference
		return dummy;
	}
}
// NOTE: Returning a reference to an object means that the function will return a "pointer" to the actual object stored in memory, rather than making a copy of the object.
// This can be more efficient in terms of memory usage and performance, especially when dealing with large objects.
// In this case, the returned reference is qualified with the class name Complex, which means that the function will return a reference to an object of the Complex class.

// Print the menu options
void print_menu()
{
	cout << "Chose operations: " << endl;

	cout << "1. Create a complex number " << endl;
	cout << "2. Remove a complex number " << endl;

	cout << "3. Add                    ,operator: (+) " << endl;
	cout << "4. Subtract               ,operator: (-) " << endl;
	cout << "5. Multiply               ,operator: (*) " << endl;
	cout << "6. Divide                 ,operator: (/) " << endl;
	cout << "7. Mod                    ,operator: (\%) " << endl;

	cout << "8. Assign                 ,operator: (=) " << endl;

	cout << "9. Add and Assign         ,operator: (+=) " << endl;
	cout << "10. Subtract and Assign   ,operator: (-=) " << endl;
	cout << "11. Multiply and Assign   ,operator: (*=) " << endl;
	cout << "12. Divide and Assign     ,operator: (/=) " << endl;
	cout << "13. Mod and Assign        ,operator: (\%=) " << endl;

	cout << "14. Compare               ,operator: (==)  " << endl;
	cout << "15. Compare NOT           ,operator: (!=) " << endl;
	cout << "16. Greater than          ,operator: (>) " << endl;
	cout << "17. Greater than or equal ,operator: (>=) " << endl;
	cout << "18. Less than             ,operator: (<)  " << endl;
	cout << "19. Less than or equal    ,operator: (<=) " << endl;
	cout << "20. NOT                   ,operator: (!) " << endl;

	cout << "21. Pre Increment         ,operator: (++n) " << endl;
	cout << "22. Post Increment        ,operator: (n++)  " << endl;
	cout << "23. Pre Decrement         ,operator: (--n) " << endl;
	cout << "24. Post Decrement        ,operator: (n--) " << endl;

	cout << "25. Clear temp " << endl;
	cout << "26. Print Complex Numbers " << endl;
	cout << "27. Clear screen " << endl;
	cout << "28. DONE " << endl;
}

// Get choice for the menu
int get_choice()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 1 || choice > 28);
	return choice;
}

// Pint the complex numbers we have created
void print_created_complex_numbers()
{
	for (auto &number : c_numbers)
	{
		cout << number.first << ": " << number.second << endl;
	}

	cout << "Temp: " << temp << endl;
}

// Get choice for the temp complex number
int get_choice_for_temp()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 1 || choice > 3);
	return choice;
}

// Options for the temp complex number
void add_or_clear_temp(Complex n)
{
	cout << "Add in temp? " << endl;
	cout << "1: ADD, 2: CLEAR, 3: SKIP" << endl;
	Complex new_temp(0, 0);
	int choice = get_choice_for_temp();
	switch (choice)
	{
		case 1:
			temp += n;
			break;
		case 2:
			temp = new_temp;
			break;
		case 3:
			cout << "SKIP" << endl;
			break;
	}

	cout << "Temp: " << temp << endl;
}

// Options for the temp complex number
void clear_temp()
{
	Complex new_temp(0, 0);
	temp = new_temp;
	cout << "Temp: " << temp << endl;
}

// Print the result and decide if we add that result to the temp complex number in doing this we create a a step by step calculator for bigger equations
void print_result(Complex n)
{
	cout << "Result: " << n << endl;
	add_or_clear_temp(n);
}

// Check if the hash table is empty
bool check_if_empty_hash_table()
{
	if (c_numbers.empty())
	{
		cerr << "Create a matrix first! " << endl;
		return true;
	}
	return false;
}