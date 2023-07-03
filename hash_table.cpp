#include <iostream>
#include "basic_functions.h"

using namespace std;
// - Hash tables
//  - Insertion is a two - step process - hash, then add
//  - Deletion is easy - once you find the element
//  - Lookup is on average better than with linked lists because you have he benefit of a real - world constant factor
//  - Not an ideal data structure if sorting is the goal - just use an array
//  - Can run the gamut of size
//
// Hash tables combine the random access ability of an array with the dynamism of a linked table.
// This means (assuming we define our hash table well):
//  - Insertion can start to tend toward q(1)
//  - Deletion can start to tend toward q(1)
//  - Lookup can start to tend toward q(1)
// We're gaining the advantages of both types of data structure, while mitigating the disadvantages.
//
// To get this performance upgrade, we create a new structure whereby when we insert data into the structure, the data itself gives us a clue about where we will find the data, should we need to later look it up.
// The trade off is that hash tables are not great at ordering or sorting data, but if we don't care about that, then we're good to go!
//
// A hash table amounts to a combination of two things with which we're quite familiar.
// - First, a hash function, which returns an nonnegative integer value called a hash code.
// - Second, an array capable of storing data of the type we wish to place into the data structure.
// - The idea is that we run our data through the hash function, and then store the data in the element of the array represented by the returned hash code.
//
// A good hash function should:
// - Use only the data being hashed
// - Use all of the data being hashed
// - Be deterministic
// - Uniformly distribute data
// - Generate very different hash codes for very similar data
//
// A collision occurs when two pieces of data, when run through the hash function, yield the same hash code.
// Presumably we want to store both pieces of data in the hash table, so we shouldn't simply overwrite the data that happened to be placed in there first.
// We need to find a way to get both elements into the hash table while trying to preserve quick insertion and lookup.
//
// Resolving collisions: Linear probing
// - In this method, if we have a collision, we try to place the data in the next consecutive element in the array (wrapping around to the beginning if necessary) until we find a vacancy.
// - That way, if we don't find what we're looking for in the first location, at least hopefully the element is somewhere nearby.
// - Linear probing is subject to a problem called clustering. Once there's a miss, two adjacent cells will contain data, making it more likely in the future that the cluster will grow.
// - Even if we switch to another probing technique, we're still limited. We can only store as much data as we have locations in our array.
//
// Resolving collisions: Chaining
// - What if instead of each element of the array holding just one piece of data, it held multiple pieces of data?
// - If each element of the array is a pointer to the head of a linked table, then multiple pieces of data can yield the same hash code and we'll be able to store it all!
// - We know that linked lists that insertion (and creation, if necessary) into a linked table is an O(1) operation.
// - For lookup, we only need to search through what is hopefully a small table, since we're distributing what would otherwise be one huge table across n lists.
//
// A hash function can be used with any kind of data that can be represented as a sequence of bytes. This is because a hash function needs to examine the bits of its input data to generate a hash value.
//
// Some common types of data that hash functions work with include:
// - Integers: A hash function for integers might be as simple as the identity function(returning the integer itself), or might do some kind of transformation to ensure a uniform distribution.
// - Strings: Strings are a very common input to hash functions.A hash function for strings will usually examine each character in the string to generate a hash.
// - Files: Hash functions can be used to generate a "checksum" for a file, which is a small piece of data that can be used to verify that the file has not been altered.
// - Objects: If you have a complex object, you can hash it by hashing its individual fields and then combining those hashes in some way.
// - Arrays or Lists: For an array or a list, a hash function can generate a hash by iterating over the elements and combining their hashes.
// Remember, the goal of a hash function is to generate a fixed - size output(the hash) that is as unique as possible for each unique input.A good hash function will minimize collisions(different inputs producing the same hash), and will distribute its output uniformly across the range of possible hash values.

// Globals
constexpr int MAX_SIZE = 10;

// Classes
template < typename D>
class Node
{
	private:
	// Member variables
	D data;
	Node<D> *next;

	public:
	// Member functions
	static_assert(is_same<D, int>::value || is_same<D, string>::value, "Type must be int or string!");

	// Constructor
	Node()
	{
		data = D();
		next = nullptr;
	}

	// Parameter constructor
	Node(D data)
	{
		this->data = data;
	}

	// Get the data
	D get_data() const
	{
		return data;
	}

	// Get next
	Node<D> *get_next() const
	{
		return next;
	}

	// Set the data
	void set_data(D data)
	{
		this->data = data;
	}

	// Set next
	void set_next(Node<D> *next)
	{
		this->next = next;
	}
};

template < typename D>
class Hash_table
{
	private:
	// Member variables
	Node<D> *table[MAX_SIZE];

	public:
	// Member functions
	static_assert(is_same<D, int>::value || is_same<D, string>::value, "Type must be int or string!");

 // Constructor
	Hash_table()
	{
		for (size_t i = 0; i < MAX_SIZE; i++)
		{
			table[i] = nullptr; //----------- Initialize each element to nullptr
		}
	}

	// Parameter constructor
	Hash_table(Node<D> *input_table)
	{
		for (size_t i = 0; i < MAX_SIZE; i++)
		{
			table[i] = input_table[i]; //---- Assign each element from the input_table to the corresponding element in the table array
		}
	}

	// Destructor
	~Hash_table()
	{
		delete_hash_table();
	}

	// Get the head of the table
	Node<D> *get_table() const
	{
		return table;
	}

	// Node exists
	Node<D> *check_if_node_exists(D data)
	{
		for (int i = 0; i < MAX_SIZE; i++)
		{
			Node<D> *trav_ptr = table[i];

			while (trav_ptr != nullptr)
			{
				if (trav_ptr->get_data() == data)
				{
					cerr << "\nNode with the same data already exists!" << endl;
					return trav_ptr;
				}
				trav_ptr = trav_ptr->get_next();
			}
		}
		return nullptr;
	}

	// Hash function for strings
	size_t hash_string_simpler(const string &input)
	{
		size_t hash = 0;
		size_t prime = 31;

		for (char c : input)
		{
			hash = hash * prime + c;
		}

		return hash % MAX_SIZE;
	}

	// Hash function for strings with mixed bits
	size_t hash_string(const string &input)
	{
		size_t hash = 0;

		for (char c : input)
		{
			// Mix the bits using bitwise operations
			hash ^= c + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		}

		return hash % MAX_SIZE;
	}

	// Hash function for integer
	size_t hash_integer(int input)
	{
		return (hash<int>{}(input)) % MAX_SIZE;
	}

	// Depending on what type of data we use do that hashing
	size_t get_hash(D data)
	{
		if constexpr (is_same<D, int>::value)
		{
			return hash_integer(data);
		}
		else if constexpr (is_same<D, string>::value)
		{
			return hash_string(data);
		}
	}

	// Prepend a node, aka add it at the front // NO CASES
	void insert_node(Node<D> *new_node)
	{
		size_t hash = get_hash(new_node->get_data());
		Node<D> *trav_ptr = table[hash];

		while (trav_ptr != nullptr) //----------------------------------------------------------------------------- Traverse the linked list at this hash index
		{
			if (trav_ptr->get_data() == new_node->get_data()) //--------------------------------------------------- If a node with the same data is found, disallow the insertion
			{
				cerr << "\nNode with the same data already exists!" << endl;
				delete new_node; //-------------------------------------------------------------------------------- Delete the new node as it's not used
				return;
			}
			trav_ptr = trav_ptr->get_next();
		}

		//--------------------------------------------------------------------------------------------------------- If no duplicates were found, insert the new node at the beginning of the linked list for this bucket
		new_node->set_next(table[hash]);
		table[hash] = new_node;

		cout << "\nNode: " << new_node << ": " << new_node->get_data() << " ---> " << new_node->get_next() << endl;
		cout << "\nHashed at location: " << hash << endl;
	}

	// Delete node by data // CASE 1: IF ITS THE FIRST NODE AND ITS THE ONLY NODE, CASE 2: IF ITS THE FIRST NODE AND THERE ARE MORE NODES, CASE 3: IF ITS ANY OTHER NODE
	void delete_node_by_data(D data)
	{
		size_t hash = get_hash(data);
		Node<D> *previous = nullptr;
		Node<D> *current = table[hash];

		while (current != nullptr)
		{
			if (current->get_data() == data)
			{
				if (previous == nullptr) //---------------------------------------------------------------------------- CASE 1: If the first node matches
				{
					if (current->get_next() == nullptr) //------------------------------------------------------------- CASE 1.1: If the list has only one element
					{
						table[hash] = nullptr; //---------------------------------------------------------------------- Set the list to point at nothing because there are no more nodes in the list
					}
					else //-------------------------------------------------------------------------------------------- CASE 1.2: If the list has more than one element
					{
						table[hash] = current->get_next(); //---------------------------------------------------------- Set the table bucket to point at the next node in the list
					}
				}
				else //------------------------------------------------------------------------------------------------ CASE 2: If a non-first node matches
				{
					previous->set_next(current->get_next());  //------------------------------------------------------- Set the previous node pointer to point at the node that the current pointer points at
				}
				cout << "\nNode at location - " << hash << ": " << current << " with data : " << data << " deleted!\n";
				delete current;
				return;
			}
			else //---------------------------------------------------------------------------------------------------- If the current node doesn't match go to the next nodes
			{
				previous = current;
				current = current->get_next();
			}
		}

		cerr << "\nThere is no node with that data: " << data << endl;
	}

	// Update node by data, when we change the data we delete the old and rehash the new, we must also check if a node with that data exists already in the table
	void update_node_by_data(Node<D> *new_data, D old_data)
	{
		size_t hash = get_hash(old_data);
		Node<D> *trav_ptr = table[hash];
		while (trav_ptr != nullptr)
		{
			if (trav_ptr->get_data() == old_data)
			{
				if (check_if_node_exists(new_data->get_data()) != nullptr)
				{
					delete new_data;
					return;
				}

				delete_node_by_data(old_data);
				insert_node(new_data);
				return;
			}
			trav_ptr = trav_ptr->get_next();
		}

		cout << "\nNo node found with that data!" << endl;
	}

	// Peek node by data
	D peek_node_by_data(D data)
	{
		size_t hash = get_hash(data);
		Node<D> *trav_ptr = table[hash];
		while (trav_ptr != nullptr)
		{
			if (trav_ptr->get_data() == data)
			{
				cout << "Hash: " << hash << " - ";
				return trav_ptr->get_data();
			}
			trav_ptr = trav_ptr->get_next();
		}

		cout << "\nNo node found with that data!" << endl;
		return D();
	}

	// Print hash table
	void print_hash_table() const
	{
		for (int i = 0; i < MAX_SIZE; i++)
		{
			Node<D> *trav_ptr = table[i];

			cout << "Bucket " << i << " : ";

			while (trav_ptr != nullptr)
			{
				cout << trav_ptr->get_data() << " ---> ";
				trav_ptr = trav_ptr->get_next();
			}

			cout << "NULL\n";
		}
	}

	// Delete table
	void delete_hash_table()
	{
		for (int i = 0; i < MAX_SIZE; i++)
		{
			Node<D> *trav_ptr = table[i];

			while (trav_ptr != nullptr)
			{
				Node<D> *temp = trav_ptr;
				trav_ptr = trav_ptr->get_next();
				delete temp;
			}

			table[i] = nullptr;
		}

		cout << "\nTable Deleted\n";
	}

	// Delete table recursive NOTE: you must adapt a reference pointer to the head if you wanna delete it recursive
	void delete_hash_table_recursive(Node<D> *&table)
	{
		for (int i = 0; i < MAX_SIZE; i++)
		{
			delete_linked_list_recursive(table[i]); // Delete each bucket
		}

		cout << "\nTable Deleted\n";
	}

	// Delete a single bucket
	void delete_linked_list_recursive(Node<D> *&head)
	{
		// Base case
		if (head == nullptr)
		{
			return;
		}
		// Recursive case
		delete_linked_list_recursive(head->get_next());
		delete head;
		head = nullptr;
	}

	// Create a node
	static Node<D> *create_node()
	{
		Node<D> *node = new Node<D>;
		cout << "\n================= Create node =================\n";
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
	Hash_table<string> table;
	int choice = 0;
	string key = "";
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
				cout << "Enter data of the node to be prepended\n";
				table.insert_node(Hash_table<string>::create_node());
				cout << "==========================================================\n";
				break;
			case 2:
				cout << "\n================= Delete node by data operation =================\n";
				// Change this if the data is not a integer type
				table.delete_node_by_data(get_valid_input<string>("Enter data of the node to be deleted: "));
				cout << "================================================================\n";
				break;
			case 3:
				cout << "\n================= Update node by data operation =================\n";
				// Change this if the data or data is not a integer type
				table.update_node_by_data(Hash_table<string>::create_node(), get_valid_input<string>("Enter old data to change: "));
				cout << "================================================================\n";
				break;
			case 4:
				cout << "\n================= Peek node by data operation =================\n";
				// Change this if the data is not a integer type
				key = get_valid_input<string>("Enter data of the node you want to peek: ");
				cout << table.peek_node_by_data(key) << endl;
				cout << "==============================================================\n";
				break;
			case 5:
				table.print_hash_table();
				break;
			case 6:
				cout << "\n================= Delete table operation =================\n";
				table.delete_hash_table();
				cout << "=========================================================\n";
				break;
			case 7:
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
	cout << "1. insert_node()" << endl;
	cout << "2. delete_node_by_data()" << endl;
	cout << "3. update_node_by_data()" << endl;
	cout << "4. peek_node_by_data()" << endl;
	cout << "5. print_hash_table()" << endl;
	cout << "6. delete_hash_table()" << endl;
	cout << "7. Clear Screen" << endl << endl;
}

// Get the choice for the menu
int get_choice()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 0 || choice > 7);
	return choice;
}