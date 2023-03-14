#include <iostream>
#include "basic_get_functions.h"

using namespace std;
string get_player_word();
int compare_words(string word);
void print_results(int score1, int score2);

int POINTS[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };

int main()
{
	// Get players input
	string word1 = get_player_word();
	string word2 = get_player_word();
	// Compare results
	int sum1 = compare_words(word1);
	int sum2 = compare_words(word2);
	// Print winner
	print_results(sum1, sum2);

	return 0;
}

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