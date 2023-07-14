#include <iostream>
#include "headers/basic_functions.h"

using namespace std;
// - Arrays
//  - Insertion is bad - lots of shifting to fit an element in the middle
//  - Deletion is bad - lots of shifting after removing an element
//  - Lookup is great - random access, constant time
//  - Relatively easy to sort
//  - Relatively small size - wise
//  - Stuck with a fixed size, no flexibility

// Definition -
// Stack is a linear data structure which operates in a LIFO(Last In First Out) or FILO(First In Last Out) pattern.
// It is named stack as it behaves like a real - world stack, for example - a deck of cards or a pile of plates, etc.
// Stack is an abstract data type with a bounded(predefined) capacity.
// It is a simple data structure that allows adding and removing elements in a particular order.
// The order may be LIFO(Last In First Out) or FILO(First In Last Out).

// Standard Stack Operations -
// push() -      Place an item onto the stack. If there is no place for new item, stack is in overflow state.
// pop() -       Return the item at the top of the stack and then remove it. If pop is called when stack is empty, it is in an underflow state.
// is_empty() -  Tells if the stack is empty or not
// is_full() -   Tells if the stack is full or not
// peek() -      Access the item at the i position
// count() -     Get the number of items in the stack
// change() -    Change the item at the i position
// display() -   Display all items in the stack

// Classes
template <typename T>
class Stack
{
	private:
	// Member variables
	int top; // Keep track of position, aka how full is our stack at the moment
	int size;
	T *arr;

	public:
	// Member functions

	// Constructor
	Stack()
	{
		top = -1;
		size = get_stack_size();
		arr = new T[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = T();
		}
	}

	// Destructor
	~Stack()
	{
		delete[] arr;
	}

	// Get the size of the stack we want to create
	int get_stack_size()
	{
		do
		{
			size = get_valid_input<int>("Enter stack size: ");
		} while (size < 1);
		return size;
	}

	// Show the stack size
	int show_stack_size() const
	{
		return size;
	}

	// Show the top
	int show_top() const
	{
		return top;
	}

	// Is the stack empty
	bool is_empty() const
	{
		if (top == -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Is the stack full
	bool is_full() const
	{
		if (top == size - 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Push: Add a new element to the top of the stack
	// • Accept a pointer to the stack
	// • Accept data of type VALUE to be added to the stack
	// • Change the location of the top of the stack
	// • Add that data to the stack at the top of the stack
	void push(T value)
	{
		if (is_full())
		{
			cerr << "Sack overflow!" << endl;
		}
		else
		{
			top++; //------------------------ Each time we add a value we increment top fist, firstly because top is -1, aka pointing at nothing, and the rest because top always is the index of the current top element in the stack
			arr[top] = value; //------------- Add value to the current top position;
		}
	}

	// Pop: Remove the most recent element from the top of the stack
	// • Accept a pointer to the stack.
	// • Change the location of the top of the stack.
	// • Return the value that was removed from the stack
	T pop()
	{
		if (is_empty())
		{
			cerr << "Stack underflow!" << endl;
			return T();
		}
		else
		{
			T pop_value = arr[top]; //--------- Get the top value
			arr[top] = T(); //----------------- Replace the top value with the default
			top--; //-------------------------- Decrement the top to point at the value below it, aka keep track of the stack size
			return pop_value;
		}
	}

	// Count how many elements we have in the stack
	int count() const
	{
		return (top + 1);
	}

	// See what value is at a current position of a stack
	T peek(int position) const
	{
		if (position > top || position < 0)
		{
			cerr << "Stack out of bounds!" << endl;
			return T();
		}
		else
		{
			return arr[position];
		}
	}

	// Change a value in a current position of a stack
	void change(int position, T value)
	{
		if (position > top || position < 0)
		{
			cerr << "Stack out of bounds!" << endl;
		}
		else
		{
			arr[position] = value;
			cout << "Value changed at location: " << position << endl;
		}
	}

	// Display all of the stack
	void display() const
	{
		cout << "All values in the Stack are: " << endl;
		for (int i = size - 1; i >= 0; i--)
		{
			cout << "Position " << i << " -> " << arr[i] << endl;
		}
	}
};

// Functions
void print_menu();
int get_choice();

int main()
{
	Stack<int> s1;
	int choice = 0;
	int position = 0;
	do
	{
		print_menu();
		choice = get_choice();
		switch (choice)
		{
			case 0:
				break;
			case 1:
				s1.push(get_valid_input<int>("Enter an item to push in the stack: "));
				break;
			case 2:
				cout << "Poped Value: " << s1.pop() << endl;
				break;
			case 3:
				if (s1.is_empty())
				{
					cout << "Stack is empty!" << endl;
				}
				else
				{
					cout << "Stack is not empty!" << endl;
				}
				break;
			case 4:
				if (s1.is_full())
				{
					cout << "Stack is full!" << endl;
				}
				else
				{
					cout << "Stack is not full!" << endl;
				}
				break;
			case 5:
				cout << "Number of Items in the Stack are: " << s1.count() << endl;
				break;
			case 6:
				position = get_valid_input<int>("Enter position of item you want to peek: ");
				cout << "Value at position " << position << " is " << s1.peek(position) << endl;
				break;
			case 7:
				s1.change(get_valid_input<int>("Enter position of item you want to change: "), get_valid_input<int>("Enter value of item you want to change: "));
				break;
			case 8:
				s1.display();
				break;
			case 9:
				cout << "Stack size is: " << s1.show_stack_size() << endl;
				break;
			case 10:
				cout << "Top is: " << s1.show_top() << endl;
				break;
			case 11:
				system("cls");
				break;
			default:
				cout << "Try again" << endl;
				break;
		}
		cout << "\n\t\t"; system("pause"); // or cin.get(); // For a pause every new operation
	} while (choice != 0);

	return 0;
}

// Print the menu
void print_menu()
{
	cout << "\nWhat operation do you want to perform? Select Option number. Enter 0 to exit." << endl;
	cout << "1. push()" << endl;
	cout << "2. pop()" << endl;
	cout << "3. is_empty()" << endl;
	cout << "4. is_full()" << endl;
	cout << "5. count()" << endl;
	cout << "6. peek()" << endl;
	cout << "7. change()" << endl;
	cout << "8. display()" << endl;
	cout << "9. Show stack size" << endl;
	cout << "10. Show the top " << endl;
	cout << "11. Clear Screen" << endl << endl;
}

// Get the choice for the menu
int get_choice()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 0 || choice > 11);
	return choice;
}