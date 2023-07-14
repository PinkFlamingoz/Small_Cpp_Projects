#include <iostream>
#include "headers/basic_functions.h"

using namespace std;
// NOTE: We can also have friend classes, when we create a friend class then all the member functions of the friend class also become the friend of the other class.
// This requires the condition that the friend becoming class must be first declared or defined.

// Classes
class Force
{
	private:
	// Member variables
	float body_mass;
	float time;
	float start_speed;
	float end_speed;
	float acceleration;

	public:
	// Member functions

	// Constructor
	Force()
	{
		body_mass = 0;
		time = 0;
		start_speed = 0;
		end_speed = 0;
		acceleration = 0;
	}

	// Print distance
	void print_force_variables() const
	{
		cout << "The body mass is: " << body_mass << endl;
		cout << "Time it took:     " << time << endl;
		cout << "Start speed is:   " << start_speed << endl;
		cout << "End speed is:     " << end_speed << endl;
		cout << "Acceleration is:  " << acceleration << endl;
	}

	// Friendly functions
	// They have the right to access all the private and protected members of the class.
	// We must pass in by reference the object we are trying to access.
	// They are not member functions, and are used in special cases when the data needs to be accessed directly without using an object of that class.
	// They can be used for operator overloading.
	friend float calculate_acceleration(Force &force);
	friend float calculate_force(Force &force);
};

int main()
{
	Force force; //----------------------------------------------------- Create an object
	force.print_force_variables(); //----------------------------------- Print the default value

	float F = calculate_force(force); //-------------------------------- Calculate the force

	force.print_force_variables(); //----------------------------------- Print the new value

	cout << "Force applied: " << F << endl;

	return 0; //-------------------------------------------------------- Success
}

//	Calculate acceleration
float calculate_acceleration(Force &force)
{
	do
	{
		force.start_speed = get_valid_input<float>("Enter the start speed of body: ");
		force.end_speed = get_valid_input<float>("Enter the end speed of body: ");
		force.time = get_valid_input<float>("Enter the time it took to reach that end speed: ");
	} while (force.start_speed < 1 || force.end_speed < 1 || force.time < 1);

	return force.acceleration = (force.end_speed - force.start_speed) / force.time;
}

// Calculate force
float calculate_force(Force &force)
{
	do
	{
		force.body_mass = get_valid_input<float>("Enter the body mass: ");
	} while (force.body_mass < 1);

	return force.body_mass * calculate_acceleration(force);
}