#include <iostream>
#include "basic_functions.h"

using namespace std;

// Functions
string get_player_word();
int compare_words(string word);
void print_results(int score1, int score2);

// Globals
int POINTS[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };

int main()
{
	string word1 = get_player_word(); // Get player 1 word
	string word2 = get_player_word(); // Get player 2 word

	int sum1 = compare_words(word1); //- Calculate points for player 1
	int sum2 = compare_words(word2); //- Calculate points for player 2

	print_results(sum1, sum2); //------- Print winner

	return 0; //------------------------ Success
}

//Get the player words and convert them to a upper case so its easy to work with
string get_player_word()
{
	string word = get_valid_input<string>("Enter word: ");
	int length = word.length();
	for (int i = 0; i < length; i++)
	{
		word[i] = toupper(word[i]);
	}
	return word;
}

// Calculate the points by adding the corresponding value of the points array to the sum,
// because the ASCII value of A = 65 we can subtract it by the character we have in the string word and we get the corresponding value of the point in the POINTS array
int compare_words(string word)
{
	int length = word.length();
	int sum = 0;
	for (int i = 0; i < length; i++)
	{
		if (isalpha(word[i]))
		{
			sum += POINTS[word[i] - 65];
		}
		else
		{
			sum += 0;
		}
	}
	return sum;
}

// Print who won
void print_results(int score1, int score2)
{
	if (score1 > score2)
	{
		cout << "Player one WINS!" << endl << "Player one score: " << score1 << endl << "Player two score: " << score2 << endl;
	}
	else if (score1 < score2)
	{
		cout << "Player two WINS!" << endl << "Player one score: " << score1 << endl << "Player two score: " << score2 << endl;;
	}
	else
	{
		cout << "TIE!" << endl << "Player one score: " << score1 << endl << "Player two score: " << score2 << endl;;
	}
}