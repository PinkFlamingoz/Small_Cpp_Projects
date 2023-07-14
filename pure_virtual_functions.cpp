#include <iostream>
#include <math.h>
#include <vector>
#include "headers/basic_functions.h"
#include <algorithm>

using namespace std;
// A pure virtual function is a function (abstract function) a virtual function for which we don't have implementation we only declare it.
// It is declared by assigning 0, example: virtual void myfunction() = 0;
//
// A class that has at least one pure virtual function is called an abstract class.
// We can have pointers and references of abstract class types, but we cannot create an object of an abstract class type aka instantiate it.
// If we do not override the pure virtual function in the derived class then the derived class also becomes abstract.
//
// Types of inheritance
//
// Single level inheritance
// [ BASE CLASS ]
//       ▲
//		 |
// [CHILD CLASS]
//
// Multi level inheritance
// [ BASE CLASS ]
//       ▲
//		 |
// [CHILD CLASS 1]
//       ▲
//		 |
// [CHILD CLASS 2]
//
// Multiple inheritance
// [ BASE CLASS 1 ] [ BASE CLASS 2 ]
//              ▲     ▲
//		        |     |
//           [CHILD CLASS]
//
// Hierarchical inheritance
//             [      BASE CLASS     ]
//              ▲         ▲         ▲
//              |         |         |
//    [CHILD CLASS] [CHILD CLASS] [CHILD CLASS]
//
// Hybrid inheritance
//             [      BASE CLASS     ]
//              ▲         ▲         ▲
//              |         *         |
//    [CHILD CLASS]       *        [CHILD CLASS]
//              ▲         *         ▲
//		        |         *         |
//             [     CHILD CLASS     ]
//
// NOTE: The way we inherit a class the variables will change accordingly, and if we do a multi level inheritance this will apply as well, depending on how we inherited the call above!
// Also the constructors and destructors are not passed in inheritance.
//
// class BASE
// {
//	  private:
//	  int x;
//	  protected:
//    int y;
//	  public:
//    int z;
// }
//
// class public_derived: public base
// {
//	  int x; is private not accessible to this class
//    int y; is protected
//    int z; is public
// }
//
// class protected_derived: protected base
// {
//	  int x; is private not accessible to this class
//    int y; is protected
//    int z; is now protected
// }
//
// class private_derived: private base
// {
//	  int x; is private not accessible to this class
//    int y; is now private
//    int z; is now private
// }
//
// NOTE: Function Overloading is a feature where two ore more functions can have the same name, but must have different type of parameters or different number of parameters or different sequence of parameters.
// NOTE: Function Overriding is a feature where a derived class defines a function with the same name as in its base class but has a different code block.
// The function that will be called is the function in the derived class if called from the derived object.
// This is called polymorphism where something can have many forms.
// Compile time polymorphism: Function overloading, operator overloading, templates
// Run time polymorphism: Function overriding

// Globals
const double PI = 3.14159265358979323846;

// Classes
class Shape
{
	private:
	// Member variables
	static int count_shapes;
	// Static member variables are shared by all objects of the class.
	// All static data is initialized to zero when the program starts, before any objects are created, if no other initialization is present.
	// We cant put it in the class definition but it can be initialized outside the class using the scope resolution operator "::" to identify which class it belongs to.
	// When we declare a member of a class static it means no matter how many objects of the class are created, there is only one copy of the static member, all instances of the class share the same static member variable.

	protected:
	// Member variables
	double default_variable;
	string default_message_perimeter;
	string default_message_volume;
	string default_message_curvature;

	public:
	// Member functions

	// Constructor
	Shape()
	{
		default_variable = 1;
		default_message_perimeter = "This shape has no perimeter.\n";
		default_message_volume = "This shape has no volume.\n";
		default_message_curvature = "This shape has no curvature.\n";
		count_shapes++;
	}

	// Static function get counter
	static int get_count()
	{
		return count_shapes;
	}
	// By declaring a member function as static, we make it independent of any particular object of the class.
	// A static member function can be called even if no objects of the class exist and the static functions are accessed using only the class name and the scope resolution operator "::".
	// A static member function can only access static data members, other static member functions and any other functions from outside the class.
	// Static member functions have a class scope and they do not have access to the "this->" pointer of the class.
	// We can use this to determine wheaten some objects of the class have been created or not!

	// Area function!
	virtual double get_area() = 0;

	// Perimeter function!
	virtual double get_perimeter() = 0;

	// Volume function!
	virtual double get_volume() = 0;

	// Curvature function!
	virtual double get_curvature() = 0;

	// Print Area function!
	virtual void print_area(double area) = 0;

	// Print Perimeter function!
	virtual void print_perimeter(double perimeter) = 0;

	// Print Volume function!
	virtual void print_volume(double volume) = 0;

	// Print Curvature function!
	virtual void print_curvature(double curvature) = 0;
};

class Shape_2D : public Shape
{
	public:
	// Member functions

	// Override the virtual functions a 2D object that does not need
	double get_volume() override
	{
		return default_variable;
	}

	double get_curvature() override
	{
		return default_variable;
	}

	void print_volume(double volume) override
	{
		cout << default_message_volume;
	}

	void print_curvature(double curvature) override
	{
		cout << default_message_curvature;
	}
};

class Shape_2D_spherical : public Shape
{
	public:
	// Member functions

	// Override the virtual functions a 2D object that does not need
	double get_volume() override
	{
		return default_variable;
	}

	void print_volume(double volume) override
	{
		cout << default_message_volume;
	}
};

class Shape_3D : public Shape
{
	public:
	// Member functions

	// Override the virtual functions a 2D object that does not need
	double get_curvature() override
	{
		return default_variable;
	}

	void print_curvature(double curvature) override
	{
		cout << default_message_curvature;
	}
};

class Shape_3D_spherical : public Shape
{
	public:
	// Member functions

	// Override the virtual functions a 2D object that does not need
	double get_perimeter() override
	{
		return default_variable;
	}

	void print_perimeter(double curvature) override
	{
		cout << default_message_perimeter;
	}
};

class Rectangle : public Shape_2D
{
	private:
	// Member variables
	double length;
	double width;

	public:
	// Member functions

	// Constructor
	Rectangle()
	{
		length = get_valid_input<double>("Enter length of Rectangle: ");
		width = get_valid_input<double>("Enter width of Rectangle: ");
	}

	// Get the area of a Rectangle
	double get_area() override
	{
		return(length * width);
	}

	// Get the perimeter of a Rectangle
	double get_perimeter() override
	{
		return(2 * length + 2 * width);
	}

	// Print the area
	void print_area(double area) override
	{
		cout << "The area of a Rectangle is: " << area << endl;
	}

	// Print the perimeter
	void print_perimeter(double perimeter) override
	{
		cout << "The perimeter of a Rectangle is: " << perimeter << endl;
	}
};

class Triangle : public Shape_2D
{
	private:
	// Member variables
	double base;
	double height;
	double side_a;
	double side_b;
	double side_c;

	public:
	// Member functions

	// Constructor
	Triangle()
	{
		base = get_valid_input<double>("Enter base of Triangle: ");
		height = get_valid_input<double>("Enter height of Triangle: ");
		side_a = get_valid_input<double>("Enter side_a of Triangle: ");
		side_b = get_valid_input<double>("Enter side_b of Triangle: ");
		side_c = get_valid_input<double>("Enter side_c of Triangle: ");
	}

	// Get the area of a Triangle
	double get_area() override
	{
		return((base * height) / 2);
	}

	// Get the perimeter of a Triangle
	double get_perimeter() override
	{
		return(side_a + side_b + side_c);
	}

	// Print the area
	void print_area(double area) override
	{
		cout << "The area of a Triangle is: " << area << endl;
	}

	// Print the perimeter
	void print_perimeter(double perimeter) override
	{
		cout << "The perimeter of a Triangle is: " << perimeter << endl;
	}
};

class Circle : public Shape_2D_spherical
{
	private:
	// Member variables
	double radius;

	public:
	// Member functions

	// Constructor
	Circle()
	{
		radius = get_valid_input<double>("Enter radius of Circle: ");
	}

	// Get the area of a Circle
	double get_area() override
	{
		return(PI * pow(radius, 2));
	}

	// Get the perimeter of a Circle
	double get_perimeter() override
	{
		return(2 * PI * radius);
	}

	// Get the curvature of a Circle
	double get_curvature() override
	{
		return((2 * PI * radius) / (2 * PI));
	}

	// Print the area
	void print_area(double area) override
	{
		cout << "The area of a Circle is: " << area << endl;
	}

	// Print the perimeter
	void print_perimeter(double perimeter) override
	{
		cout << "The perimeter of a Circle is: " << perimeter << endl;
	}

	// Print the curvature
	void print_curvature(double curvature) override
	{
		cout << "The curvature of a Circle is: " << curvature << endl;
	}
};

class Square : public Shape_2D
{
	private:
	// Member variables
	double side_a;

	public:
	// Member functions

	// Constructor
	Square()
	{
		side_a = get_valid_input<double>("Enter side of Square: ");
	}

	// Get the area of a Square
	double get_area() override
	{
		return(pow(side_a, 2));
	}

	// Get the perimeter of a Square
	double get_perimeter() override
	{
		return(4 * side_a);
	}

	// Print the area
	void print_area(double area) override
	{
		cout << "The area of a Square is: " << area << endl;
	}

	// Print the perimeter
	void print_perimeter(double perimeter) override
	{
		cout << "The perimeter of a Square is: " << perimeter << endl;
	}
};

class Cube : public Shape_3D
{
	private:
	// Member variables
	double side_a;

	public:
	// Member functions

	// Constructor
	Cube()
	{
		side_a = get_valid_input<double>("Enter side of Cube: ");
	}

	// Get the area of a Cube
	double get_area() override
	{
		return(6 * pow(side_a, 2));
	}

	// Get the perimeter of a Cube
	double get_perimeter() override
	{
		return(12 * side_a);
	}

	// Get the volume of a Cube
	double get_volume() override
	{
		return(pow(side_a, 3));
	}

	// Print the area
	void print_area(double area) override
	{
		cout << "The surface area of a Cube is: " << area << endl;
	}

	// Print the perimeter
	void print_perimeter(double perimeter) override
	{
		cout << "The perimeter of a Cube is: " << perimeter << endl;
	}

	// Print the volume
	void print_volume(double volume) override
	{
		cout << "The volume of a Cube is: " << volume << endl;
	}
};

class Sphere : public Shape_3D_spherical
{
	private:
	// Member variables
	double radius;

	public:
	// Member functions

	// Constructor
	Sphere()
	{
		radius = get_valid_input<double>("Enter radius of Sphere: ");
	}

	// Get the area of a Sphere
	double get_area() override
	{
		return(4 * PI * pow(radius, 2));
	}

	// Get the volume of a Sphere
	double get_volume() override
	{
		return((static_cast<double>(4) / static_cast<double>(3)) * PI * pow(radius, 3));
	}

	// Get the curvature of a Sphere
	double get_curvature() override
	{
		return(1 / radius);
	}

	// Print the area
	void print_area(double area) override
	{
		cout << "The surface area of a Sphere is: " << area << endl;
	}

	// Print the volume
	void print_volume(double volume) override
	{
		cout << "The volume of a Sphere is: " << volume << endl;
	}

	// Print the curvature
	void print_curvature(double curvature) override
	{
		cout << "The curvature of a Sphere is: " << curvature << endl;
	}
};

class Cylinder : public Shape_3D
{
	private:
	// Member variables
	double radius;
	double height;

	public:
	// Member functions

	// Constructor
	Cylinder()
	{
		radius = get_valid_input<double>("Enter radius of Cylinder: ");
		height = get_valid_input<double>("Enter height of Cylinder: ");
	}

	// Get the area of a Cylinder
	double get_area() override
	{
		return((2 * PI * radius * height) + (2 * PI * pow(radius, 2)));
	}

	// Get the volume of a Cylinder
	double get_volume() override
	{
		return(PI * pow(radius, 2) * height);
	}

	// Get the perimeter of a Cylinder
	double get_perimeter() override
	{
		return(2 * PI * radius * height);
	}

	// Print the area
	void print_area(double area) override
	{
		cout << "The surface area of a Cylinder is: " << area << endl;
	}

	// Print the volume
	void print_volume(double volume) override
	{
		cout << "The volume of a Cylinder is: " << volume << endl;
	}

	// Print the perimeter
	void print_perimeter(double perimeter) override
	{
		cout << "The perimeter of a Cylinder is: " << perimeter << endl;
	}
};

class Cone : public Shape_3D_spherical
{
	private:
	// Member variables
	double radius;
	double height;

	public:
	// Member functions

	// Constructor
	Cone()
	{
		radius = get_valid_input<double>("Enter radius of Cone: ");
		height = get_valid_input<double>("Enter height of Cone: ");
	}

	// Get the area of a Cone
	double get_area() override
	{
		return((PI * pow(radius, 2)) + (PI * radius * sqrt(pow(radius, 2) + pow(height, 2))));
	}

	// Get the volume of a Cone
	double get_volume() override
	{
		return((static_cast<double>(1) / static_cast<double>(3)) * PI * pow(radius, 2) * height);
	}

	// Get the curvature of a Cone
	double get_curvature() override
	{
		double slant_height = sqrt(pow(radius, 2) + pow(height, 2));
		double radius_of_curvature = pow(radius, 2) / slant_height;
		return(1 / radius_of_curvature);
	}

	// Print the area
	void print_area(double area) override
	{
		cout << "The surface area of a Cone is: " << area << endl;
	}

	// Print the volume
	void print_volume(double volume) override
	{
		cout << "The volume of a Cone is: " << volume << endl;
	}

	// Print the curvature
	void print_curvature(double curvature) override
	{
		cout << "The curvature of a Cone is: " << curvature << endl;
	}
};

class Ellipse : public Shape_3D_spherical
{
	private:
	// Member variables
	double side_a;
	double side_b;

	public:
	// Member functions

	// Constructor
	Ellipse()
	{
		side_a = get_valid_input<double>("Enter side_a of Ellipse: ");
		side_b = get_valid_input<double>("Enter side_b of Ellipse: ");
	}

	// Get the curvature of a Ellipse
	double get_curvature() override
	{
		return(2 * PI * sqrt((side_a * side_a + side_b * side_b) / 2) / (side_a + side_b));
	}

	// Get the area of a Ellipse
	double get_area() override
	{
		return(PI * side_a * side_b);
	}

	// Get the volume of a Ellipse
	double get_volume() override
	{
		return((static_cast<double>(4) / static_cast<double>(3)) * PI * pow(side_b, 2) * side_a);
	}

	// Print the curvature
	void print_curvature(double curvature) override
	{
		cout << "The curvature of a Ellipse is: " << curvature << endl;
	}

	// Print the area
	void print_area(double area) override
	{
		cout << "The surface area of a Ellipse is: " << area << endl;
	}

	// Print the volume
	void print_volume(double volume) override
	{
		cout << "The volume of a Ellipse is: " << volume << endl;
	}
};

// Initialize static member variables
int Shape::count_shapes = 0;

//Functions
string select_option();

template <typename T>
void calculator(Shape *shape, string choice);

int main()
{
	// Shape::print_area(Shape::get_area()); -------------- This is not allowed because its not a static member function
	// Rectangle::print_area(Rectangle::get_area()); ------ This is not allowed because its not a static member function
	Shape::get_count(); //--------------------------------- This is allowed because the function is a static member function

	bool done = false; //---------------------------------- Create a loop variable, set it to false when we are done and exit the program

	while (!done) //--------------------------------------- Begin the program
	{
		string choice = select_option(); //---------------- Get from the user the choice of what he wants to do

		Shape *shape = nullptr; //------------------------- Make a pointer of a shape class

		switch (choice[0]) //------------------------------ Based on what the user wants do the correct thing
		{
			case 'r':
				calculator<Rectangle>(shape, choice); //--- Calculate Rectangle functions
				break;
			case 't':
				calculator<Triangle>(shape, choice); //---- Calculate Triangle functions
				break;
			case 'c':
				if (choice == "circle")
				{
					calculator<Circle>(shape, choice); //-- Calculate Circle functions
				}
				else if (choice == "cube")
				{
					calculator<Cube>(shape, choice); //---- Calculate Cube functions
				}
				else if (choice == "cylinder")
				{
					calculator<Cylinder>(shape, choice); // Calculate Cylinder functions
				}
				else
				{
					calculator<Cone>(shape, choice); //---- Calculate Cone functions
				}
				break;
			case 's':
				if (choice == "square")
				{
					calculator<Square>(shape, choice); //-- Calculate Square functions
				}
				else
				{
					calculator<Sphere>(shape, choice); //-- Calculate Sphere functions
				}
				break;
			case 'e':
				calculator<Ellipse>(shape, choice); //----- Calculate Ellipse functions
				break;
			case'd':
				done = true; //---------------------------- Change the loop variable to true
				break;
			default:
				cout << endl << "Try again! " << endl;
				break;
		}
	}

	return 0; //------------------------------------------- Success
}

// Select what to calculate, prompt the user until he enters the string thats in the vector choices array
string select_option()
{
	vector<string> choices = { "rectangle", "triangle", "circle", "square", "cube", "sphere", "cylinder", "cone", "ellipse", "done" };

	cout << endl << "Enter: Rectangle, Triangle, Circle, Square, Cube, Sphere, Cylinder, Cone, Ellipse. " << endl << "Enter Done when you are done!" << endl;

	string choice = "";

	do
	{
		choice = get_valid_input<string>("What do you want to calculate: ");
		transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
	} while (find(choices.begin(), choices.end(), choice) == choices.end());

	return choice;
}

// Do the calculations while accessing the functions through the shape pointer
// With this we don't repeat the same functions calls for all the objects we want to create.
template <typename T>
void calculator(Shape *shape, string choice)
{
	T shape_object{};

	shape = &shape_object;

	cout << endl << "*~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~* " << choice << " * ~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~*" << endl;

	double area = shape->get_area();
	shape->print_area(area);

	double perimeter = shape->get_perimeter();
	shape->print_perimeter(perimeter);

	double volume = shape->get_volume();
	shape->print_volume(volume);

	double curvature = shape->get_curvature();
	shape->print_curvature(curvature);

	cout << "Total shapes created: " << Shape::get_count() << "!" << endl;
}