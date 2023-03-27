#include <iostream>
#include <fstream>
#include "basic_functions.h"

using namespace std;

// Functions
bool is_a_digit(string word_size);
void set_word_size(int word_size_int);
string get_guess(int WORDSIZE, string word_list_file_name);
bool check_if_word_exists(string guess, string word_list_file_name);
void set_initial_elements_to_zero(int WORDSIZE, int status[]);
void print_word(string guess, int WORDSIZE, int status[]);
int check_word(string guess, int WORDSIZE, int status[], string choice);
void print_end(bool won, string choice);

// Globals
const int LISTSIZE = 1000;

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
constexpr int EXACT = 2;
constexpr int CLOSE = 1;
constexpr int WRONG = 0;

// ANSI color codes for boxed in letters
constexpr auto GREEN = "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m";
constexpr auto YELLOW = "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m";
constexpr auto RED = "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m";
constexpr auto RESET = "\e[0;39m";

int WORDSIZE = 0;

int main(int argc, char *argv[])
{   //* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 2)
	{
		cerr << "Error 1: Too many or none arguments " << endl << "Usage: ./wordle [size of words]" << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}

	// Check if the word size is a digit
	string word_size = argv[1];
	if (!is_a_digit(word_size))
	{
		cerr << "Error 2: Enter a digit " << endl;
		return 2;
	}

	// Check if the word_size matches the given range
	int word_size_int = stoi(word_size);
	if (word_size_int < 5 || word_size_int > 8)
	{
		cerr << "Error 3: Must be 5, 6, 7 or 8" << endl;
		return 3;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	set_word_size(word_size_int); //------------------------------- Set word size

	string word_list_file_name = to_string(WORDSIZE) + ".txt"; //-- Open correct file, each file has exactly LISTSIZE words
	ifstream word_list(word_list_file_name);
	if (!word_list.is_open())
	{
		cerr << "Error opening file " << word_list_file_name << "." << endl;
		return 4;
	}

	string *options = new string[LISTSIZE]; //--------------------- Load word file into an array of size LISTSIZE
	for (int i = 0; i < LISTSIZE; i++)
	{
		word_list >> options[i];
	}

	srand(time(NULL)); //------------------------------------------ Pseudorandomly select a word for this game
	string choice = options[rand() % LISTSIZE];

	int guesses = WORDSIZE + 1; //--------------------------------- Allow one more guess than the length of the word
	bool won = false;

	cout << GREEN << "This is WORDLE50" << RESET << endl;
	cout << "You have " << guesses << " tries to guess the " << WORDSIZE << "-letter word I'm thinking of" << endl;
	cout << "DEBUG WORD: " << choice << endl;

	for (int i = 0; i < guesses; i++) //--------------------------- Main game loop
	{
		string guess = get_guess(WORDSIZE, word_list_file_name); // Obtain user's guess

		int *status = new int[WORDSIZE]; //------------------------ Array to hold guess status, initially set to zero

		set_initial_elements_to_zero(WORDSIZE, status); //--------- Set all elements of status array initially to 0, aka WRONGs

		int score = check_word(guess, WORDSIZE, status, choice); // Calculate score for the guess

		cout << "Guess " << i + 1 << ": ";

		print_word(guess, WORDSIZE, status); //-------------------- Print the guess

		if (score == EXACT * WORDSIZE) //------------------------ If they guessed it exactly right, terminate loop
		{
			won = true;
			break;
		}

		delete[] status; //---------------------------------------- Free up the allocated memory
	}

	print_end(won, choice); //------------------------------------- Print the games results

	delete[] options; //------------------------------------------- Free up the allocated memory
	word_list.close();//------------------------------------------- Close to free up memory

	return 0; //--------------------------------------------------- Success
}

// Check if all the characters are digits from argv[1]
bool is_a_digit(string word_size)
{
	int length = word_size.length();
	for (int i = 0; i < length; i++)
	{
		if (!isdigit(word_size[i]))
		{
			return false;
		}
	}
	return true;
}

// Set the word size base on the choice by the user
void set_word_size(int word_size_int)
{
	switch (word_size_int)
	{
		case 5:
		{
			WORDSIZE = 5;
			break;
		}
		case 6:
		{
			WORDSIZE = 6;
			break;
		}
		case 7:
		{
			WORDSIZE = 7;
			break;
		}
		case 8:
		{
			WORDSIZE = 8;
			break;
		}
		default:
		{
			cerr << "Error 3: Must be 5, 6, 7 or 8" << endl;
			break;
		}
	}
}

//* Get the guess and re-prompt the user to enter again if the word is not found and if its not the correct size ------------------------------------------
string get_guess(int WORDSIZE, string word_list_file_name)
{
	string guess = "";
	bool exists = false;
	int length = 0;
	do
	{
		guess = get_valid_input<string>("Enter guess: ");
		exists = check_if_word_exists(guess, word_list_file_name);
		length = guess.length();
	} while (length > WORDSIZE || length < WORDSIZE || !exists);
	return guess;
}

// Check if the word exists by going through all the words in the file and finding a match
bool check_if_word_exists(string guess, string word_list_file_name)
{
	string word = "";
	ifstream word_list(word_list_file_name);
	bool found = false;
	while (getline(word_list, word))
	{
		if (word == guess)
		{
			found = true;
			word_list.close();
			break;
		}
	}
	if (!found)
	{
		cout << "Word does not exist!" << endl;
	}
	word_list.close();
	return found;
}
//* Get the guess and re-prompt the user to enter again if the word is not found and if its not the correct size ------------------------------------------

// Initialize the status dynamic array to false
void set_initial_elements_to_zero(int WORDSIZE, int status[])
{
	for (int i = 0; i < WORDSIZE; i++)
	{
		status[i] = WRONG;
	}
}

// Print word character-for-character with correct color coding, then reset terminal font to normal
void print_word(string guess, int WORDSIZE, int status[])
{
	for (int i = 0; i < WORDSIZE; i++)
	{
		switch (status[i])
		{
			case EXACT:
			{
				cout << GREEN << guess[i] << RESET;
				break;
			}
			case CLOSE:
			{
				cout << YELLOW << guess[i] << RESET;
				break;
			}
			case WRONG:
			{
				cout << RED << guess[i] << RESET;
				break;
			}
		}
	}

	cout << endl;
}

// Compare guess to choice and score points as appropriate, storing points in status
int check_word(string guess, int WORDSIZE, int status[], string choice)
{
	int score = 0;
	bool *used_letter = new bool[WORDSIZE] //--------------- Initialize an array to keep track of which letters have been matched in the choice string
	{
		false
	};

	for (int i = 0; i < WORDSIZE; i++) //------------------- Iterate over each letter of the guess
	{
		for (int j = 0; j < WORDSIZE; j++) //--------------- Iterate over each letter of the choice
		{
			if (guess[i] == choice[j] && !used_letter[j]) // Compare the current guess letter to the current choice letter, and check if the letter in the choice string has already been used
			{
				if (i == j) //------------------------------ If they're the same position in the word, score EXACT points (green) and mark the letter as used
				{
					score += EXACT;
					status[i] = EXACT;
					used_letter[j] = true;
					break;
				}
				else //------------------------------------- If it's in the word, but not the right spot, score CLOSE points (yellow) and mark the letter as used
				{
					score += CLOSE;
					status[i] = CLOSE;
					used_letter[j] = true;
					break;
				}
			}
		}
	}

	cout << "DEBUG SCORE: " << score << endl;

	delete[] used_letter; //-------------------------------- Free up the allocated memory

	return score;
}

// Print the results of the game after the guesses
void print_end(bool won, string choice)
{
	if (won)
	{
		cout << GREEN << "YOU WIN!" << RESET << endl;
	}
	else
	{
		cout << RED << "YOU LOST!" << RESET << endl << "The word was: " << YELLOW << choice << RESET << endl;
	}
}