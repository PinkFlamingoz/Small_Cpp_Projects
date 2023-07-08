#include <iostream>
#include <fstream>
#include "basic_functions.h"

using namespace std;

// Globals
constexpr int SIZE_OF_ALPHABET = 26;
constexpr int MAXCHAR = 20;

// Struct
struct Node
{
	bool is_word;
	Node *children[SIZE_OF_ALPHABET];
};

// Head of the trie
Node *head = new Node;

// Functions
bool check(string &name);
void delete_trie();
void delete_trie_recursive(Node *&node);

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 2)
	{
		cerr << "Error 1: Too many or none arguments " << endl << "Usage: ./dog_names [dog_names.txt]" << endl;
		return 1;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	//* Open files --------------------------------------------------------------------------------------------------------------------------------------------

	// Open input file
	ifstream input_file(argv[1]);
	if (!input_file.is_open())
	{
		cerr << "Error 2: Cant open file " << argv[1] << endl;
		return 2;
	}
	//* Open files --------------------------------------------------------------------------------------------------------------------------------------------

	//* Initialize head ---------------------------------------------------------------------------------------------------------------------------------------
	head->is_word = false;
	for (int i = 0; i < SIZE_OF_ALPHABET; i++)
	{
		head->children[i] = nullptr;
	}
	//* Initialize head ---------------------------------------------------------------------------------------------------------------------------------------

	//* Add words  --------------------------------------------------------------------------------------------------------------------------------------------
	string buffer = "";
	while (input_file >> buffer)
	{
		Node *trav_ptr = head;
		for (auto character : buffer)
		{
			int index = tolower(static_cast<unsigned char>(character)) - 'a';
			if (index < 0 || index >= SIZE_OF_ALPHABET)
			{
				cerr << "Invalid character in string: " << character << "\n";
				continue;
			}

			if (trav_ptr->children[index] == nullptr)
			{
				Node *new_name = new Node;
				new_name->is_word = false;
				for (int i = 0; i < SIZE_OF_ALPHABET; i++)
				{
					new_name->children[i] = nullptr;
				}
				trav_ptr->children[index] = new_name;
			}
			trav_ptr = trav_ptr->children[index];
		}
		trav_ptr->is_word = true;
	}
	//* Add words  --------------------------------------------------------------------------------------------------------------------------------------------

	string input_word = get_valid_input<string>("Check name: ");
	if (check(input_word))
	{
		cout << "Found!" << endl;
	}
	else
	{
		cout << "Not Found!" << endl;
	}

	delete_trie();
}

// Check if the word is in the trie
bool check(string &name)
{
	Node *trav_ptr = head;
	for (auto character : name)
	{
		int index = tolower(static_cast<unsigned char>(character)) - 'a';
		if (index < 0 || index >= SIZE_OF_ALPHABET)
		{
			cerr << "Invalid character in string: " << character << "\n";
			continue;
		}

		if (trav_ptr->children[index] == nullptr)
		{
			return false;
		}
		trav_ptr = trav_ptr->children[index];
	}

	return  trav_ptr != nullptr && trav_ptr->is_word;
}

// Delete the trie recursive
void delete_trie()
{
	delete_trie_recursive(head);
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
	for (int i = 0; i < SIZE_OF_ALPHABET; i++)
	{
		delete_trie_recursive(node->children[i]);
	}

	delete node;
	node = nullptr;
}