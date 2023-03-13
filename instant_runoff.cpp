#include <iostream>
#include <cstring>
#include <D:\Xixijan\repos\Small_C++_Projects\basic_get_functions.h>

using namespace std;

struct Candidate
{
	string name = "";
	int votes = 0;
	bool eliminated = false;
};

const int MAX_CANDIDATES = 9;
const int MAX_VOTERS = 100;

Candidate candidates[MAX_CANDIDATES];
int preferences[MAX_VOTERS][MAX_CANDIDATES];

int candidate_count = 0;
int voter_count = 0;

void get_candidates(char* argv[]);
int get_number_of_voters();
int caluclate_vote();
void vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner();
int find_min();
bool is_tie(int min);
void eliminate(int min);
void print_tie();
void reset_vote_count();

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Error 1: Too many or none arguments " << endl << "Usage: ./plurality_vote [candidate ...]" << endl;
		return 1;
	}
	candidate_count = argc - 1;
	if (candidate_count > MAX_CANDIDATES)
	{
		cout << "Error 2: Too many candidates the max is: " << MAX_CANDIDATES << endl;
		return 2;
	}
	else
	{
		get_candidates(argv);
		voter_count = get_number_of_voters();
		if (voter_count > MAX_VOTERS)
		{
			cout << "Error 3: Maximum number of voter is: " << MAX_VOTERS << endl;
			return 3;
		}

		caluclate_vote();

		while (true)
		{
			// Calculate votes given remaining candidates
			tabulate();

			// Check if election has been won
			bool won = print_winner();
			if (won)
			{
				break;
			}

			// Eliminate last-place candidates
			int min = find_min();
			bool tie = is_tie(min);

			// If tie, everyone wins
			if (tie)
			{
				print_tie();
				break;
			}

			// Eliminate anyone with minimum number of votes
			eliminate(min);

			// Reset vote counts back to zero
			reset_vote_count();
		}
		return 0;
	}
}

void get_candidates(char* argv[])
{
	for (int i = 0; i < candidate_count; i++)
	{
		candidates[i].name = argv[i + 1];
		candidates[i].votes = 0;
		candidates[i].eliminated = false;
	}
}

int get_number_of_voters()
{
	int number = 0;
	do
	{
		number = get_valid_input<int>("Number of voters: ");
	} while (number < 1);
	return number;
}

int caluclate_vote()
{
	for (int i = 0; i < voter_count; i++)
	{
		cout << "Voter " << i << ": " << endl;
		// Query for each rank
		for (int j = 0; j < candidate_count; j++)
		{
			string name;
			bool valid_name = false;
			while (!valid_name)
			{
				name = get_valid_input<string>("Enter vote preference", "", -1, "", j);
				valid_name = false;
				for (int c = 0; c < candidate_count; c++)
				{
					if (name == candidates[c].name)
					{
						valid_name = true;
						break;
					}
				}
				if (!valid_name)
				{
					cout << "Error: Invalid candidate name." << endl;
				}
			}
			// Record vote
			vote(i, j, name);
		}
		cout << endl;
	}
	return 0;
}

void vote(int voter, int rank, string name)
{
	for (int i = 0; i < candidate_count; i++)
	{
		if (strcmp(candidates[i].name.c_str(), name.c_str()) == 0)
		{
			preferences[voter][rank] = i;
		}
	}
}

void tabulate()
{
	for (int i = 0; i < voter_count; i++)
	{
		int pointer = 0;
		for (int j = 0; j < candidate_count; j++)
		{
			if ((preferences[i][pointer] == j) && (candidates[j].eliminated == false))
			{
				candidates[j].votes++;
				break;
			}
			if ((preferences[i][pointer] == j) && (candidates[j].eliminated == true))
			{
				while (candidates[preferences[i][pointer]].eliminated == true)
				{
					pointer++;
				}
				candidates[preferences[i][pointer]].votes++;
				break;
			}
		}
	}
}

bool print_winner()
{
	int max = candidates[0].votes;
	int index_of_winner = 0;
	for (int i = 0; i < candidate_count; i++)
	{
		if (max < candidates[i].votes)
		{
			max = candidates[i].votes;
			index_of_winner = i;
		}
	}
	if (max > (voter_count / 2))
	{
		cout << "Winner/s: " << candidates[index_of_winner].name << endl;
		return true;
	}
	return false;
}

int find_min()
{
	int min = candidates[0].votes;
	for (int i = 0; i < candidate_count; i++)
	{
		if (candidates[i].eliminated == false)
		{
			if (min > candidates[i].votes)
			{
				min = candidates[i].votes;
			}
		}
	}
	return min;
}

bool is_tie(int min)
{
	for (int i = 0; i < candidate_count; i++)
	{
		if ((candidates[i].votes != min) && (candidates[i].eliminated == false))
		{
			return false;
		}
	}
	return true;
}

void eliminate(int min)
{
	for (int i = 0; i < candidate_count; i++)
	{
		if ((min == candidates[i].votes) && (candidates[i].eliminated == false))
		{
			candidates[i].eliminated = true;
		}
	}
}

void print_tie()
{
	for (int i = 0; i < candidate_count; i++)
	{
		if (!candidates[i].eliminated)
		{
			cout << candidates[i].name << endl;
		}
	}
}

void reset_vote_count()
{
	for (int i = 0; i < candidate_count; i++)
	{
		candidates[i].votes = 0;
	}
}