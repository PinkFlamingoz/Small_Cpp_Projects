#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include "basic_functions.h"

using namespace std;

// Globals
const int MAX_CANDIDATES = 9;
const int MAX_VOTERS = 100;

Candidate candidates[MAX_CANDIDATES];
int preferences[MAX_VOTERS][MAX_CANDIDATES];

int candidate_count = 0;
int voter_count = 0;

// Structures
struct Candidate
{
	string name = "";
	int votes = 0;
	bool eliminated = false;
};

// Functions
bool check_if_candidates_are_different(int argc, char *argv[]);
int get_number_of_voters();
void get_candidates(char *argv[]);
void set_voter_preferences();
string check_if_ranked(string name, int j, vector<string> &ranked_candidates);
string get_cast_vote(string name, int j);
bool check_correct_vote_cast(bool valid_name, string name);
void vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner();
void find_max(int &max, int &index_of_winner);
int find_min();
bool is_tie(int min);
void eliminate(int min);
void print_tie();
void reset_vote_count();

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc < 2)
	{
		cerr << "Error 1: Too many or none arguments " << endl << "Usage: ./plurality_vote [candidate ...]" << endl;
		return 1;
	}

	// Check if the user does not go over the limit of candidates
	candidate_count = argc - 1;
	if (candidate_count > MAX_CANDIDATES)
	{
		cerr << "Error 2: Too many candidates the max is: " << MAX_CANDIDATES << endl;
		return 2;
	}

	// Check if all the candidates are random
	bool all_random = check_if_candidates_are_different(argc, argv);
	if (!all_random)
	{
		cerr << "Error 3: Candidates must not have the same name! " << endl;
		return 3;
	}

	// Check if the user does not go over the number of voters
	voter_count = get_number_of_voters();
	if (voter_count > MAX_VOTERS)
	{
		cerr << "Error 4: Maximum number of voter is: " << MAX_VOTERS << endl;
		return 4;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	get_candidates(argv); //--------- Initialize the candidates structure array

	set_voter_preferences(); //------ Set for each voter their preference in the preferences array example Voter[0] has candidates in order [{1, 2, 0, 3}]

	while (true) //------------------ Do this until a winner is found
	{
		tabulate(); //--------------- Calculate votes given remaining candidates

		bool won = print_winner(); // Check if election has been won and if so print the winner
		if (won)
		{
			break;
		}

		int min = find_min(); //----- Find the candidate with the minimum votes

		bool tie = is_tie(min); //--- If tie, everyone wins
		if (tie)
		{
			print_tie(); //---------- Print the winners
			break;
		}

		eliminate(min); //----------- Eliminate anyone with minimum number of votes

		reset_vote_count(); //------- Reset vote counts back to zero
	}

	return 0; // -------------------- Success
}

// Check if the user entered all random candidates by comparing the first candidate with the rest and then the second with the rest, skipping the first comparison. Repeat the same process for each candidate
bool check_if_candidates_are_different(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		for (int j = i + 1; j < argc; j++)
		{
			if (_stricmp(argv[i], argv[j]) == 0)
			{
				return false;
			}
		}
	}
	return true;
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

// Initialize the candidates structure array with the default values and the names from argv[]
void get_candidates(char *argv[])
{
	for (int i = 0; i < candidate_count; i++)
	{
		candidates[i].name = argv[i + 1];
		candidates[i].votes = 0;
		candidates[i].eliminated = false;
	}
}

//* Set the voters preference -----------------------------------------------------------------------------------------------------------------------------
void set_voter_preferences()
{
	for (int i = 0; i < voter_count; i++) //---------------------- Keep querying for votes
	{
		cout << "Voter " << i << ": " << endl;

		vector<string> ranked_candidates; //---------------------- Vector array to keep track of already ranked candidates

		for (int j = 0; j < candidate_count; j++) //-------------- Query for each rank
		{
			string name;
			name = check_if_ranked(name, j, ranked_candidates); // Get the name and check if thats a valid enter

			vote(i, j, name); //---------------------------------- Record vote
		}
		cout << endl;
	}
}

// Check if the candidate has already been ranked by making a temporary vector array and pushing each rank in it as the voter votes, reset the vector array for the new voter
string check_if_ranked(string name, int j, vector<string> &ranked_candidates)
{
	bool valid_vote = false;
	while (!valid_vote)
	{
		name = get_cast_vote(name, j); //---------------------------------------------------------------- Get the name of the candidate to check
		transform(name.begin(), name.end(), name.begin(), ::tolower);
		if (find(ranked_candidates.begin(), ranked_candidates.end(), name) != ranked_candidates.end()) // Find returns the value of the last pushed element if the element we are searching for is not found
		{
			cerr << "Error: Candidate already ranked." << endl;
		}
		else
		{
			ranked_candidates.push_back(name);
			valid_vote = true;
		}
	}
	return name;
}

// Get the name of the candidate to vote for
string get_cast_vote(string name, int j)
{
	bool valid_name = false;
	while (!valid_name)
	{
		name = get_valid_input<string>("Enter vote preference", "", -1, "", j);
		valid_name = check_correct_vote_cast(valid_name, name); //------------- Check if the candidate name is in the pool of candidates to vote for
		if (!valid_name)
		{
			cerr << "Error: Invalid candidate name." << endl;
		}
	}
	return name;
}

// Check if the candidate name is in the pool of candidates to vote for by comparing the name with each of the candidate names in the pool
bool check_correct_vote_cast(bool valid_name, string name)
{
	for (int i = 0; i < candidate_count; i++)
	{
		if (_stricmp(candidates[i].name.c_str(), name.c_str()) == 0)
		{
			return valid_name = true;
		}
	}
	return valid_name = false;
}

// Record the vote by comparing the entered name with the candidate names in the pool of candidates and record it in the preferences array example voter[0]has ranked[{1, 2, 0, 3}]
void vote(int voter, int rank, string name)
{
	for (int i = 0; i < candidate_count; i++)
	{
		if (_stricmp(candidates[i].name.c_str(), name.c_str()) == 0)
		{
			preferences[voter][rank] = i;
			break; //---------------------------------------------- When we have the correct vote break out of the cycle
		}
	}
}
//* Set the voters preference -----------------------------------------------------------------------------------------------------------------------------

// Calculate votes given remaining candidates, we use a pointer to keep track of which candidates are eliminated and their votes go to the next preference
//
// Example Candidates A = 0, B = 1, C = 2;
//
// preferences[0][1, 2, 0]
// preferences[1][2, 1, 0]
// preferences[2][0, 1, 2]
// preferences[3][2, 1, 0]
// preferences[4][1, 0, 2]
//
// Round 1
//
// candidates[0].votes = 1;
// candidates[1].votes = 2;
// candidates[2].votes = 2;
//
// candidates[preferences[0][0]] = 1 ++; candidate 1 gets a vote;
// candidates[preferences[1][0]] = 2 ++; candidate 2 gets a vote;
// candidates[preferences[2][0]] = 0 ++; candidate 0 gets a vote;
// candidates[preferences[3][0]] = 2 ++; candidate 2 gets a vote;
// candidates[preferences[4][0]] = 1 ++; candidate 1 gets a vote;
//
// Round 2
//
// candidates[0].votes = 0;
// candidates[1].votes = 3; WINNER
// candidates[2].votes = 2;
//
// candidates[preferences[0][0]] = 1 ++; candidate 1 gets a vote;
// candidates[preferences[1][0]] = 2 ++; candidate 2 gets a vote;
// candidates[preferences[2][0]] = 0;    candidate is eliminated increase pointer ++; candidates[preferences[2][1]] = 1 ++; candidate 1 gets a vote;
// candidates[preferences[3][0]] = 2 ++; candidate 2 gets a vote;
// candidates[preferences[4][0]] = 1 ++; candidate 1 gets a vote;
void tabulate()
{
	for (int i = 0; i < voter_count; i++)
	{
		int pointer = 0;
		for (int j = 0; j < candidate_count; j++)
		{
			while (candidates[preferences[i][pointer]].eliminated == true)
			{
				pointer++;
			}
			candidates[preferences[i][pointer]].votes++;
			break; //----------------------------------------------------- When we have the correct vote break out of the cycle
		}
	}
}

//* Print the winner if someone has more than half the votes ----------------------------------------------------------------------------------------------
bool print_winner()
{
	int max = candidates[0].votes;
	int index_of_winner = 0;
	find_max(max, index_of_winner);
	if (max > (voter_count / 2))
	{
		cout << "Winner: " << candidates[index_of_winner].name << endl;
		return true;
	}
	return false;
}

// Find the max number of votes some candidate has
void find_max(int &max, int &index_of_winner)
{
	for (int i = 0; i < candidate_count; i++)
	{
		if (max < candidates[i].votes)
		{
			max = candidates[i].votes;
			index_of_winner = i;
		}
	}
}
//* Print the winner if someone has more than half the votes ----------------------------------------------------------------------------------------------

// Find the min number of votes some candidate has, we set the min to be equal to the first non eliminated candidate
int find_min()
{
	int min = 0;
	for (int i = 0; i < candidate_count; i++)
	{
		if (candidates[i].eliminated == false)
		{
			min = candidates[i].votes;
			break;
		}
	}

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

// Check if there is a tie in the way that if all not eliminated candidates have the same number of votes and thats the min vote
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

// Eliminate the candidate with the min votes
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

// Print the tie winners
void print_tie()
{
	for (int i = 0; i < candidate_count; i++)
	{
		if (!candidates[i].eliminated)
		{
			cout << "Winners: " << candidates[i].name << endl;
		}
	}
}

// Reset the vote count in the candidates array
void reset_vote_count()
{
	for (int i = 0; i < candidate_count; i++)
	{
		candidates[i].votes = 0;
	}
}