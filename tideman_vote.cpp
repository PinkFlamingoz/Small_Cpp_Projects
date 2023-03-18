#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include "basic_get_functions.h"

using namespace std;

struct Pair
{
	int winner;
	int loser;
};

const int MAX_CANDIDATES = 9;
const int MAX_VOTERS = 100;

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX_CANDIDATES][MAX_CANDIDATES];

// locked[i][j] means i is locked in over j
bool locked[MAX_CANDIDATES][MAX_CANDIDATES];

string candidates[MAX_CANDIDATES];
Pair pairs[MAX_CANDIDATES * (MAX_CANDIDATES - 1) / 2];

int pair_count = 0;
int candidate_count = 0;
int voter_count = 0;

bool check_if_candidates_are_different(int argc, char* argv[]);
void get_candidates(char* argv[]);
void clear_graph();
int get_number_of_voters();
void set_voter_preference();
string check_if_ranked(string name, int j, vector<string>& ranked_candidates);
string get_cast_vote(string name, int j);
bool check_correct_vote_cast(bool valid_name, string name);
void vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs();
void sort_pairs();
bool check_cycle(int winner, int loser);
void lock_pairs();
void print_winner();

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
	bool all_random = check_if_candidates_are_different(argc, argv);
	if (!all_random)
	{
		cout << "Error 3: Candidates must not have the same name! " << endl;
		return 3;
	}
	else
	{
		get_candidates(argv);
		clear_graph();
		voter_count = get_number_of_voters();
		if (voter_count > MAX_VOTERS)
		{
			cout << "Error 3: Maximum number of voter is: " << MAX_VOTERS << endl;
			return 3;
		}
		set_voter_preference();
		add_pairs();
		sort_pairs();
		lock_pairs();
		print_winner();
		return 0;
	}
}

bool check_if_candidates_are_different(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		for (int j = i + 1; j < argc; j++)
		{
			if (stricmp(argv[i], argv[j]) == 0)
			{
				return false;
			}
		}
	}
	return true;
}

void get_candidates(char* argv[])
{
	for (int i = 0; i < candidate_count; i++)
	{
		candidates[i] = argv[i + 1];
	}
}

void clear_graph()
{
	for (int i = 0; i < candidate_count; i++)
	{
		for (int j = 0; j < candidate_count; j++)
		{
			locked[i][j] = false;
		}
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

void set_voter_preference()
{
	// Query for votes
	for (int i = 0; i < voter_count; i++)
	{
		// ranks[i] is voter's ith preference
		int* ranks = new int[candidate_count];

		cout << "Voter " << i << ": " << endl;
		// Vector array to keep track of already ranked candidates
		vector<string> ranked_candidates;
		// Query for each rank
		for (int j = 0; j < candidate_count; j++)
		{
			string name = check_if_ranked(name, j, ranked_candidates);

			vote(j, name, ranks);
		}

		record_preferences(ranks);
		delete[] ranks;
		cout << endl;
	}
}

string check_if_ranked(string name, int j, vector<string>& ranked_candidates)
{
	bool valid_vote = false;
	while (!valid_vote)
	{
		name = get_cast_vote(name, j);
		transform(name.begin(), name.end(), name.begin(), ::tolower);
		if (find(ranked_candidates.begin(), ranked_candidates.end(), name) != ranked_candidates.end())
		{
			cout << "Error: Candidate already ranked." << endl;
		}
		else
		{
			ranked_candidates.push_back(name);
			valid_vote = true;
		}
	}
	return name;
}

string get_cast_vote(string name, int j)
{
	bool valid_name = false;
	while (!valid_name)
	{
		name = get_valid_input<string>("Enter vote preference", "", -1, "", j);
		valid_name = check_correct_vote_cast(valid_name, name);
		if (!valid_name)
		{
			cout << "Error: Invalid candidate name." << endl;
		}
	}
	return name;
}

bool check_correct_vote_cast(bool valid_name, string name)
{
	for (int i = 0; i < candidate_count; i++)
	{
		if (stricmp(candidates[i].c_str(), name.c_str()) == 0)
		{
			return valid_name = true;
		}
	}
	return valid_name = false;
}

// Update ranks given a new vote
void vote(int rank, string name, int ranks[])
{
	for (int i = 0; i < candidate_count; i++)
	{
		if (stricmp(candidates[i].c_str(), name.c_str()) == 0)
		{
			ranks[rank] = i;
			break;
		}
	}
}

// Update preferences given one voter's ranks ALICE = 0 BOB = 1 CHARLIE = 2
// VOTER 1 = 0 2 1
// preferences[0][2]++
// preferences[0][1]++
// preferences[2][1]++
// VOTER 2 = 2 0 1
// preferences[2][0]++
// preferences[2][1]++
// preferences[0][1]++
// ---------------------------------------------------------------------
void record_preferences(int ranks[])
{
	for (int i = 0; i < candidate_count; i++)
	{
		for (int j = i + 1; j < candidate_count; j++)
		{
			preferences[ranks[i]][ranks[j]]++;
		}
	}
}

// Record pairs of candidates where one is preferred over the other
void add_pairs()
{
	for (int i = 0; i < candidate_count; i++)
	{
		for (int j = i; j < candidate_count; j++)
		{
			if (preferences[i][j] != 0)
			{
				if (preferences[i][j] > preferences[j][i]) // We always compare the opposites of the matrix example to check if Alice wins that will be 0, preferences[0][1], opposite of that in the matrix is preferences[1][0], so we compare them next we check Alice vs Charlie or [0][2] vs [2][0], then we have no more for alice and we go to Bob thats 1, [1][0] is already checked we skip to [1][2] vs [2][1] and so on
				{
					pairs[pair_count].winner = i;
					pairs[pair_count].loser = j;
					pair_count++;
				}
				else if (preferences[i][j] < preferences[j][i])
				{
					pairs[pair_count].winner = j;
					pairs[pair_count].loser = i;
					pair_count++;
				}
			}
		}
	}
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs()
{
	int swap_counter = -1;
	Pair help;
	while (swap_counter != 0)
	{
		swap_counter = 0;
		for (int i = 0; i < pair_count - 1; i++)
		{
			if ((preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]) < (preferences[pairs[i + 1].winner][pairs[i + 1].loser] - preferences[pairs[i + 1].loser][pairs[i + 1].winner]))
			{
				help = pairs[i];
				pairs[i] = pairs[i + 1];
				pairs[i + 1] = help;
				swap_counter++;
			}
		}
	}
}

//       W  L  W  L  W  L
// PAIRS 0->1, 2->0, 1->2;
//
//  TABLE   0 1 2                                     |    TABLE   0 1 2                                                      |      TABLE   0 1 2
//        0 F F F                                     |          0 F T F                                                      |            0 F T F
//        1 F F F                                     |          1 F F F                                                      |            1 F F F
//        2 F F F                                     |          2 F F F                                                      |            2 T F F
//                                                    |                                                                       |
//          W  L                                      |            W  L                                                       |              W  L
// CHECK 1 (0, 1)                                     |   CHECK 2 (2, 0)                                                      |     CHECK 3 (1, 2)
// {       0 == 1 = F                                 |   {       2 == 0 = F                                                  |     {       1 == 2 = F
//      LOCKED [L][ i < candidate_count] == TRUE?     |        LOCKED [L][ i < candidate_count] == TRUE?                      |          LOCKED [L][ i < candidate_count] == TRUE?
//      {      [1][0] == F;                           |        {      [0][0] == F;                                            |          {      [2][0] == T;|1 -> 2 -> 0|
//             [1][1] == F;                           |               [0][1] == T;|2 -> 0 -> 1|                               |          call again   { CHECK 3.1 (W, i)
//             [1][2] == F;                           |        call again   { CHECK 2.1 (W, i)                                |                         {         1 == 0 = F
//      }                                             |                       {         2 == 1 = F                            |                              LOCKED [L][ i < candidate_count] == TRUE?
//      CHECK 1 = FALSE                               |                            LOCKED [L][ i < candidate_count] == TRUE?  |                              {      [0][0] == F;
//      ADD TRUE AT [0][1]                            |                            {      [1][0] == F;                        |                                     [0][1] == T;|1 -> 2 -> 0 -> 1|
// }                                                  |                                   [1][1] == F;                        |                              call again   { CHECK 3.2 (W, i)
//                                                    |                                   [1][2] == F;                        |                                             {         1 == 1 = T  CYCLE HAS BEEN CREATED
//    0 -> 1;                                         |                            }                                          |                                                  CHECK 3.2 = TRUE
//                                                    |                            CHECK 2.1 = FALSE                          |                                             }
//                                                    |                       }                                               |                                           }
//                                                    |                     }                                                 |                              }
//                                                    |               [0][2] == F;                                            |                              CHECK 3.1 = TRUE
//                                                    |        }                                                              |                         }
//                                                    |        CHECK 2 = FALSE                                                |                       }
//                                                    |        ADD TRUE AT [2][0]                                             |          }
//                                                    |   }                                                                   |          CHECK 3 = TRUE
//                                                    |       2 -> 0 -> 1                                                     |          DONT ADD CYCLE
//                                                    |                                                                       |     }
//                                                    |                                                                       |         1 -> 2 -> 0 -> 1
//                                                    |                                                                       |
bool check_cycle(int winner, int loser)
{
	// base case
	if (winner == loser) // Check if a cycle has been created
	{
		return true;
	}

	// recursive case
	for (int i = 0; i < candidate_count; i++)
	{
		if (locked[loser][i]) // We check if loser wins in any pairs in the locked array
		{
			if (check_cycle(winner, i)) // We build a chain and see if we get back to the original
			{
				return true;
			}
		}
	}
	return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs()
{
	for (int i = 0; i < pair_count; i++)
	{
		if (!check_cycle(pairs[i].winner, pairs[i].loser))
		{
			locked[pairs[i].winner][pairs[i].loser] = true;
		}
	}
}

// Print the winner of the election
void print_winner()
{
	for (int i = 0; i < candidate_count; i++)
	{
		int counter_of_truths = 0;
		for (int j = 0; j < candidate_count; j++)
		{
			if (locked[j][i] == false) // We check if the columb is all false
			{
				counter_of_truths++;
			}
		}
		if (counter_of_truths == candidate_count)
		{
			cout << "Winner is: " << candidates[i] << endl;
		}
	}
}