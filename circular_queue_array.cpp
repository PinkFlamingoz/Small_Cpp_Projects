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
// Circular queue is a linear data structure in which the operations are performed based on FIFO(First In First Out) principle and the last position is connected back to the first position to make a circle.
// It is also called 'Ring Buffer'.
// It is a type of Queue data structure which overcomes some drawback of the simple queue data structure.
// In a Linear queue, once the queue is completely full, it's not possible to insert more elements.
// Even if we dequeue the queue to remove some of the elements, until the queue is reset, no new elements can be inserted.
// When we dequeue any element to remove it from the queue, we are actually moving the front of the queue forward, thereby reducing the overall size of the queue.And we cannot insert new elements, because the rear pointer is still at the end of the queue.
// The only way is to reset the linear queue, for a fresh start.

// Classes
template <typename T>
class Circular_queue
{
	private:
	// Member variables
	int front; // The front represents the front of the queue, the value we have to delete for example
	int rear; //- The rear represents the back of the queue, the value we have to insert
	int size;
	int item_count;
	T *arr;

	public:
	// Member functions

	// Constructor
	Circular_queue()
	{
		front = -1;
		rear = -1;
		item_count = 0;
		size = get_queue_size();
		arr = new T[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = T();
		}
	}

	// Destructor
	~Circular_queue()
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
		if ((rear + 1) % size == front)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// Example:
	// size = 5; we have 0=[] 1=[] 2=[] 3=[] 4=[]
	// rear = 4 aka at the end;
	// front = 0 aka we have not dequeued anything yet;
	// rear = (4 + 1) % 5 = 0 == 0 = front; condition is true and the queue is full

	// rear = 4 aka at the end;
	// front = 1 we dequeue once;
	// rear = (4 + 1) % 5 = 0 == 1 = front; condition is not true, now there is free space to add at the beginning of the circle

	// rear = 0 aka we added one more value;
	// front = 1 aka we have not dequeued;
	// rear = (0 + 1) % 5 = 1 == 1 = front; condition is true and the queue is full

	// Add to the queue
	void enqueue(T value)
	{
		if (is_full())
		{
			cerr << "Circular queue full!" << endl;
			return;
		}
		else if (is_empty()) //------------------- We check if its the first element in the queue in this case we have to increase rear and front +1 because they are both -1
		{
			rear = 0;
			front = 0;
			arr[rear] = value;
			item_count++;
		}
		else //----------------------------------- If we already have elements in the queue then we simply increase the rear and add the value there at the new rear index
		{
			rear = (rear + 1) % size;
			arr[rear] = value;
			item_count++;
		}
	}
	// Example: size = 5; rear = 0; we have 0=[] 1=[] 2=[] 3=[] 4=[]
	// rear = (0 + 1) % 5 = 1
	// rear = (1 + 1) % 5 = 2
	// rear = (2 + 1) % 5 = 3
	// rear = (3 + 1) % 5 = 4
	// rear = (4 + 1) % 5 = 0
	// When the rear reaches the 4 it goes to the start, hence making a circle

	// Remove from the queue
	T dequeue()
	{
		T x{};
		if (is_empty())
		{
			cerr << "Circular queue is empty!" << endl;
			return x;
		}
		else if (front == rear) //-------------------- We check if the rear and front are equal which means that the queue has come to an end and we have to re-set it to position -1, aka empty
		{
			cout << "front value: " << front << " -> ";
			x = arr[front];
			arr[front] = T();
			rear = -1;
			front = -1;
			item_count--;
			return x;
		}
		else //--------------------------------------- If we are not at the end of the queue we simply get the value at the front, replace that position with the default and increase the front to point at the next in line
		{
			cout << "front value: " << front << " -> ";
			x = arr[front];
			arr[front] = T();
			front = (front + 1) % size;
			item_count--;
			return x;
		}
	}
	// Example: size = 5; front = 0; we have 0=[] 1=[] 2=[] 3=[] 4=[]
	// front = (0 + 1) % 5 = 1
	// front = (1 + 1) % 5 = 2
	// front = (2 + 1) % 5 = 3
	// front = (3 + 1) % 5 = 4
	// front = (4 + 1) % 5 = 0
	// When the front reaches the 4 it goes to the start, hence making a circle

	// Count how many elements in the queue
	int count() const
	{
		return item_count;
	}

	// See what value is at a current position of a stack
	T peek(int possition) const
	{
		if (possition > rear || possition < front || possition < 0)
		{
			cerr << "Circular queue out of bounds!" << endl;
			return T();
		}
		else
		{
			return arr[possition];
		}
	}

	// Change a value in a current position of a stack
	void change(int possition, T value)
	{
		if (possition > rear || possition < front || possition < 0)
		{
			cerr << "Circular queue out of bounds!" << endl;
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
		cout << "All values in the Circular queue are - " << endl;
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
	Circular_queue<int> q1;
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
				q1.enqueue(get_valid_input<int>("Enter an item to Enqueue in the Circular queue: "));
				break;
			case 2:
				cout << "Dequeued Value: " << q1.dequeue() << endl;
				break;
			case 3:
				if (q1.is_empty())
				{
					cout << "Circular queue is empty!" << endl;
				}
				else
				{
					cout << "Circular queue is not empty!" << endl;
				}
				break;
			case 4:
				if (q1.is_full())
				{
					cout << "Circular queue is full!" << endl;
				}
				else
				{
					cout << "Circular queue is not full!" << endl;
				}
				break;
			case 5:
				cout << "Number of items in Circular queue are: " << q1.count() << endl;
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
				cout << "Circular queue size is: " << q1.show_queue_size() << endl;
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