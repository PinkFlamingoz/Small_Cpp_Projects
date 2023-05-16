#include <iostream>
#include "basic_functions.h"

using namespace std;
// • Arrays
//  • Insertion is bad – lots of shifting to fit an element in the middle
//  • Deletion is bad – lots of shifting after removing an element
//  • Lookup is great – random access, constant time
//  • Relatively easy to sort
//  • Relatively small size - wise
//  • Stuck with a fixed size, no flexibility

// Definition –
// Queue is a linear data structure which operates in a First IN First OUT or Last IN Last OUT.
// It is named queue as it behaves like a real - world queue, for example – queue(line) of cars in a single lane, queue of people waiting at food counter etc.
// Queue is an abstract data type with a bounded(predefined) capacity.
// It is a simple data structure that allows adding and removing elements in a particular order.
// The order is FIFO(First IN First OUT) or LILO(Last In Last Out).

// Standard Queue Operations –
// enqueue() – Add item to the queue from the REAR.
// dequeue() – Remove item from the queue from the FRONT.
// is_full() – Check if queue is full or not.
// is_empty() – Check if queue empty or not.
// count() – Get number of items in the queue.

// Some types of Queue(We will discuss them in detail in other articles) -
// Simple Queue
// Circular queue
// Priority Queue

// Classes
template <typename T>
class Queue
{
	private:
	// Member variables
	int front; // The front represents the front of the queue, the value we have to delete for example
	int rear; //- The rear represents the back of the queue, the value we have to insert
	int size;
	T *arr;

	public:
	// Member functions

	// Constructor
	Queue()
	{
		front = -1;
		rear = -1;
		size = get_queue_size();
		arr = new T[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = T();
		}
	}

	// Destructor
	~Queue()
	{
		delete[] arr;
	}

	// Get the size of the queue we want to create
	int get_queue_size()
	{
		do
		{
			size = get_valid_input<int>("Enter queue size: ");
		} while (size < 1);
		return size;
	}

	// Show the queue size
	int show_queue_size() const
	{
		return size;
	}

	// Show the front
	int show_front() const
	{
		return front;
	}

	// Show the rear
	int show_rear() const
	{
		return rear;
	}

	// Is the queue empty!
	bool is_empty() const
	{
		if (front == -1 && rear == -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Is the queue full!
	bool is_full() const
	{
		if (rear == size - 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Add to the queue
	void enqueue(T value)
	{
		if (is_full())
		{
			cerr << "Queue full!" << endl;
			return;
		}
		else if (is_empty()) //---------- We check if its the first element in the queue in this case we have to increase rear and front +1 because they are both -1
		{
			rear = 0;
			front = 0;
			arr[rear] = value;
		}
		else //-------------------------- If we already have elements in the queue then we simply increase the rear and add the value there at the new rear index
		{
			rear++;
			arr[rear] = value;
		}
	}

	// Remove from the queue
	T dequeue()
	{
		T x{};
		if (is_empty())
		{
			cerr << "Queue is empty!" << endl;
			return x;
		}
		else if (front == rear) //--------------------- We check if the rear and front are equal which means that the queue has come to an end and we have to re-set it to position -1, aka empty
		{
			cout << "front value: " << front << " -> ";
			x = arr[front];
			arr[front] = T();
			rear = -1;
			front = -1;
			return x;
		}
		else //---------------------------------------- If we are not at the end of the queue we simply get the value at the front, replace that position with the default and increase the front to point at the next in line
		{
			cout << "front value: " << front << " -> ";
			x = arr[front];
			arr[front] = T();
			front++;
			return x;
		}
	}

	// Count how many elements in the queue
	int count() const
	{
		if (is_empty())
		{
			return 0;
		}
		else
		{
			return (rear - front + 1);
		}
	}

	// See what value is at a current position of a queue
	T peek(int possition) const
	{
		if (possition > rear || possition < front || possition < 0)
		{
			cerr << "Queue out of bounds!" << endl;
			return T();
		}
		else
		{
			return arr[possition];
		}
	}

	// Change a value in a current position of a queue
	void change(int possition, T value)
	{
		if (possition > rear || possition < front || possition < 0)
		{
			cerr << "Queue out of bounds!" << endl;
		}
		else
		{
			arr[possition] = value;
			cout << "Value changed at location: " << possition << endl;
		}
	}

	// Display all of the queue
	void display() const
	{
		cout << "All values in the Queue are - " << endl;
		for (int i = 0; i < size; i++)
		{
			cout << arr[i] << "  ";
		}
	}
};

// Functions
void print_menu();
int get_choice();

int main()
{
	Queue<int> q1;
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
				q1.enqueue(get_valid_input<int>("Enter an item to Enqueue in the Queue: "));
				break;
			case 2:
				cout << "Dequeued Value: " << q1.dequeue() << endl;
				break;
			case 3:
				if (q1.is_empty())
				{
					cout << "Queue is empty!" << endl;
				}
				else
				{
					cout << "Queue is not empty!" << endl;
				}
				break;
			case 4:
				if (q1.is_full())
				{
					cout << "Queue is full!" << endl;
				}
				else
				{
					cout << "Queue is not full!" << endl;
				}
				break;
			case 5:
				cout << "Number of items in Queue are: " << q1.count() << endl;
				break;
			case 6:
				position = get_valid_input<int>("Enter position of item you want to peek: ");
				cout << "Value at position " << position << " is " << q1.peek(position) << endl;
				break;
			case 7:
				q1.change(get_valid_input<int>("Enter position of item you want to change: "), get_valid_input<int>("Enter value of item you want to change: "));
				break;
			case 8:
				q1.display();
				break;
			case 9:
				cout << "Queue size is: " << q1.show_queue_size() << endl;
				break;
			case 10:
				cout << "Front is: " << q1.show_front() << endl;
				break;
			case 11:
				cout << "Rear is: " << q1.show_rear() << endl;
				break;
			case 12:
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

void print_menu()
{
	cout << "\nWhat operation do you want to perform? Select Option number. Enter 0 to exit." << endl;
	cout << "1. enqueue()" << endl;
	cout << "2. dequeue()" << endl;
	cout << "3. is_empty()" << endl;
	cout << "4. is_full()" << endl;
	cout << "5. count()" << endl;
	cout << "6. peek()" << endl;
	cout << "7. change()" << endl;
	cout << "8. display()" << endl;
	cout << "9. Show queue size" << endl;
	cout << "10. Show front " << endl;
	cout << "11. Show rear " << endl;
	cout << "12. Clear Screen" << endl << endl;
}

// Get the choice for the menu
int get_choice()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 0 || choice > 12);
	return choice;
}