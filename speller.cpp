// Implements a spell-checker
#include <cctype>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include "dictionary.h"

// Default dictionary
constexpr auto DICTIONARY = "dictionaries/large.txt";

// Functions
double calculate(chrono::high_resolution_clock::time_point start, chrono::high_resolution_clock::time_point end);

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 2 && argc != 3)
	{
		cerr << "Error 1: Too many or none arguments " << endl << "Usage: ./speller [DICTIONARY] [TEXT.txt]" << endl;
		return 1;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	// Benchmarks
	double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;

	//* Open files --------------------------------------------------------------------------------------------------------------------------------------------

	// Determine dictionary to use
	string dictionary = (argc == 3) ? argv[1] : DICTIONARY;

	// Load dictionary
	auto start = chrono::high_resolution_clock::now();
	bool loaded = load(dictionary);
	auto end = chrono::high_resolution_clock::now();
	time_load = calculate(start, end);

	// Exit if dictionary not loaded
	if (!loaded)
	{
		cerr << "ERROR IN MAIN, Could not load " << dictionary << endl;
		return 1;
	}

	// Try to open text
	char *text = (argc == 3) ? argv[2] : argv[1];
	ifstream file(text);
	if (!file)
	{
		cerr << "ERROR IN TEXT, Could not open " << text << endl;
		unload();
		return 1;
	}
	//* Open files --------------------------------------------------------------------------------------------------------------------------------------------

	// Prepare to report misspellings
	cout << "\nMISSPELLED WORDS\n\n";

	// Prepare to spell-check
	int index = 0, misspellings = 0, words = 0;
	string word;

	// Spell-check each word in text
	while (file >> word)
	{
		// Ignore words with numbers
		if (any_of(word.begin(), word.end(), ::isdigit))
		{
			continue;
		}

		// Update counter
		words++;

		// Check word's spelling
		start = chrono::high_resolution_clock::now();
		bool misspelled = !check(word.c_str());
		end = chrono::high_resolution_clock::now();
		time_check += calculate(start, end);

		// Print word if misspelled
		if (misspelled)
		{
			cout << word << endl;
			misspellings++;
		}
	}

	// Close text
	file.close();

	// Determine dictionary's size
	start = chrono::high_resolution_clock::now();
	size_t n = size();
	end = chrono::high_resolution_clock::now();
	time_size = calculate(start, end);

	// Unload dictionary
	start = chrono::high_resolution_clock::now();
	bool unloaded = unload();
	end = chrono::high_resolution_clock::now();
	time_unload = calculate(start, end);

	// Abort if dictionary not unloaded
	if (!unloaded)
	{
		cerr << "Could not unload " << dictionary << endl;
		return 1;
	}

	// Report benchmarks
	cout << "\nWORDS MISSPELLED:   " << misspellings << endl;
	cout << "WORDS IN DICTIONARY:  " << n << endl;
	cout << "WORDS IN TEXT:        " << words << endl;
	cout << "TIME IN load:         " << time_load << endl;
	cout << "TIME IN check:        " << time_check << endl;
	cout << "TIME IN size:         " << time_size << endl;
	cout << "TIME IN unload:       " << time_unload << endl;
	cout << "TIME IN TOTAL:        " << time_load + time_check + time_size + time_unload << endl;

	// Success
	return 0;
}

// Calculate time duration in seconds
double calculate(chrono::high_resolution_clock::time_point start, chrono::high_resolution_clock::time_point end)
{
	chrono::duration<double> diff = end - start;
	return diff.count();
}