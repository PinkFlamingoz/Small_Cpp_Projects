#include <iostream>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

// each of our text files contains 1000 words
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

// GLOBALS
int WORDSIZE = 0;

// FUNCTIONS
bool is_a_digit(string worldsize);
void set_word_size(int worldsize_int);
string get_guess(int WORDSIZE, string wl_filename);
bool check_if_word_exists(string guess, string wl_filename);
void set_initial_elements_to_zero(int WORDSIZE, int status[]);
void print_word(string guess, int WORDSIZE, int status[]);
int check_word(string guess, int WORDSIZE, int status[], string choice);
void print_end(bool won, string choice);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Error 1: Too many or none arguments " << endl << "Usage: ./wordle (size of words)" << endl;
		return 1;
	}
	string worldsize = argv[1];
	if (!is_a_digit(worldsize))
	{
		cout << "Error 2: Enter a digit " << endl;
		return 1;
	}
	int worldsize_int = stoi(worldsize);
	if (worldsize_int < 5 || worldsize_int > 8)
	{
		cout << "Error 3: Must be 5, 6, 7 or 8" << endl;
		return 1;
	}
	else
	{
		// Set word size
		set_word_size(worldsize_int);

		// open correct file, each file has exactly LISTSIZE words
		string wl_filename = to_string(WORDSIZE) + ".txt";
		ifstream wordlist(wl_filename);
		if (!wordlist.is_open())
		{
			cout << "Error opening file " << wl_filename << "." << endl;
			return 1;
		}

		// load word file into an array of size LISTSIZE
		string* options = new string[LISTSIZE];
		for (int i = 0; i < LISTSIZE; i++)
		{
			wordlist >> options[i];
		}

		// pseudorandomly select a word for this game
		srand(time(NULL));
		string choice = options[rand() % LISTSIZE];

		// allow one more guess than the length of the word
		int guesses = WORDSIZE + 1;
		bool won = false;

		// print greeting, using ANSI color codes to demonstrate
		cout << GREEN << "This is WORDLE50" << RESET << endl;
		cout << "You have " << guesses << " tries to guess the " << WORDSIZE << "-letter word I'm thinking of" << endl;

		cout << "DEBUG WORD: " << choice << endl;
		// main game loop, one iteration for each guess
		for (int i = 0; i < guesses; i++)
		{
			// obtain user's guess
			string guess = get_guess(WORDSIZE, wl_filename);

			// array to hold guess status, initially set to zero
			int* status = new int[WORDSIZE];

			// set all elements of status array initially to 0, aka WRONG
			set_initial_elements_to_zero(WORDSIZE, status);

			// Calculate score for the guess
			int score = check_word(guess, WORDSIZE, status, choice);

			cout << "Guess " << i + 1 << ": ";

			// Print the guess
			print_word(guess, WORDSIZE, status);

			// if they guessed it exactly right, terminate loop
			//if (score == EXACT * WORDSIZE)
			if (guess == choice)
			{
				won = true;
				break;
			}
		}
		// Print the game's result
		print_end(won, choice);

		delete[] options;
		// that's all folks!
		return 0;
	}
}

template <typename T>
T get_valid_input(const string& prompt)
{
	T input;
	while (true)
	{
		cout << prompt;
		cin >> input;
		if (cin.fail())
		{
			// Input is not valid
			cout << "Error: Please enter a valid input." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			// Input is valid
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}
	return input;
}

template<>
string get_valid_input<string>(const string& prompt)
{
	string input;
	while (true)
	{
		cout << prompt;
		getline(cin, input);
		if (cin.fail() || input.empty())
		{
			// Input is not valid
			cout << "Error: Please enter a valid input." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			// Input is valid
			break;
		}
	}
	return input;
}

bool is_a_digit(string worldsize)
{
	int length = worldsize.length();
	for (int i = 0; i < length; i++)
	{
		if (!isdigit(worldsize[i]))
		{
			return false;
		}
	}
	return true;
}

void set_word_size(int worldsize_int)
{
	switch (worldsize_int)
	{
	case 5:
		WORDSIZE = 5;
		break;
	case 6:
		WORDSIZE = 6;
		break;
	case 7:
		WORDSIZE = 7;
		break;
	case 8:
		WORDSIZE = 8;
		break;

	default:
		cout << "Error 3: Must be 5, 6, 7 or 8" << endl;
		break;
	}
}

string get_guess(int WORDSIZE, string wl_filename)
{
	string guess;
	bool exists = false;
	int length = 0;
	do
	{
		guess = get_valid_input<string>("Enter guess: ");
		exists = check_if_word_exists(guess, wl_filename);
		length = guess.length();
	} while (length > WORDSIZE || length < WORDSIZE || !exists);

	return guess;
}
bool check_if_word_exists(string guess, string wl_filename)
{
	string word;
	ifstream wordlist(wl_filename);
	bool found = false;
	while (getline(wordlist, word))
	{
		if (word == guess)
		{
			found = true;
			break;
		}
	}
	if (found == false)
	{
		cout << "Word does not exist!" << endl;
	}
	return found;
}

void set_initial_elements_to_zero(int WORDSIZE, int status[])
{
	for (int i = 0; i < WORDSIZE; i++)
	{
		status[i] = WRONG;
	}
}

void print_word(string guess, int WORDSIZE, int status[])
{
	// print word character-for-character with correct color coding, then reset terminal font to normal

	for (int i = 0; i < WORDSIZE; i++)
	{
		switch (status[i])
		{
		case EXACT:
			cout << GREEN << guess[i] << RESET;
			break;
		case CLOSE:
			cout << YELLOW << guess[i] << RESET;
			break;
		case WRONG:
			cout << RED << guess[i] << RESET;
			break;
		}
	}

	cout << endl;
}

int check_word(string guess, int WORDSIZE, int status[], string choice)
{
	int score = 0;

	// compare guess to choice and score points as appropriate, storing points in status

	// HINTS
	// iterate over each letter of the guess
		// iterate over each letter of the choice
			// compare the current guess letter to the current choice letter
				// if they're the same position in the word, score EXACT points (green) and break so you don't compare that letter further
				// if it's in the word, but not the right spot, score CLOSE point (yellow)
		// keep track of the total score by adding each individual letter's score from above

	for (int i = 0; i < WORDSIZE; i++)
	{
		for (int j = 0; j < WORDSIZE; j++)
		{
			if (guess[i] == choice[j])
			{
				if (i == j)
				{
					score += EXACT;
					status[i] = EXACT;
					break;
				}
				score += CLOSE;
				status[i] = CLOSE;
			}
		}
	}
	cout << "DEBUG SCORE: " << score << endl;

	return score;
}

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