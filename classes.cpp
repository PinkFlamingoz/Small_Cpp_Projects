#include <iostream>
#include "headers/basic_functions.h"

using namespace std;
// NOTE: this-> is a special operator, "this" is a keyword that refers to a pointer to the current object.
// The "this" pointer is used to access the member variables and member functions of the current object.
// The -> operator is used to access members of an object pointed to by a pointer.
// When used together with this, it is used to access the members of the current object through the "this" pointer.
//
// Every object in C++ has access to its own address through an important pointer called "this" pointer.
// The "this" pointer is an implicit parameter to all member functions. Therefore, inside a member function, "this" may be used to refer to the invoking object.
// "this" pointer can also be used to return its own reference.
// Fiend functions do not have a "this" pointer, because friends are not members of a class. Only member functions have a "this" pointer.
// "this" pointer is not available in static member functions as static member functions can be called without any object(with class name).
// Following are the situations where 'this' pointer is used :
// When local variable's name is same as member's name.
// To return reference to the calling object.

// Classes
class Cars
{
	private:
	// Member variables or data members
	string company;
	string model;
	string fuel_type;
	float mileage;
	double price;

	protected:
	// Member variables or data members

	public:
	// Member functions they can be constructors, destructors, accessors, setters or mutators

	// Constructor
	// The constructor initializes objects of a class, it is automatically called when object(instance of a class) is created.
	// Its a special member function, it has the same name of the class, they don't have a return type, if we don't specify a constructor the compiler generates a default constructor for us(with no parameters and has an empty body).

	// Default Constructor does not take any arguments, it has no parameters.
	// Or we can use initialization lists in constructors
	// Cars() : company("Company"), model("Default Model"), fuel_type("Default Fuel Type"), mileage(0), price(0){ }
	Cars()
	{
		cout << "Default Constructor called!" << endl;
		company = "Default Company";
		model = "Default Model";
		fuel_type = "Default Fuel Type";
		mileage = 0;
		price = 0;
	}

	// Parameter Constructor takes arguments, so when we create the object we pass in the parameters
	//
	// NOTE: We can also do it like this
	// Cars(string company, string model, string fuel_type, float mileage, double price) : company(company), model(model), fuel_type(fuel_type), mileage(mileage), price(price){ }
	Cars(string company, string model, string fuel_type, float mileage, double price)
	{
		cout << "Parameter Constructor called!" << endl;
		this->company = company;
		this->model = model;
		this->fuel_type = fuel_type;
		this->mileage = mileage;
		this->price = price;
	}

	// Copy Constructor initializes an object using another object of the same class
	Cars(Cars &object)
	{
		cout << "Copy Constructor called!" << endl;
		company = object.company;
		model = object.model;
		fuel_type = object.fuel_type;
		mileage = object.mileage;
		price = object.price;
	}

	// Destructor (Deallocation of memory happens in the destructor, we have to write it manually)
	// The destructor is a special member function, it destructs or deletes an object.
	// It is called when the function ends, the program ends, a block containing local variables ends, a delete operator is called.
	// Destructors have the same name of the class  preceded by a tilde(~).
	// Destructors don't have any arguments and don't return anything not even void.
	// There can only be one destructor unlike the constructors.
	// If we do not write our own destructor in a class, the compiler creates a default destructor for us.
	// If we have dynamically allocated memory or pointer in a class, we have to write a destructor to release the memory before the class instance is destroyed, so we don't create a memory leak.
	~Cars()
	{
		cout << "Destructor called!" << endl;
	}

	// Set the data for a car from the user
	void set_data()
	{
		do
		{
			company = get_valid_input<string>("Enter Company of car: ");
			model = get_valid_input<string>("Enter mode of car: ");
			fuel_type = get_valid_input<string>("Enter fuel type of car: ");
			mileage = get_valid_input<float>("Enter mileage of car: ");
			price = get_valid_input<double>("Enter price of car: ");
		} while (company.empty() || model.empty() || fuel_type.empty() || mileage <= 0 || price <= 0);
	}
	//void set_data(string company, string model, string fuel_type, float mileage, double price)
	//{
	//	this->company = company;
	//	this->model = model;
	//	this->fuel_type = fuel_type;
	//	this->mileage = mileage;
	//	this->price = price;
	//}

	// Display the data of a car
	void display_data() const
	{
		cout << "Company name:  " << company << endl;
		cout << "Car model:     " << model << endl;
		cout << "Car fuel type: " << fuel_type << endl;
		cout << "Car mileage:   " << mileage << endl;
		cout << "Car price:     " << price << endl;
	}
};

// Functions
int get_size();
void set_data_for_cars(Cars cars[], int size);
void display_data_for_cars(Cars cars[], int size);

int main()
{
	//--------------------------------------------------- Objects are nothing but variables of type class
	Cars parameter_car("Honda", "42", "Water", 0, 99); // Create an object with the parameter constructor
	parameter_car.display_data(); //--------------------- Display that data

	Cars copy_car(parameter_car); //--------------------- Create an object with the copy constructor
	copy_car.display_data(); //-------------------------- Display that data

	int size = get_size(); //---------------------------- Get the size of the cars
	Cars *cars = new Cars[size]; //---------------------- Create an object with the set_data member function

	set_data_for_cars(cars, size); //-------------------- Set the data for each car
	display_data_for_cars(cars, size); //---------------- Display data for each car

	delete[] cars; //------------------------------------ Free up the allocated memory

	return 0; //----------------------------------------- Success
}

// Get the size for the cars class array
int get_size()
{
	int size = 0;
	do
	{
		size = get_valid_input<int>("Enter how many cars: ");
	} while (size < 1);
	return size;
}

// Set the data for each car
void set_data_for_cars(Cars cars[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "Enter data for car: " << i << endl;
		cars[i].set_data();
	}
}

// Display the data for each car
void display_data_for_cars(Cars cars[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "Data for car: " << i << endl;
		cars[i].display_data();
	}
}