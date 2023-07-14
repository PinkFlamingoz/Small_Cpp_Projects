#include <iostream>
#include "headers/basic_functions.h"

using namespace std;
// - Tries
//  - Insertion is complex - a lot of dynamic memory allocation, but gets easier as you go
//  - Deletion is easy - just free a node
//  - Lookup is fast - not quite as fast as an array, but almost
//  - Already sorted - sorts as you build in almost all situations
//  - Rapidly becomes huge, even with very little data present, not great if space is at a premium
//
// Tries combine structures and pointers together to store data in an interesting way.
// - The data to be searched for in the trie is now a roadmap.
// - If you can follow the map from beginning to end, the data exists in the trie.
// - If you can't, it doesn't.
// - Unlike with a hash table, there are no collisions, and no two pieces of data (unless they are identical) have the same path.

// Globals
constexpr int MAX_SIZE = 95;
constexpr int INDEX_RANGE = 32;
constexpr int SPACE = 40;

// Classes
class Node
{
	private:
	// Member variables
	bool end_of_data;
	Node *children[MAX_SIZE];

	public:
	// Member functions

	// Constructor
	Node()
	{
		end_of_data = false;
		for (int i = 0; i < MAX_SIZE; i++)
		{
			children[i] = nullptr;
		}
	}

	// Get the end_of_data
	bool get_end_of_data() const
	{
		return end_of_data;
	}

	// Get children
	Node **get_children()
	{
		return children;
	}

	// Get specific child
	Node *&get_child(int index)
	{
		return children[index];
	}

	// Set the end_of_data
	void set_end_of_data(bool end_of_data)
	{
		this->end_of_data = end_of_data;
	}

	// Set specific child
	void set_child(int index, Node *child)
	{
		this->children[index] = child;
	}
};

class Trie
{
	private:
	// Member variables
	Node *head;

	public:
	// Member functions

	// Constructor
	Trie()
	{
		head = new Node();
	}

	// Destructor
	~Trie()
	{
		delete_trie_recursive(head);
	}

	// Get the head of the trie
	Node *&get_head_of_trie()
	{
		return head;
	}

	// Check if node is empty
	bool is_empty(Node *&node)
	{
		for (int i = 0; i < MAX_SIZE; i++)
		{
			if (node->get_child(i) != nullptr)
			{
				return false;
			}
		}
		return true;
	}

	// Insert a word into the trie
	void insert_word(const string &word)
	{
		Node *node = head;
		for (char c : word)
		{
			int index = c - INDEX_RANGE; //-------- Handles ASCII 32 to 126
			if (node->get_child(index) == nullptr)
			{
				node->set_child(index, new Node());
			}
			node = node->get_child(index);
		}
		node->set_end_of_data(true);
	}

	// Search for a word in the trie
	bool search(const string &word)
	{
		Node *node = head;
		for (char c : word)
		{
			int index = c - INDEX_RANGE;
			if (node->get_child(index) == nullptr)
			{
				return false;
			}
			node = node->get_child(index);
		}
		return node != nullptr && node->get_end_of_data();
	}

	// Delete a word from the trie
	bool delete_word(const string &word)
	{
		// Call the helper function that does the actual recursive deletion
		// Start from the head of the trie and at depth 0 (the first character of the word)
		return delete_word_helper(head, word, 0);
	}

	// Recursive helper function to delete a word
	bool delete_word_helper(Node *&node, const string &word, int depth)
	{
		// Base case: If the node is null, we've encountered an empty space where the word should've been (the word is not in the trie)
		if (node == nullptr)
		{
			return false;
		}

		if (depth == word.size()) //-------------------------------------------------- If we've reached the depth equal to word length, we're at the end of the word
		{
			if (node->get_end_of_data()) //------------------------------------------- If the current node marks the end of a word
			{
				node->set_end_of_data(false); //-------------------------------------- Set end of data to false, indicating there's no word ending here anymore

				if (is_empty(node) && node != head) //-------------------------------- If the node has no child nodes (i.e., it is empty)
				{
					delete node; //--------------------------------------------------- Delete the node and set it to nullptr, freeing up memory and removing the word from the trie
					node = nullptr;
					cout << "Letter deleted!" << endl;
					return true; //--------------------------------------------------- Return true indicating the word was successfully deleted
				}
				cout << "Word contains children, end of data is set to false" << endl;
				return false; //------------------------------------------------------ If the node is not empty (it is part of another word), just return false
			}
		}
		// Recursive case: We're not at the end of the word yet
		else
		{
			int index = word[depth] - INDEX_RANGE; //--------------------------------- Calculate the index in the array of children based on the ASCII value of the current character
			if (delete_word_helper(node->get_child(index), word, depth + 1)) //------- Recursively call the delete function for the child node corresponding to the current character
			{
				node->set_child(index, nullptr); //----------------------------------- If the child node was successfully deleted, set the corresponding child pointer to nullptr

				if (!node->get_end_of_data() && is_empty(node) && node != head) //---- If the current node is empty (has no children) and does not represent the end of a word
				{
					delete node; //--------------------------------------------------- Delete the current node and set it to nullptr, pruning the trie
					node = nullptr;
					cout << "Letter deleted!" << endl;
					return true; //--------------------------------------------------- Return true indicating the deletion was successful
				}
				cout << "Word contains children, child is set to nullptr" << endl;
				return false; //------------------------------------------------------ If the current node is not empty (it is part of another word), just return false
			}
		}
		cout << "Letter is linked" << endl;
		return false; //-------------------------------------------------------------- If we haven't found the word to delete, return false
	}

	// Print the trie
	void print_all_words(Node *node, string word = "")
	{
		// Base case
		if (node == nullptr)
		{
			return;
		}

		if (node->get_end_of_data())
		{
			cout << word << endl; //---------------------- If it's the end of a word, print the word
		}
		// Recursive case
		for (int i = 0; i < MAX_SIZE; i++)
		{
			char c = i + INDEX_RANGE; //------------------ Convert the index back to a character
			print_all_words(node->get_child(i), word + c);
		}
	}

	// Print the Trie
	void print_trie_connections(Node *node, string word = "", int depth = 0)
	{
		// Base case
		if (node == nullptr)
		{
			return;
		}

		for (int i = 0; i < depth; ++i) //---------------------------------- Print indentation proportional to the depth
		{
			cout << "---";
		}

		cout << "> " << word; //-------------------------------------------- Print the current word

		if (node->get_end_of_data()) //------------------------------------- Print if this node is end of a word
		{
			cout << " [end of word]";
		}

		cout << endl;
		// Recursive case
		for (int i = 0; i < MAX_SIZE; i++)
		{
			char c = i + INDEX_RANGE; //------------------------------------ Convert the index back to a character
			print_trie_connections(node->get_child(i), word + c, depth + 1);
		}
	}

	// Print spaces for 2D trie
	void print_spaces(int space) const
	{
		for (int i = SPACE; i < space; i++)
		{
			cout << " ";
		}
	}

	// Print a trie in 2D
	void print_trie_2D(Node *node, int space)
	{
		// Base case
		if (node == nullptr)
		{
			return;
		}

		// Recursive case
		space += SPACE;

		for (int i = MAX_SIZE - 1; i >= 0; i--)
		{
			Node *child = node->get_child(i);
			print_trie_2D(child, space);

			if (child != nullptr)
			{
				cout << endl;
				print_spaces(space);
				char c = i + INDEX_RANGE;
				cout << node << " -> child index[" << i << "]: " << c;
				if (child->get_end_of_data())
				{
					cout << " [end of a word]";
				}
				cout << endl;
			}
		}
	}

	// Delete the trie recursive
	void delete_trie()
	{
		delete_trie_recursive(head);
		head = new Node(); //------- We must reset the head to point at a empty trie, because in the recursive function we delete and set the head to point at nothing when we try to enter a new node after this we get a error if we don't reset the head
	}

	// Delete the trie recursive
	void delete_trie_recursive(Node *&node)
	{
		// Base case
		if (node == nullptr)
		{
			return;
		}

		// Recursive case
		for (int i = 0; i < MAX_SIZE; i++)
		{
			delete_trie_recursive(node->get_child(i));
		}

		delete node;
		node = nullptr;
	}
};

// Functions
void print_menu();
int get_choice();

int main()
{
	Trie t1;
	int choice = 0;
	do
	{
		print_menu();
		choice = get_choice();
		switch (choice)
		{
			case 0:
				break;
			case 1:
				cout << "\n================= Insert =================\n";
				t1.insert_word(get_valid_input<string>("Enter data of the node to be inserted: "));
				cout << "Word inserted!" << endl;
				cout << "==========================================================\n";
				break;
			case 2:
				cout << "\n================= Search =================\n";
				if (t1.search(get_valid_input<string>("Enter data of the node: ")))
				{
					cout << "Word found!" << endl;
				}
				else
				{
					cout << "No word found!" << endl;
				}
				cout << "==============================================================\n";
				break;
			case 3:
				cout << "\n================= Delete =================\n";
				t1.delete_word(get_valid_input<string>("Enter data of the node to be deleted: "));
				cout << "Word deleted!" << endl;
				cout << "================================================================\n";
				break;
			case 4:
				t1.print_all_words(t1.get_head_of_trie());
				break;
			case 5:
				t1.print_trie_connections(t1.get_head_of_trie());
				break;
			case 6:
				t1.print_trie_2D(t1.get_head_of_trie(), 5);
				break;
			case 7:
				cout << "\n================= Delete trie =================\n";
				t1.delete_trie();
				cout << "Trie deleted!" << endl;
				cout << "=========================================================\n";
				break;
			case 8:
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
	cout << "1. insert()" << endl;
	cout << "2. search()" << endl;
	cout << "3. delete()" << endl;
	cout << "4. print_all_words()" << endl;
	cout << "5. print_trie_connections()" << endl;
	cout << "6. print_trie_2D()" << endl;
	cout << "7. delete_tire_recursive()" << endl;
	cout << "8. Clear Screen" << endl << endl;
}

// Get the choice for the menu
int get_choice()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 0 || choice > 8);
	return choice;
}