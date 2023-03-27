#include <iostream>
#include "basic_functions.h"

using namespace std;

// Functions
int get_number_of_subjects();
void enter_scores(int number, float scores[]);
float get_average(int number, float scores[]);
void print_average(int number, float scores[]);

int main()
{
	int number_of_subjects = get_number_of_subjects(); // Get the number of subjects
	float *scores = new float[number_of_subjects]; // --- Make a dynamic array with that size

	enter_scores(number_of_subjects, scores); //--------- For each subject enter a score

	print_average(number_of_subjects, scores); //-------- Print the average score

	delete[] scores; //---------------------------------- Free up the allocated memory

	return 0; //----------------------------------------- Success
}

// Get the number of subjects
int get_number_of_subjects()
{
	int number = 0;
	do
	{
		number = get_valid_input<int>("Number of subjects: ");
	} while (number < 1);
	return number;
}

// Enter the score for each subject
void enter_scores(int number, float scores[])
{
	for (int i = 0; i < number; i++)
	{
		scores[i] = get_valid_input<float>("Enter score for subject", "", -1, "", i + 1);
	}
}

// Get the average by summing up all the scores and dividing them by the total of subjects
float get_average(int number, float scores[])
{
	float sum = 0;
	for (int i = 0; i < number; i++)
	{
		sum += scores[i];
	}
	return sum / static_cast<float>(number);
}

// Print the average score, and we also print all the scores for each subject
void print_average(int number, float scores[])
{
	for (int i = 0; i < number; i++)
	{
		cout << "Grade " << i + 1 << ": " << scores[i] << "\n";
	}
	cout << "Average is: " << get_average(number, scores) << "\n";
}