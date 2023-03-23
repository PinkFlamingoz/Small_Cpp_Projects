#include <iostream>
#include "basic_functions.h"

using namespace std;

int get_size();
void fill_array(int size, int array[]);
char get_max_or_min();
void print_results(char answer, int size, int array[]);

int main()
{
	int size = get_size();
	int *array = new int[size];

	fill_array(size, array);

	char answer = get_max_or_min();

	print_results(answer, size, array);

	delete[] array;

	return 0;
}

int get_size()
{
	int size = 0;
	do
	{
		size = get_valid_input<int>("Enter size: ");
	} while (size < 1);
	return size;
}

void fill_array(int size, int array[])
{
	for (int i = 0; i < size; i++)
	{
		array[i] = get_valid_input<int>("Enter value: ");
	}
}

int max(int size, int array[])
{
	int max = array[0];
	for (int i = 0; i < size; i++)
	{
		if (max < array[i])
		{
			max = array[i];
		}
	}
	return max;
}

int min(int size, int array[])
{
	int min = array[0];
	for (int i = 0; i < size; i++)
	{
		if (min > array[i])
		{
			min = array[i];
		}
	}
	return min;
}

char get_max_or_min()
{
	char answer = get_valid_input<char>("Max(1) or Min(2): ");
	return answer;
}

void print_results(char answer, int size, int array[])
{
	switch (answer)
	{
		case'1':
		{
			cout << "Max is: " << max(size, array) << endl;
			break;
		}
		case'2':
		{
			cout << "Min is: " << min(size, array) << endl;
			break;
		}
		default:
		{
			cout << "Max is: " << max(size, array) << endl;
			cout << "Min is: " << min(size, array) << endl;
			break;
		}
	}
}