#include <iostream>
#include "headers/basic_functions.h"

using namespace std;

// Functions
int get_weeks();
void fill_the_weeks(int weeks, float hours[]);
float get_average(int weeks, float hours[]);
float get_total(int weeks, float hours[]);
char get_T_or_A();
void print_results(int weeks, float hours[], char answer);

int main()
{
	int weeks = get_weeks(); //------------ Get the number of weeks to study
	float *hours = new float[weeks]; //---- Make a dynamic array with that size

	fill_the_weeks(weeks, hours); //------- Enter the hours for each week

	char answer = get_T_or_A();	//--------- Get from user to see total or average
	print_results(weeks, hours, answer); // Print for total, average or both

	delete[] hours; //--------------------- Free up the allocated memory

	return 0; //--------------------------- Success
}

// Get the number of weeks to study
int get_weeks()
{
	int weeks = 0;
	do
	{
		weeks = get_valid_input<int>("Enter number of weeks for study: ");
	} while (weeks < 1);
	return weeks;
}

// Enter hours for each week
void fill_the_weeks(int weeks, float hours[])
{
	for (int i = 0; i < weeks; i++)
	{
		hours[i] = get_valid_input<float>("Enter number of hours for week", "", -1, "", i);
	}
}

// Get the average by summing up all the hours and dividing them by the total of subjects
float get_average(int weeks, float hours[])
{
	float sum = 0;
	for (int i = 0; i < weeks; i++)
	{
		sum += hours[i];
	}
	return sum / static_cast<float>(weeks);
}

// Get the total by summing up all the hours
float get_total(int weeks, float hours[])
{
	float sum = 0;
	for (int i = 0; i < weeks; i++)
	{
		sum += hours[i];
	}
	return sum;
}

// Get from user to see total or average
char get_T_or_A()
{
	char answer = get_valid_input<char>("Total(T) or Average(A): ");
	answer = toupper(answer);
	return answer;
}

// Print the result depending on the answer in a switch case
void print_results(int weeks, float hours[], char answer)
{
	switch (answer)
	{
		case 'A':
		{
			for (int i = 0; i < weeks; i++)
			{
				cout << "Week " << i + 1 << ": " << hours[i] << "\n";
			}
			cout << "Average is: " << get_average(weeks, hours) << "\n";
			break;
		}
		case 'T':
		{
			for (int i = 0; i < weeks; i++)
			{
				cout << "Week " << i + 1 << ": " << hours[i] << "\n";
			}
			cout << "Total is: " << get_total(weeks, hours) << "\n";
			break;
		}
		default:
		{
			for (int i = 0; i < weeks; i++)
			{
				cout << "Week " << i + 1 << ": " << hours[i] << "\n";
			}
			cout << "Average is: " << get_average(weeks, hours) << "\n";
			cout << "Total is: " << get_total(weeks, hours) << "\n";
			break;
		}
	}
}