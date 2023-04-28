// Storage Classes in C++ define the scope (visibility) and life-time of variables and/or functions within a C++ Program.
// Lifetime means the duration till which the variable remains active and visibility defines in which module of the program the variable is accessible.
// There are 5 types of Storage Classes in C++ :
// Automatic
// External
// Static
// Register
// Mutable
//
// Storage Class	Keyword	  Lifetime	      Visibility	Initial Value
// Automatic	    auto	  Function        Block	Local	Garbage
// External	        extern    Whole Program	  Global	    Zero
// Static	        static	  Whole Program	  Local	        Zero
// Register	        register  Function Block  Local	        Garbage
// Mutable	        mutable	  Class	          Local	        Garbage
//
//
//
//
//
//
//
// Automatic Storage Class
// Automatic storage class assigns a variable to its default storage type.
// auto keyword is used to declare automatic variables.
// However, if a variable is declared without any keyword inside a function, it is automatic by default.
// This variable is visible only within the function it is declared and its lifetime is same as the lifetime of the function as well.
// Once the execution of function is finished, the variable is destroyed.
// Example of Automatic Storage Class:
// auto int x;
// float y = 5.67;// auto by default
//
//
//
//
//
//
//
// External Storage Class
// External storage class assigns variable a reference to a global variable declared outside the given program.
// extern keyword is used to declare external variables.
// They are visible throughout the program and its lifetime is same as the lifetime of the program where it is declared.
// This visible to all the functions present in the program.
// Example of External Storage Class:
int test = 100; // assigning value to test
void multiply(int n)
{
	test = test * n;
}

#include<iostream>
// #include "sub.cpp" // includes the content of sub.cpp
using namespace std;

extern int test; // declaring test

int main()
{
	cout << test << endl;
	multiply(5);
	cout << test << endl;
	return 0;
}
// A variable test is declared as external in main.cpp.
// It is a global variable and it is assigned to 100 in sub.cpp.
// It can be accessed in both files.
// The function multiply() multiplies the value of test with the parameter passed to it while invoking it.
// The program performs the multiplication and changes the global variable test to 500.
// NOTE: Run the main.cpp program
// Output:
// 100
// 500
//
//
//
//
//
//
//
// Static Storage Class
// The static storage class instructs the compiler to keep a local variable in existence during the life - time of the program instead of creating and destroying it each time it comes into and goes out of scope.
// Therefore, making local variables static allows them to maintain their values between function calls.
// The static modifier may also be applied to global variables.
// When this is done, it causes that variable's scope to be restricted to the file in which it is declared.
// In C++, when static is used on a class data member, it causes only one copy of that member to be shared by all objects of its class.
// Example of Static Storage Class:
#include <iostream>

// Function declaration
void func(void);
static int count1 = 10; // Global variable

main()
{
	while (count1--)
	{
		func();
	}
	return 0;
}

// Function definition
void func(void)
{
	static int i = 5; // Local static variable
	i++;
	std::cout << "i is " << i;
	std::cout << " and count1 is " << count1 << std::endl;
}
// i is 6 and count is 9
// i is 7 and count is 8
// i is 8 and count is 7
// i is 9 and count is 6
// i is 10 and count is 5
// i is 11 and count is 4
// i is 12 and count is 3
// i is 13 and count is 2
// i is 14 and count is 1
// i is 15 and count is 0
//
//
//
//
//
//
//
// Register Storage Class
// Register storage assigns a variable's storage in the CPU registers rather than primary memory.
// It has its lifetime and visibility same as automatic variable.
// The purpose of creating register variable is to increase access speed and makes program run faster.
// If there is no space available in register, these variables are stored in main memory and act similar to variables of automatic storage class.
// So only those variables which requires fast access should be made register.
// For example:
// register int id;
// register char a;
//
//
//
//
//
//
//
// Mutable Storage Class
// In C++, a class object can be kept constant using keyword const.
// This doesn't allow the data members of the class object to be modified during program execution.
// But, there are cases when some data members of this constant object must be changed.
// Example of Mutable Storage Class:
#include<iostream>

using namespace std;

class test1
{
	mutable int a;
	int b;
	public:
	test1(int x, int y)
	{
		a = x;
		b = y;
	}
	void square_a() const
	{
		a = a * a;
	}
	void square_b() const
	{
		// b = b * b; error here
	}
	void display() const
	{
		cout << "a = " << a << endl;
		cout << "b = " << b << endl;
	}
};

int main()
{
	const test1 x(2, 3);
	cout << "Initial value" << endl;
	x.display();
	x.square_a();
	cout << "Final value" << endl;
	x.display();
	return 0;
}
// A class test is defined in the program.
// It consists of a mutable data member a.
// A constant object x of class test is created and the value of data members are initialized using user-defined constructor.
// Since, b is a normal data member, its value can't be changed after initialization.
// However a being mutable, its value can be changed which is done by invoking square_a() method.
// display() method is used to display the value the data members.
//
// Output
// Total Objects: 1
// Initial value
// a = 2
// b = 3
// Final value
// a = 4
// b = 3