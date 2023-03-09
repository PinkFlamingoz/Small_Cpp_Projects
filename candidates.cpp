#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Candidate
{
	string name;
	int votes;
};

int get_number_of_candidates();
void fill_in_the_candidates(Candidate candidates[], int number);
Candidate get_candidate(string prompt);
void print_candidates(Candidate candidates[], int number);

int main(void)
{
	int number = get_number_of_candidates();
	// Create candidates
	Candidate* candidates = new Candidate[number];
	fill_in_the_candidates(candidates, number);
	// Get candidates
	print_candidates(candidates, number);

	delete[] candidates;

	return 0;
}

template <typename T>
T get_valid_input(const string& prompt) {
	T input;
	while (true) {
		cout << prompt;
		cin >> input;
		if (cin.fail()) {
			// Input is not valid
			cout << "Error: Please enter a valid input." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else {
			// Input is valid
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}
	return input;
}

template<>
string get_valid_input<string>(const string& prompt) {
	string input;
	while (true) {
		cout << prompt;
		getline(cin, input);
		if (cin.fail() || input.empty()) {
			// Input is not valid
			cout << "Error: Please enter a valid input." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else {
			// Input is valid
			break;
		}
	}
	return input;
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
		candidates[i] = get_candidate("Enter candidate");
	}
}

Candidate get_candidate(string prompt)
{
	cout << prompt << endl;

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