#include <iostream>
#include <D:\Xixijan\repos\Small_C++_Projects\basic_get_functions.h>

using namespace std;

int get_weeks();
void fill_the_weeks(int weeks, float hours[]);
float get_average(int weeks, float hours[]);
float get_total(int weeks, float hours[]);
char get_T_or_A();
void print_results(int weeks, float hours[], char answer);

int main()
{
	// Get how many weeks
	int weeks = get_weeks();
	float* hours = new float[weeks];
	// Enter the hours
	fill_the_weeks(weeks, hours);
	// Print for total or average
	char answer = get_T_or_A();
	print_results(weeks, hours, answer);

	delete[] hours;

	return 0;
}

int get_weeks()
{
	int weeks = 0;
	do
	{
		weeks = get_valid_input<int>("Enter number of weeks for study: ");
	} while (weeks < 1);
	return weeks;
}

void fill_the_weeks(int weeks, float hours[])
{
	for (int i = 0; i < weeks; i++)
	{
		hours[i] = get_valid_input<int>("Enter number of hours for week", "", -1, "", i);
	}
}

float get_average(int weeks, float hours[])
{
	float sum = 0;
	for (int i = 0; i < weeks; i++)
	{
		sum += hours[i];
	}
	return sum / (float)weeks;
}

float get_total(int weeks, float hours[])
{
	float sum = 0;
	for (int i = 0; i < weeks; i++)
	{
		sum += hours[i];
	}
	return sum;
}

char get_T_or_A()
{
	char answer = get_valid_input<char>("Total(T) or Average(A): ");
	answer = toupper(answer);
	return answer;
}

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