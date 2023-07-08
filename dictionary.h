// Declares a dictionary's functionality
#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
constexpr unsigned int LENGTH = 45;

// Struct
struct Node
{
	string word;
	Node *next;
};

// Choose number of buckets in hash table
const unsigned int N = 999983;

// Hash table
Node *table[N] = { nullptr };

// Total number of words in dictionary
int total_number_of_words_in_dictionary = 0;

// Hashes word to a number
// Hash function for strings with mixed bits
size_t hash_string(const string &input)
{
	size_t hash = 0;

	for (char c : input)
	{
		// Mix the bits using bitwise operations
		hash ^= c + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	}

	return hash % N;
}

// Returns true if word is in dictionary, else false
bool check(const string &word)
{
	size_t hash_key = hash_string(word);
	Node *trav_ptr = table[hash_key];

	string to_lower_word = word;
	transform(to_lower_word.begin(), to_lower_word.end(), to_lower_word.begin(), ::tolower);

	while (trav_ptr != nullptr)
	{
		string to_lower_node_word = trav_ptr->word;
		transform(to_lower_node_word.begin(), to_lower_node_word.end(), to_lower_node_word.begin(), ::tolower);

		if (to_lower_node_word == to_lower_word)
		{
			return true;
		}
		trav_ptr = trav_ptr->next;
	}
	return false;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const string &dictionary)
{
	ifstream in_file(dictionary);
	if (!in_file)
	{
		cerr << "Error opening file! ERROR IN LOAD!" << endl;
		return false;
	}

	string word;

	while (in_file >> word)
	{
		total_number_of_words_in_dictionary++;

		size_t hash_key = hash_string(word);

		Node *new_word = new Node();
		new_word->word = word;
		new_word->next = table[hash_key];
		table[hash_key] = new_word;
	}

	in_file.close();

	return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
size_t size(void)
{
	return total_number_of_words_in_dictionary;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
	for (int i = 0; i < N; i++)
	{
		Node *trav_ptr = table[i];
		while (trav_ptr != nullptr)
		{
			Node *temp = trav_ptr;
			trav_ptr = trav_ptr->next;
			delete temp;
		}

		table[i] = nullptr;
	}
	return true;
}
