#include <iostream>
#include <cstring>
#include "basic_functions.h"

using namespace std;

// Structures
struct Candidate
{
	string name = "";
	int votes = 0;
};

// Globals
const int MAX = 10;
int candidate_count = 0;

Candidate candidates[MAX];

// Functions
void get_candidates(char *argv[]);
int get_number_of_voters();
void calculate_votes(int voter_count);
bool vote(string name);
void print_winner(void);
int get_max_vote();

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc < 3)
	{
		cerr << "Error 1: Enter more than two arguments " << endl << "Usage: ./plurality_vote [candidate ...]" << endl;
		return 1;
	}

	// Make sure the user does not enter more than the MAX candidates
	candidate_count = argc - 1;
	if (candidate_count > MAX)
	{
		cerr << "Error 2: Too many candidates the max is: " << MAX << endl;
		return 2;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	get_candidates(argv); //-------------------- Initialize the candidates structure array

	int voter_count = get_number_of_voters(); // Get the number of voters

	calculate_votes(voter_count); //------------ Calculate the votes

	print_winner(); //-------------------------- Print the winner

	return 0; //-------------------------------- Success
}

// Initialize the candidates structure array with the default values and the names from argv[]
void get_candidates(char *argv[])
{
	for (int i = 0; i < candidate_count; i++)
	{
		candidates[i].name = argv[i + 1];
		candidates[i].votes = 0;
	}
}

// Get the number of voters
int get_number_of_voters()
{
	int number = 0;
	do
	{
		number = get_valid_input<int>("Number of voters: ");
	} while (number < 1);
	return number;
}

//* Calculate votes and check if the vote is valid, if not don't count it ----------------------------------------------------------------------------------
void calculate_votes(int voter_count)
{
	for (int i = 0; i < voter_count; i++)
	{
		string name = get_valid_input<string>("Voter", "", i, "votes for: ");
		if (!vote(name))
		{
			cerr << "Invalid vote!" << endl;
		}
	}
}

// Record the vote by comparing the entered name with the candidate names in the pool of candidates and add one vote to the matching names
bool vote(string name)
{
	for (int i = 0; i < candidate_count; i++)
	{
		if (_stricmp(candidates[i].name.c_str(), name.c_str()) == 0)
		{
			candidates[i].votes += 1;
			return true;
		}
	}
	return false;
}
//* Calculate votes and check if the vote is valid, if not don't count it ----------------------------------------------------------------------------------

//* Print the winner/s that have the max vote -------------------------------------------------------------------------------------------------------------
void print_winner()
{
	int max = get_max_vote();
	for (int i = 0; i < candidate_count; i++)
	{
		if (max == candidates[i].votes)
		{
			cout << "Winner/s: " << candidates[i].name << endl;
		}
	}
}

// Get the max vote a candidate has
int get_max_vote()
{
	int max = candidates[0].votes;
	for (int i = 0; i < candidate_count; i++)
	{
		if (max < candidates[i].votes)
		{
			max = candidates[i].votes;
		}
	}
	return max;
}
//* Print the winner/s that have the max vote -------------------------------------------------------------------------------------------------------------