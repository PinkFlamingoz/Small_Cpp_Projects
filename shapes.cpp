#include <iostream>
#include <math.h>
#include "basic_functions.h"

using namespace std;
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
// Hierarchial inheritance
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
// NOTE: Function Overloading is a feature where two ore more functions can have the same name, but must have different type of parameters or different number of parameters or different squence of parameters.
// NOTE: Function Overriding is a feature where a derived class defines a function with the same name as in its base class.
// The function that will be called is the function in the derived class if called from the derived object.

// Globals
const double PI = 3.14159265358979323846;

// Classes
class Shape
{
	private:
	// Member variables

	protected:
	// Member variables
	double width;
	double height;
	double length;
	double radius;
	double base;
	double side_a;
	double side_b;
	double side_c;

	public:
	// Member functions

	// Constructor
	Shape()
	{
		width = 0;
		height = 0;
		length = 0;
		radius = 0;
		base = 0;
		side_a = 0;
		side_b = 0;
		side_c = 0;
	}

	// Destructor
	~Shape()
	{
	}

	// Set width
	void set_width(int width)
	{
		this->width = width;
	}

	// Set height
	void set_height(int height)
	{
		this->height = height;
	}

	// Set length
	void set_length(int length)
	{
		this->length = length;
	}

	// Set height
	void set_radius(int radius)
	{
		this->radius = radius;
	}

	// Set base
	void set_base(int base)
	{
		this->base = base;
	}

	// Set side_a
	void set_side_a(int side_a)
	{
		this->side_a = side_a;
	}

	// Set side_b
	void set_side_b(int side_b)
	{
		this->side_b = side_b;
	}

	// Set height
	void set_side_c(int side_c)
	{
		this->side_c = side_c;
	}

	// Area function!
	double get_area()
	{
		cout << "Area function!" << endl;
		return 1;
	}

	// Perimeter function!
	double get_perimeter()
	{
		cout << "Perimeter function!" << endl;
		return 1;
	}

	// Volume function!
	double get_volume()
	{
		cout << "Volume function!" << endl;
		return 1;
	}

	// Curvature function!
	double get_curvature()
	{
		cout << "Curvature function!" << endl;
		return 1;
	}
};

class Rectangle : public Shape
{
	public:
	// Member functions

	// Get the area of a Rectangle
	double get_area()
	{
		return(length * width);
	}

	// Get the perimeter of a Rectangle
	double get_perimeter()
	{
		return(2 * length + 2 * width);
	}

	// Print the area
	void print_area(double area)
	{
		cout << "The area of a Rectangle is: " << area << endl;
	}

	// Print the perimeter
	void print_perimeter(double perimeter)
	{
		cout << "The perimeter of a Rectangle is: " << perimeter << endl;
	}
};

class Triangle : public Shape
{
	public:
	// Member functions

	// Get the area of a Triangle
	double get_area()
	{
		return((base * height) / 2);
	}

	// Get the perimeter of a Triangle
	double get_perimeter()
	{
		return(side_a + side_b + side_c);
	}

	// Print the area
	void print_area(double area)
	{
		cout << "The area of a Triangle is: " << area << endl;
	}

	// Print the perimeter
	void print_perimeter(double perimeter)
	{
		cout << "The perimeter of a Triangle is: " << perimeter << endl;
	}
};

class Circle : public Shape
{
	public:
	// Member functions

	// Get the area of a Circle
	double get_area()
	{
		return(PI * pow(radius, 2));
	}

	// Get the perimeter of a Circle
	double get_perimeter()
	{
		return(2 * PI * radius);
	}

	// Get the curvature of a Circle
	double get_curvature()
	{
		return((2 * PI * radius) / (2 * PI));
	}

	// Print the area
	void print_area(double area)
	{
		cout << "The area of a Circle is: " << area << endl;
	}

	// Print the perimeter
	void print_perimeter(double perimeter)
	{
		cout << "The perimeter of a Circle is: " << perimeter << endl;
	}

	// Print the curvature
	void print_curvature(double curvature)
	{
		cout << "The curvature of a Circle is: " << curvature << endl;
	}
};

class Square : public Shape
{
	public:
	// Member functions

	// Get the area of a Square
	double get_area()
	{
		return(pow(side_a, 2));
	}

	// Get the perimeter of a Square
	double get_perimeter()
	{
		return(4 * side_a);
	}

	// Print the area
	void print_area(double area)
	{
		cout << "The area of a Square is: " << area << endl;
	}

	// Print the perimeter
	void print_perimeter(double perimeter)
	{
		cout << "The perimeter of a Square is: " << perimeter << endl;
	}
};

class Cube : public Shape
{
	public:
	// Member functions

	// Get the area of a Cube
	double get_area()
	{
		return(6 * pow(side_a, 2));
	}

	// Get the perimeter of a Cube
	double get_perimeter()
	{
		return(12 * side_a);
	}

	// Get the volume of a Cube
	double get_volume()
	{
		return(pow(side_a, 3));
	}

	// Print the area
	void print_area(double area)
	{
		cout << "The surface area of a Cube is: " << area << endl;
	}

	// Print the perimeter
	void print_perimeter(double perimeter)
	{
		cout << "The perimeter of a Cube is: " << perimeter << endl;
	}

	// Print the volume
	void print_volume(double volume)
	{
		cout << "The volume of a Cube is: " << volume << endl;
	}
};

class Sphere : public Shape
{
	public:
	// Member functions

	// Get the area of a Sphere
	double get_area()
	{
		return(4 * PI * pow(radius, 2));
	}

	// Get the volume of a Sphere
	double get_volume()
	{
		return((static_cast<double>(4) / static_cast<double>(3)) * PI * pow(radius, 3));
	}

	// Print the area
	void print_area(double area)
	{
		cout << "The surface area of a Sphere is: " << area << endl;
	}

	// Print the volume
	void print_volume(double volume)
	{
		cout << "The volume of a Sphere is: " << volume << endl;
	}
};

class Cylinder : public Shape
{
	public:
	// Member functions

	// Get the area of a Cylinder
	double get_area()
	{
		return((2 * PI * radius * height) + (2 * PI * pow(radius, 2)));
	}

	// Get the volume of a Cylinder
	double get_volume()
	{
		return(PI * pow(radius, 2) * height);
	}

	// Get the perimeter of a Circle
	double get_perimeter()
	{
		return(2 * PI * radius);
	}

	// Print the area
	void print_area(double area)
	{
		cout << "The surface area of a Cylinder is: " << area << endl;
	}

	// Print the volume
	void print_volume(double volume)
	{
		cout << "The volume of a Cylinder is: " << volume << endl;
	}

	// Print the perimeter
	void print_perimeter(double perimeter)
	{
		cout << "The perimeter of a Cylinder Base is a Circle: " << perimeter << endl;
	}
};

class Cone : public Shape
{
	public:
	// Member functions

	// Get the area of a Cone
	double get_area()
	{
		return((PI * pow(radius, 2)) + (PI * radius * sqrt(pow(radius, 2) + pow(height, 2))));
	}

	// Get the volume of a Cone
	double get_volume()
	{
		return((static_cast<double>(1) / static_cast<double>(3)) * PI * pow(radius, 2) * height);
	}

	// Get the perimeter of a Circle
	double get_perimeter()
	{
		return(2 * PI * radius);
	}

	// Print the area
	void print_area(double area)
	{
		cout << "The surface area of a Cone is: " << area << endl;
	}

	// Print the volume
	void print_volume(double volume)
	{
		cout << "The volume of a Cone is: " << volume << endl;
	}

	// Print the perimeter
	void print_perimeter(double perimeter)
	{
		cout << "The perimeter of a Cone Base is a Circle: " << perimeter << endl;
	}
};

class Ellipse : public Shape
{
	public:
	// Member functions

	// Get the curvature of a Ellipse
	double get_curvature()
	{
		return(2 * PI * sqrt((side_a * side_a + side_b * side_b) / 2) / (side_a + side_b));
	}

	// Print the curvature
	void print_curvature(double curvature)
	{
		cout << "The curvature of a Ellipse is: " << curvature << endl;
	}
};

int main()
{
	cout << "*~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~* Rectangle *~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~*" << endl;
	Rectangle rectangle;
	rectangle.set_length(get_valid_input<double>("Set the length for a rectangle: "));
	rectangle.set_width(get_valid_input<double>("Set the width for a rectangle: "));
	rectangle.print_area(rectangle.get_area());
	rectangle.print_perimeter(rectangle.get_perimeter());
	cout << "*~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~* Triangle *~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~*" << endl;
	Triangle triangle;
	triangle.set_base(get_valid_input<double>("Set the base for a triangle: "));
	triangle.set_height(get_valid_input<double>("Set the height for a triangle: "));
	triangle.set_side_a(get_valid_input<double>("Set the side a for a triangle: "));
	triangle.set_side_b(get_valid_input<double>("Set the side b for a triangle: "));
	triangle.set_side_c(get_valid_input<double>("Set the side c for a triangle: "));
	triangle.print_area(triangle.get_area());
	triangle.print_perimeter(triangle.get_perimeter());
	cout << "*~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~* Circle *~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~*" << endl;
	Circle circle;
	circle.set_radius(get_valid_input<double>("Set the radius of a circle: "));
	circle.print_area(circle.get_area());
	circle.print_perimeter(circle.get_perimeter());
	circle.print_curvature(circle.get_curvature());
	cout << "*~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~* Square *~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~*" << endl;
	Square square;
	square.set_side_a(get_valid_input<double>("Set the side of a square: "));
	square.print_area(square.get_area());
	square.print_perimeter(square.get_perimeter());
	cout << "*~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~* Cube *~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~*" << endl;
	Cube cube;
	cube.set_side_a(get_valid_input<double>("Set the side of a cube: "));
	cube.print_area(cube.get_area());
	cube.print_perimeter(cube.get_perimeter());
	cube.print_volume(cube.get_volume());
	cout << "*~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~* Sphere *~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~*" << endl;
	Sphere sphere;
	sphere.set_radius(get_valid_input<double>("Set the radius of a sphere: "));
	sphere.print_area(sphere.get_area());
	sphere.print_volume(sphere.get_volume());
	cout << "*~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~* Cylinder *~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~*" << endl;
	Cylinder cylinder;
	cylinder.set_radius(get_valid_input<double>("Set the radius of a cylinder: "));
	cylinder.set_height(get_valid_input<double>("Set the height for a cylinder: "));
	cylinder.print_area(cylinder.get_area());
	cylinder.print_perimeter(cylinder.get_perimeter());
	cylinder.print_volume(cylinder.get_volume());
	cout << "*~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~* Cone *~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~*" << endl;
	Cone cone;
	cone.set_radius(get_valid_input<double>("Set the radius of a cone: "));
	cone.set_height(get_valid_input<double>("Set the height for a cone: "));
	cone.print_area(cone.get_area());
	cone.print_perimeter(cone.get_perimeter());
	cone.print_volume(cone.get_volume());
	cout << "*~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~* Ellipse *~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~**~*" << endl;
	Ellipse ellipse;
	ellipse.set_side_a(get_valid_input<double>("Set the side a for a ellipse: "));
	ellipse.set_side_b(get_valid_input<double>("Set the side b for a ellipse: "));
	ellipse.print_curvature(ellipse.get_curvature());

	return 0;
}