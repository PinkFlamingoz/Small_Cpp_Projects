#include <iostream>
#include "basic_functions.h"

// - Linked lists
//  - Insertion is easy - just tack onto the front
//  - Deletion is easy - once you find the element
//  - Lookup is bad - have to rely on linear search
//  - Relatively difficult to sort - unless you're willing to compromise on super - fast insertion and instead sort as you construct
//  - Relatively small size - wise(not as small as arrays)

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
// peek() -      Access the item at the i position
// count() -     Get the number of items in the stack
// change() -    Change the item at the i position
// display() -   Display all items in the stack

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
class Stack
{
	private:
	// Member variables
	Node<K, D> *top;

	public:
	// Member functions

	// Constructor
	Stack()
	{
		top = nullptr;
	}

	// Parameter constructor
	Stack(Node<K, D> *top)
	{
		this->top = top;
	}

	// Destructor
	~Stack()
	{
		delete_stack();
	}

	// Get the top of the stack
	Node<K, D> *get_top() const
	{
		return top;
	}

	// Is the stack empty!
	bool is_empty() const
	{
		if (top == nullptr)
		{
			return true;
		}
		return false;
	}

	// Check if node exists
	// All that we do here is make a traversal pointer and use that pointer to check all the nodes in the linked list for the same key
	Node<K, D> *node_exists(K key) const
	{
		Node<K, D> *temp = nullptr; //----------------------------------------------------------- We create a temp pointer so we can store the address of the node that exists with that key

		for (Node<K, D> *trav_ptr = top; trav_ptr != nullptr; trav_ptr = trav_ptr->get_next()) // We create a traversal pointer pointing to the stack's top, and after a cycle has been completed we set that traversal pointer to point at the next node, until we reach the end, aka at the end of the list its always a nullptr (We do this because we don't want the top to change whats it pointing at, if we change the top here we will lose the list)
		{
			if (trav_ptr->get_key() == key) //--------------------------------------------------- If the keys match
			{
				temp = trav_ptr; //-------------------------------------------------------------- Then make temp point at the address that the traversal pointer points at, aka we get the node with the same key
				break;
			}
		}

		return temp;
	}

	// To push, dynamically allocate a new node, set its next pointer to point to the current top of the list, then move the top pointer to the newly-created node
	void push(Node<K, D> *new_node)
	{
		if (node_exists(new_node->get_key()) != nullptr)
		{
			cerr << "\nNode already exists with this key: " << new_node->get_key() << endl;
			delete new_node;
			return;
		}

		if (top == nullptr)
		{
			top = new_node;
			cout << "\nNew node with key[" << new_node->get_key() << "] and data: " << new_node->get_data() << " pushed successfully!" << endl;
		}
		else
		{
			new_node->set_next(top);
			top = new_node;
			cout << "\nNew node with key[" << new_node->get_key() << "] and data: " << new_node->get_data() << " pushed successfully!" << endl;
		}
	}

	// To pop, traverse the linked list to its second element (if it exists), free the top of the list, then move the top pointer to the (former) second element
	void pop()
	{
		if (is_empty())
		{
			cerr << "\nStack underflow!" << endl;
			return;
		}

		Node<K, D> *temp = nullptr;
		temp = top;
		top = top->get_next();

		cout << "\nNode with key[" << temp->get_key() << "] and data: " << temp->get_data() << " popped!" << endl;
		delete temp;
	}

	// Count how many elements we have in the stack
	int count() const
	{
		int count = 0;
		for (Node<K, D> *trav_ptr = top; trav_ptr != nullptr; trav_ptr = trav_ptr->get_next())
		{
			count++;
		}

		return count;
	}

	// See what value is at a current position of a stack
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

	// Change a value in a current position of a stack
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

	// Display all of the stack
	void display() const
	{
		if (is_empty())
		{
			cout << "\nStack is empty!" << endl;
			return;
		}

		cout << "\nAll items in the Stack are: " << endl;
		for (Node<K, D> *trav_ptr = top; trav_ptr != nullptr; trav_ptr = trav_ptr->get_next())
		{
			cout << "[" << trav_ptr << "] Key[" << trav_ptr->get_key() << "] data: " << trav_ptr->get_data() << " ---> [" << trav_ptr->get_next() << "]" << endl;
		}
	}

	// Delete stack
	void delete_stack()
	{
		while (top != nullptr)
		{
			Node<K, D> *temp = top->get_next(); // Grab the next pointer before deleting this one!
			delete top;
			top = temp;
		}
		cout << "\nStack deleted!\n";
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
	Stack<int, int> s1;
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
				s1.push(Stack<int, int>::create_node());
				break;
			case 2:
				s1.pop();
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
				cout << "Number of Items in the Stack are: " << s1.count() << endl;
				break;
			case 5:
				key = get_valid_input<int>("Enter key of the item you want to peek: ");
				cout << "Data at key[" << key << "] is: " << s1.peek(key) << endl;
				break;
			case 6:
				s1.change(get_valid_input<int>("Enter key of item you want to change: "), get_valid_input<int>("Enter data of item you want to change: "));
				break;
			case 7:
				s1.display();
				break;
			case 8:
				if (s1.is_empty())
				{
					cout << "Stack is empty!" << endl;
				}
				else
				{
					cout << "Top is node with key: " << s1.get_top()->get_key() << endl;
				}
				break;
			case 9:
				s1.delete_stack();
				break;
			case 10:
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
	cout << "4. count()" << endl;
	cout << "5. peek()" << endl;
	cout << "6. change()" << endl;
	cout << "7. display()" << endl;
	cout << "8. Show the top " << endl;
	cout << "9. Delete stack " << endl;
	cout << "10. Clear Screen" << endl << endl;
}

// Get the choice for the menu
int get_choice()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 0 || choice > 10);
	return choice;
}