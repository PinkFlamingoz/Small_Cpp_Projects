#include <iostream>
#include "basic_functions.h"

using namespace std;

// Structures
struct Candidate
{
	string name = "";
	int votes = 0;
};

// Functions
int get_number_of_candidates();
void fill_in_the_candidates(Candidate candidates[], int number);
Candidate get_candidate(string prompt, int i);
void print_candidates(Candidate candidates[], int number);

int main(void)
{
	int number = get_number_of_candidates(); //------ Get the number of candidates
	Candidate *candidates = new Candidate[number]; // Make a dynamic array with that size

	fill_in_the_candidates(candidates, number); //--- Fill in the candidate structure array for each candidate a name and total votes that that candidate has

	print_candidates(candidates, number); //--------- Print each candidate from the candidate structure array

	delete[] candidates; //-------------------------- Free up the allocated memory

	return 0; //------------------------------------- Success
}

// Get how many candidates to put in the candidate array
int get_number_of_candidates()
{
	int number = 0;
	do
	{
		number = get_valid_input<int>("Enter number of candidates: ");
	} while (number < 1);
	return number;
}

//* Fill in the candidate structure array -----------------------------------------------------------------------------------------------------------------
void fill_in_the_candidates(Candidate candidates[], int number)
{
	for (int i = 0; i < number; i++)
	{
		candidates[i] = get_candidate("Enter candidate", i);
	}
}

// Get the values of each candidate here aka their name and total votes
Candidate get_candidate(string prompt, int num)
{
	cout << prompt << " " << num << ": " << endl;

	Candidate temp;
	temp.name = get_valid_input<string>("Enter name: ");
	temp.votes = get_valid_input<int>("Enter votes: ");
	return temp;
}
//* Fill in the candidate structure array -----------------------------------------------------------------------------------------------------------------

// Print the candidates
void print_candidates(Candidate candidates[], int number)
{
	for (int i = 0; i < number; i++)
	{
		cout << "Candidate " << candidates[i].name;
		cout << " has: " << candidates[i].votes << " votes!" << endl;
	}
}