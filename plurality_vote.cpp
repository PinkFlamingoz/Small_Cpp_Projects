#include <iostream>
#include <cstring>
#include "basic_get_functions.h"

using namespace std;

struct Candidate
{
	string name = "";
	int votes = 0;
};

const int MAX = 10;

Candidate candidates[MAX];

int candidate_count = 0;

void get_candidates(char* argv[]);
int get_number_of_voters();
void calculate_votes(int voter_count);
bool vote(string name);
int get_max_vote();
void print_winner(void);

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Error 1: Too many or none arguments " << endl << "Usage: ./plurality_vote [candidate ...]" << endl;
		return 1;
	}
	candidate_count = argc - 1;
	if (candidate_count > MAX)
	{
		cout << "Error 2: Too many candidates the max is: " << MAX << endl;
		return 2;
	}
	else
	{
		get_candidates(argv);
		int voter_count = get_number_of_voters();
		calculate_votes(voter_count);
		print_winner();

		return 0;
	}
}

void get_candidates(char* argv[])
{
	for (int i = 0; i < candidate_count; i++)
	{
		candidates[i].name = argv[i + 1];
		candidates[i].votes = 0;
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

void calculate_votes(int voter_count)
{
	for (int i = 0; i < voter_count; i++)
	{
		string name = get_valid_input<string>("Voter", "", i, "votes for: ");
		if (!vote(name))
		{
			cout << "Invalid vote!" << endl;
		}
	}
}

bool vote(string name)
{
	for (int i = 0; i < candidate_count; i++)
	{
		if (stricmp(candidates[i].name.c_str(), name.c_str()) == 0)
		{
			candidates[i].votes += 1;
			return true;
		}
	}
	return false;
}

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