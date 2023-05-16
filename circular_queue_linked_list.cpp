#include <iostream>
#include "basic_functions.h"

using namespace std;
// • Linked lists
//  • Insertion is easy – just tack onto the front
//  • Deletion is easy – once you find the element
//  • Lookup is bad – have to rely on linear search
//  • Relatively difficult to sort – unless you're willing to compromise on super - fast insertion and instead sort as you construct
//  • Relatively small size - wise(not as small as arrays)

// Definition –
// Circular queue is a linear data structure in which the operations are performed based on FIFO(First In First Out) principle and the last position is connected back to the first position to make a circle.
// It is also called 'Ring Buffer'.
// It is a type of Circular queue data structure which overcomes some drawback of the simple queue data structure.
// In a Linear queue, once the queue is completely full, it's not possible to insert more elements.
// Even if we dequeue the queue to remove some of the elements, until the queue is reset, no new elements can be inserted.
// When we dequeue any element to remove it from the queue, we are actually moving the front of the queue forward, thereby reducing the overall size of the queue. And we cannot insert new elements, because the rear pointer is still at the end of the queue.
// The only way is to reset the linear queue, for a fresh start.

// Classes
template <typename K, typename D>
class Node
{
	private:
	// Member variables
	K key;
	D data;
	Node<K, D> *next;
	public:
	// Member functions

	// Constructor
	Node()
	{
		key = K();
		data = D();
		next = nullptr;
	}

	// Parameter constructor
	Node(K key, D data)
	{
		this->key = key;
		this->data = data;
	}

	// Get the key
	K get_key() const
	{
		return key;
	}

	// Get the data
	D get_data() const
	{
		return data;
	}

	// Get next
	Node<K, D> *get_next() const
	{
		return next;
	}

	// Set the key
	void set_key(K key)
	{
		this->key = key;
	}

	// Set the data
	void set_data(D data)
	{
		this->data = data;
	}

	// Set next
	void set_next(Node<K, D> *next)
	{
		this->next = next;
	}
};

template <typename K, typename D>
class Circular_queue
{
	private:
	// Member variables
	Node<K, D> *front;
	Node<K, D> *rear;

	public:
	// Member functions

	// Constructor
	Circular_queue()
	{
		front = nullptr;
		rear = nullptr;
	}

	// Parameter constructor
	Circular_queue(Node<K, D> *new_front, Node<K, D> *new_rear)
	{
		front = new_front;
		rear = new_rear;
	}

	// Destructor
	~Circular_queue()
	{
		delete_queue();
	}

	// Show the front
	Node<K, D> *get_front() const
	{
		return front;
	}

	// Show the rear
	Node<K, D> *get_rear() const
	{
		return rear;
	}

	// Check if node exists
	// All that we do here is make a traversal pointer and use that pointer to check all the nodes in the linked list for the same key because the last node will point at the first node we must use a do while loop
	Node<K, D> *node_exists(K key) const
	{
		Node<K, D> *temp = nullptr; //------ We create a temp pointer so we can store the address of the node that exists with that key

		if (is_empty())
		{
			return temp;
		}

		Node<K, D> *trav_ptr = front;

		do
		{
			if (trav_ptr->get_key() == key)
			{
				temp = trav_ptr;
				return temp;
			}

			trav_ptr = trav_ptr->get_next();
		} while (trav_ptr != front);

		return temp;
	}

	// Is the queue empty!
	bool is_empty() const
	{
		if (front == nullptr && rear == nullptr)
		{
			return true;
		}
		return false;
	}

	// Add to the queue
	void enqueue(Node<K, D> *new_node)
	{
		if (node_exists(new_node->get_key()) != nullptr)
		{
			cerr << "\nNode already exists with this key: " << new_node->get_key() << endl;
			return;
		}

		if (is_empty())
		{
			front = new_node;
			rear = new_node;
			rear->set_next(new_node);
			cout << "\nNew node with key[" << new_node->get_key() << "] and data: " << new_node->get_data() << " enqueued successfully!" << endl;
		}
		else
		{
			rear->set_next(new_node);
			rear = new_node;
			new_node->set_next(front);
			cout << "\nNew node with key[" << new_node->get_key() << "] and data: " << new_node->get_data() << " enqueued successfully!" << endl;
		}
	}

	// Remove from the queue
	void dequeue()
	{
		if (is_empty())
		{
			cerr << "\nCircular queue is empty!" << endl;
			return;
		}

		if (front == rear) //----------------------------------------------------------------------------------------- If we have one element in the queue
		{
			Node<K, D> *temp = front;
			front = nullptr;
			rear = nullptr;

			cout << "\nNode with key[" << temp->get_key() << "] and data: " << temp->get_data() << " dequeued!" << endl;
			delete temp;
		}
		else //------------------------------------------------------------------------------------------------------- If we have more than one element in the queue
		{
			Node<K, D> *temp = front;
			front = front->get_next();
			rear->set_next(front);

			cout << "\nNode with key[" << temp->get_key() << "] and data: " << temp->get_data() << " dequeued!" << endl;
			delete temp;
		}
	}

	// Count how many elements in the queue
	int count() const
	{
		if (is_empty())
		{
			cout << "\nCircular queue is empty!" << endl;
			return 0;
		}

		int count = 0;

		Node<K, D> *trav_ptr = front;
		do
		{
			count++;

			trav_ptr = trav_ptr->get_next();
		} while (trav_ptr != front);

		return count;
	}

	// See what value is at a current position of a queue
	D peek(K key) const
	{
		Node<K, D> *temp = node_exists(key);
		if (temp == nullptr)
		{
			cerr << "\nThere is no node with that key: " << key << endl;
			return D();
		}

		return temp->get_data();
	}

	// Change a value in a current position of a queue
	void change(K key, D data)
	{
		Node<K, D> *temp = node_exists(key);
		if (temp == nullptr)
		{
			cerr << "\nThere is no node with that key: " << key << endl;
			return;
		}

		temp->set_data(data);

		cout << "\nData for node with key: " << key << " updated! \n";
	}

	// Display all of the queue
	void display() const
	{
		if (is_empty())
		{
			cout << "\nCircular queue is empty!" << endl;
			return;
		}

		cout << "\nAll items in the Circular queue are: " << endl;
		Node<K, D> *trav_ptr = front;
		do
		{
			cout << "[" << trav_ptr << "] Key[" << trav_ptr->get_key() << "] data: " << trav_ptr->get_data() << " ---> [" << trav_ptr->get_next() << "]";

			trav_ptr = trav_ptr->get_next();
		} while (trav_ptr != front);
	}

	// Delete queue
	void delete_queue()
	{
		if (is_empty())
		{
			cout << "\nCircular queue is empty!\n";
			return;
		}

		Node<K, D> *temp = front;
		do
		{
			Node<K, D> *next = temp->get_next(); // Grab the next pointer before deleting this one!
			delete temp;
			temp = next;
		} while (temp != front); //---------------- Continue until we reach the end of the list or encounter a null pointer
		front = nullptr;
		rear = nullptr;
		cout << "\nCircular queue deleted!\n";
	}

	// Create a node
	static Node<K, D> *create_node()
	{
		Node<K, D> *node = new Node<K, D>;
		cout << "\n================= Create node =================\n";
		node->set_key(get_valid_input<K>("Set key: "));
		node->set_data(get_valid_input<D>("Set the data: "));
		cout << "===============================================\n";
		return node;
	}
};

// Functions
void print_menu();
int get_choice();

int main()
{
	Circular_queue<int, int> q1;
	int choice = 0;
	int key = 0;
	do
	{
		print_menu();
		choice = get_choice();
		switch (choice)
		{
			case 0:
				break;
			case 1:
				q1.enqueue(Circular_queue<int, int>::create_node());
				break;
			case 2:
				q1.dequeue();
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
				cout << "Number of items in Circular queue are: " << q1.count() << endl;
				break;
			case 5:
				key = get_valid_input<int>("Enter key of the item you want to peek: ");
				cout << "Data at key[" << key << "] is: " << q1.peek(key) << endl;
				break;
			case 6:
				q1.change(get_valid_input<int>("Enter key of item you want to change: "), get_valid_input<int>("Enter data of item you want to change: "));
				break;
			case 7:
				q1.display();
				break;
			case 8:
				if (q1.is_empty())
				{
					cout << "Circular queue is empty!" << endl;
				}
				else
				{
					cout << "Front is: " << q1.get_front()->get_key() << endl;
				}
				break;
			case 9:
				if (q1.is_empty())
				{
					cout << "Circular queue is empty!" << endl;
				}
				else
				{
					cout << "Rear is: " << q1.get_rear()->get_key() << endl;
				}
				break;
			case 10:
				q1.delete_queue();
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

void print_menu()
{
	cout << "\nWhat operation do you want to perform? Select Option number. Enter 0 to exit." << endl;
	cout << "1. enqueue()" << endl;
	cout << "2. dequeue()" << endl;
	cout << "3. is_empty()" << endl;
	cout << "4. count()" << endl;
	cout << "5. peek()" << endl;
	cout << "6. change()" << endl;
	cout << "7. display()" << endl;
	cout << "8. Show front " << endl;
	cout << "9. Show rear " << endl;
	cout << "10. Delete queue " << endl;
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