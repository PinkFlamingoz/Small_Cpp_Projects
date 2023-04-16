#include <iostream>
#include "basic_functions.h"

using namespace std;
// NOTE: Virtual functions are member functions which are declared within the base class and are re-defined(overridden) by the derived class.
// When we refer to a derived class object using a pointer or a reference of the base class, we can call a virtual function for that object and execute the derived class version of the function.
// The resolving of function call is done at run time.
// They are declared with the key word virtual before the function.

// Classes
class Animal
{
	public:
	// Member functions

	// Eat function
	virtual void eat()
	{
		cout << "Eat!" << endl;
	}
};

class Cat : public Animal
{
	private:
	// Member variables
	string food;

	public:
	// Member functions
	Cat(string food)
	{
		this->food = food;
	}

	// Eat function
	void eat() override
	{
		cout << "Cat eats " << food << "!" << endl;
	}
};

class Dog : public Animal
{
	private:
	// Member variables
	string food;

	public:
	// Member functions
	Dog(string food)
	{
		this->food = food;
	}

	// Eat function
	void eat() override
	{
		cout << "Dog eats " << food << "!" << endl;
	}
};
// Functions
void print_eats(Animal *animal_pointer);

int main()
{
	Animal *animal_pointer = nullptr; //-------------------------------- Create an object pointer

	Cat cat_object(get_valid_input<string>("Enter food for cats: ")); // Create a derived class object
	Dog dog_object(get_valid_input<string>("Enter food for dogs: ")); // Create a derived class object

	animal_pointer = &cat_object; //------------------------------------ Set the pointer to point at the cat object
	print_eats(animal_pointer); //-------------------------------------- Call the function

	animal_pointer = &dog_object; //------------------------------------ Set the pointer to point at the dog object
	print_eats(animal_pointer); //-------------------------------------- Call the function

	return 0; //-------------------------------------------------------- Success
}

// Print function
void print_eats(Animal *animal_pointer)
{
	animal_pointer->eat(); // This will call the base case function eats if we don't make that function a virtual function!
}