#include <iostream>
#include "basic_functions.h"

using namespace std;
// • Linked lists
//  • Insertion is easy – just tack onto the front
//  • Deletion is easy – once you find the element
//  • Lookup is bad – have to rely on linear search
//  • Relatively difficult to sort – unless you're willing to compromise on super - fast insertion and instead sort as you construct
//  • Relatively small size - wise(not as small as arrays)

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
class Circular_linked_list
{
	private:
	// Member variables
	Node<K, D> *head;

	public:
	// Member functions

	// Constructor
	Circular_linked_list()
	{
		head = nullptr;
	}

	// Parameter constructor
	Circular_linked_list(Node<K, D> *new_head)
	{
		head = new_head;
	}

	// Destructor
	~Circular_linked_list()
	{
		delete_list();
	}

	// Get the head of the list
	Node<K, D> *get_head() const
	{
		return head;
	}

	// Check if the list is empty
	bool is_empty() const
	{
		if (head == nullptr)
		{
			return true;
		}
		return false;
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

		Node<K, D> *trav_ptr = head;
		do
		{
			if (trav_ptr->get_key() == key)
			{
				temp = trav_ptr;
				return temp;
			}

			trav_ptr = trav_ptr->get_next();
		} while (trav_ptr != head);

		return temp;
	}

	// Get last node
	Node<K, D> *get_last_node() const
	{
		Node<K, D> *trav_ptr = head;
		while (trav_ptr->get_next() != head)
		{
			trav_ptr = trav_ptr->get_next();
		}
		return trav_ptr;
	}

	// Prepend a node, aka add it at the front // CASE 1: LIST IS EMPTY, CASE 2: ADD AT THE FRONT
	void prepend_node(Node<K, D> *new_node)
	{
		if (node_exists(new_node->get_key()) != nullptr)
		{
			cerr << "\nNode already exists with this key: " << new_node->get_key() << endl;
			return;
		}

		if (head == nullptr) //------------------------------------------------------------ CASE 1: If this list is empty we make this new node the whole list, aka we set the head to point at this new node
		{
			head = new_node;
			new_node->set_next(head); //--------------------------------------------------- We set the last node which here is also the first to point back at itself
			cout << "\nNode prepended\n";
		}
		else //---------------------------------------------------------------------------- CASE 2: There are already elements in the list so we traverse till the end of the list and we make the last node point at the new node
		{
			Node<K, D> *last_node = get_last_node();
			last_node->set_next(new_node); //---------------------------------------------- We set the last node to point back at the head
			new_node->set_next(head); //--------------------------------------------------- Important: To set the new node to point at whatever the head is pointing so we don't lose whatever the head is pointing to
			head = new_node; //------------------------------------------------------------ Then we make the head point at this new node
			cout << "\nNode prepended\n";
		}
	}

	// Append a node, aka add it at the end // CASE 1: LIST IS EMPTY, CASE 2: ADD AT THE END
	void append_node(Node<K, D> *new_node)
	{
		if (node_exists(new_node->get_key()) != nullptr)
		{
			cerr << "\nNode already exists with this key: " << new_node->get_key() << endl;
			return;
		}

		if (head == nullptr) //------------------------------------------------------------ CASE 1: If this list is empty we make this new node the whole list, aka we set the head to point at this new node
		{
			head = new_node;
			new_node->set_next(head); //--------------------------------------------------- We set the last node which here is also the first to point back at itself
			cout << "\nNode appended\n";
		}
		else //---------------------------------------------------------------------------- CASE 2: There are already elements in the list so we traverse till the end of the list and we make the last node point at the new node
		{
			Node<K, D> *last_node = get_last_node();
			last_node->set_next(new_node);
			new_node->set_next(head); //--------------------------------------------------- We set the last node to point back at the head
			cout << "\nNode appended\n";
		}
	}

	// We insert a node after a certain key // NO CASES
	void insert_node_after(K key, Node<K, D> *new_node)
	{
		Node<K, D> *temp = node_exists(key); //-------------------------------------------- Get the node with that key
		if (temp == nullptr) //------------------------------------------------------------ We must check if a node exist with the key that we want to insert after it, with this we also check if the list is empty
		{
			cerr << "\nThere is no node with that key: " << key << endl;
			return;
		}

		if (node_exists(new_node->get_key()) != nullptr)
		{
			cerr << "\nNode already exists with this key: " << new_node->get_key() << endl;
			return;
		}

		new_node->set_next(temp->get_next());
		temp->set_next(new_node);
		cout << "\nNode inserted after node with key: " << key << endl;
	}

	// Insert node before a certain key // CASE 1: ADD AT FRONT, CASE 2: ADD ANYWHERE ELSE
	void insert_node_before(K key, Node<K, D> *new_node)
	{
		Node<K, D> *temp = node_exists(key);
		if (temp == nullptr)
		{
			cerr << "\nThere is no node with that key: " << key << endl;
			return;
		}

		if (node_exists(new_node->get_key()) != nullptr)
		{
			cerr << "\nNode already exists with this key: " << new_node->get_key() << endl;
			return;
		}

		Node<K, D> *previous = nullptr;
		Node<K, D> *current = head;
		do //------------------------------------------------------------------------------ We use this loop to find the previous pointer of the current node
		{
			if (current->get_key() == key)
			{
				break;
			}
			previous = current;
			current = current->get_next();
		} while (current->get_next() != head);

		if (previous == nullptr) //-------------------------------------------------------- CASE 1: If the node with the given key is the head of the list
		{
			Node<K, D> *last_node = get_last_node();
			last_node->set_next(new_node); //---------------------------------------------- We set the last node to point back at the head
			new_node->set_next(head); //--------------------------------------------------- Important: To set the new node to point at whatever the head is pointing so we don't lose whatever the head is pointing to
			head = new_node; //------------------------------------------------------------ Then we make the head point at this new node
			cout << "\nNode inserted before node with key: " << key << endl;
		}
		else //---------------------------------------------------------------------------- CASE 2: If it's not the head of the list
		{
			previous->set_next(new_node); //----------------------------------------------- Set the previous node to point to the new node
			new_node->set_next(current); //------------------------------------------------ Set the new node to point at the current node
			cout << "\nNode inserted before node with key: " << key << endl;
		}
	}

	// Insert sorted // CASE 1: EMPTY LIST, CASE 2: ADD IT AT THE FRONT, CASE 3: ADD IT AT THE END, CASE 4: ADD IT ANYWHERE ELSE
	void insert_node_sorted(Node<K, D> *new_node)
	{
		if (node_exists(new_node->get_key()) != nullptr)
		{
			cerr << "\nNode already exists with this key: " << new_node->get_key() << endl;
			return;
		}

		if (head == nullptr) //------------------------------------------------------------ CASE 1: If the list is empty
		{
			head = new_node; //------------------------------------------------------------ This node is the whole list
			new_node->set_next(head); //--------------------------------------------------- We set the last node which here is also the first to point back at itself
			cout << "\nNode inserted sorted in the empty list!\n";
		}
		else if (new_node->get_data() < head->get_data()) //------------------------------- CASE 2(Basically prepend): If the new node belongs at beginning of list
		{
			Node<K, D> *last_node = get_last_node();
			last_node->set_next(new_node); //---------------------------------------------- We set the last node to point back at the head
			new_node->set_next(head); //--------------------------------------------------- Set the new node to point at the current head node
			head = new_node; //------------------------------------------------------------ Set list to point at the last inserted node aka making it the new head
			cout << "\nNode inserted sorted at the beginning!\n";
		}
		else //---------------------------------------------------------------------------- CASE 3: If the new node belongs later in list
		{
			Node<K, D> *trav_ptr = head;
			do //-------------------------------------------------------------------------- Iterate over nodes in the list till the end
			{
				if (trav_ptr->get_next() == head) //--------------------------------------- CASE 3.1 (Basically append): If at end of list
				{
					Node<K, D> *last_node = get_last_node();
					last_node->set_next(new_node); //-------------------------------------- Set the last node of the csll to point at the new node
					new_node->set_next(head); //------------------------------------------- We set the last node to point back at the head
					cout << "\nNode inserted sorted at the end!\n";
					break;
				}
				if (new_node->get_data() < trav_ptr->get_next()->get_data()) //------------ CASE 3.2 (Basically insert after): If in middle of list, if the new node value is smaller than the next node value
				{
					new_node->set_next(trav_ptr->get_next()); //--------------------------- Set the new node to point at the current node pointer, aka the node after the current node
					trav_ptr->set_next(new_node); //--------------------------------------- Set the current node to point at the new node and this new node also points to the rest of the values in the circular singly linked list
					cout << "\nNode inserted sorted in the middle of the list!\n";
					break;
				}
				trav_ptr = trav_ptr->get_next();
			} while (trav_ptr != head);
		}
	}

	// Delete node by key // CASE 1:IF ITS THE FIRST NODE AND ITS THE ONLY NODE, CASE 2: IF ITS THE FIRST NODE AND THERE ARE MORE NODES, CASE 3: IF ITS ANY OTHER NODE
	void delete_node_by_key(K key)
	{
		if (node_exists(key) == nullptr)
		{
			cerr << "\nThere is no node with that key: " << key << endl;
			return;
		}

		Node<K, D> *previous = nullptr;
		Node<K, D> *current = head;
		do
		{
			if (current->get_key() == key)
			{
				if (previous == nullptr) //-------------------------------------------- CASE 1: If the first node matches
				{
					if (current->get_next() == head) //-------------------------------- CASE 1.1: If the list has only one element
					{
						head = nullptr; //--------------------------------------------- Set the list to point at nothing because there are no more nodes in the list
					}
					else //------------------------------------------------------------ CASE 1.2: If the list has more than one element
					{
						Node<K, D> *last_node = get_last_node();
						last_node->set_next(current->get_next()); //------------------- Set the last node of the csll to point at the new head
						head = current->get_next(); //--------------------------------- Set the head of the list to point at the next node in the list
					}
				}
				else //---------------------------------------------------------------- CASE 2: If a non-first node matches
				{
					previous->set_next(current->get_next());  //----------------------- Set the previous node pointer to point at the node that the current pointer points at
				}
				cout << "\nNode: " << current << " with key: " << key << " deleted!\n";
				delete current;
				break;
			}
			else //-------------------------------------------------------------------- If the current node doesn't match go to the next nodes
			{
				previous = current;
				current = current->get_next();
			}
		} while (current != head);
	}

	// Update node by key
	void update_node_by_key(K key, D data)
	{
		Node<K, D> *temp = node_exists(key);
		if (temp == nullptr)
		{
			cerr << "\nThere is no node with that key: " << key << endl;
			return;
		}

		temp->set_data(data);

		cout << "Data for node with key: " << key << " updated!\n";
	}

	// Peek node by key
	D peek_node_by_key(K key) const
	{
		Node<K, D> *temp = node_exists(key);
		if (temp == nullptr)
		{
			cerr << "\nThere is no node with that key: " << key << endl;
			return D();
		}

		return temp->get_data();
	}

	// Print list
	void print_list() const
	{
		if (is_empty())
		{
			cout << "\nList is empty!\n";
			return;
		}

		Node<K, D> *trav_ptr = head;
		do
		{
			cout << trav_ptr << " : [ " << trav_ptr->get_key() << " ] = [ " << trav_ptr->get_data() << " ] [ " << trav_ptr->get_next() << " ] ---> ";

			trav_ptr = trav_ptr->get_next();
		} while (trav_ptr != head);
	}

	// Delete list
	void delete_list()
	{
		if (is_empty())
		{
			cout << "\nList is empty!\n";
			return;
		}

		Node<K, D> *temp = head;
		do
		{
			Node<K, D> *next = temp->get_next(); // Grab the next pointer before deleting this one!
			delete temp;
			temp = next;
		} while (temp != head); //----------------- Continue until we reach the end of the list or encounter a null pointer
		head = nullptr;
		cout << "List deleted!\n";
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
	Circular_linked_list<int, int> list;
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
				cout << "\n================= Prepend node operation =================\n";
				cout << "Enter key & data of the node to be prepended\n";
				list.prepend_node(Circular_linked_list<int, int>::create_node());
				cout << "==========================================================\n";
				break;
			case 2:
				cout << "\n================= Append node operation =================\n";
				cout << "Enter key & data of the node to be appended\n";
				list.append_node(Circular_linked_list<int, int>::create_node());
				cout << "=========================================================\n";
				break;
			case 3:
				cout << "\n================= Insert node after operation =================\n";
				// Change this if the key is not a integer type
				list.insert_node_after(get_valid_input<int>("Enter key of existing node after which you want to insert this new node: "), Circular_linked_list<int, int>::create_node());
				cout << "===============================================================\n";
				break;
			case 4:
				cout << "\n================= Insert node before operation =================\n";
				// Change this if the key is not a integer type
				list.insert_node_before(get_valid_input<int>("Enter key of existing node before which you want to insert this new node: "), Circular_linked_list<int, int>::create_node());
				cout << "================================================================\n";
				break;
			case 5:
				cout << "\n================= Insert node sorted operation =================\n";
				list.insert_node_sorted(Circular_linked_list<int, int>::create_node());
				cout << "================================================================\n";
				break;
			case 6:
				cout << "\n================= Delete node by key operation =================\n";
				// Change this if the key is not a integer type
				list.delete_node_by_key(get_valid_input<int>("Enter key of the node to be deleted: "));
				cout << "================================================================\n";
				break;
			case 7:
				cout << "\n================= Update node by key operation =================\n";
				// Change this if the key or data is not a integer type
				list.update_node_by_key(get_valid_input<int>("Enter key: "), get_valid_input<int>("Enter new data: "));
				cout << "================================================================\n";
				break;
			case 8:
				cout << "\n================= Peek node by key operation =================\n";
				// Change this if the key is not a integer type
				key = get_valid_input<int>("Enter key of the node you want to peek: ");
				cout << "Data at key: " << key << " is " << list.peek_node_by_key(key) << endl;
				cout << "==============================================================\n";
				break;
			case 9:
				list.print_list();
				break;
			case 10:
				cout << "\n================= Delete list operation =================\n";
				list.delete_list();
				cout << "=========================================================\n";
				break;
			case 11:
				system("cls");
				break;
			default:
				cout << "Try again!" << endl;
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
	cout << "1. prepend_node()" << endl;
	cout << "2. append_node()" << endl;
	cout << "3. insert_node_after()" << endl;
	cout << "4. insert_node_before()" << endl;
	cout << "5. insert_node_sorted()" << endl;
	cout << "6. delete_node_by_key()" << endl;
	cout << "7. update_node_by_key()" << endl;
	cout << "8. peek_node_by_key()" << endl;
	cout << "9. print_list()" << endl;
	cout << "10. delete_list()" << endl;
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