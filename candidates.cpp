#include <iostream>
#include "basic_functions.h"

using namespace std;

struct Candidate
{
	string name = "";
	int votes = 0;
};

int get_number_of_candidates();
void fill_in_the_candidates(Candidate candidates[], int number);
Candidate get_candidate(string prompt, int i);
void print_candidates(Candidate candidates[], int number);

int main(void)
{
	int number = get_number_of_candidates();
	// Create candidates
	Candidate *candidates = new Candidate[number];

	fill_in_the_candidates(candidates, number);
	// Get candidates
	print_candidates(candidates, number);

	delete[] candidates;

	return 0;
}

int get_number_of_candidates()
{
	int number;
	do
	{
		number = get_valid_input<int>("Enter number of candidates: ");
	} while (number < 1);
	return number;
}

void fill_in_the_candidates(Candidate candidates[], int number)
{
	for (int i = 0; i < number; i++)
	{
		candidates[i] = get_candidate("Enter candidate", i);
	}
}

Candidate get_candidate(string prompt, int num)
{
	cout << prompt << " " << num << ": " << endl;

	Candidate temp;

	temp.name = get_valid_input<string>("Enter name: ");
	temp.votes = get_valid_input<int>("Enter votes: ");

	return temp;
}

void print_candidates(Candidate candidates[], int number)
{
	for (int i = 0; i < number; i++)
	{
		cout << "Candidate " << candidates[i].name;
		cout << " has: " << candidates[i].votes << " votes!" << endl;
	}
}