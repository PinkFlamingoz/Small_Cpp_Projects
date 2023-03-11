#include <iostream>
#include <limits>

using namespace std;

int get_size_bounded();
void print_horizontal(int n);
void print_vertical(int n);
void print_grid1(int n);
void print_grid2(int n);
void print_pyramid_left(int n);
void print_pyramid_right(int n);
void print_pyramid_full(int n);
void print_pyramid_full_gap(int n);

int main()
{
	// Get the bounded size
	int n = get_size_bounded();
	// Print the pyramid
	print_horizontal(n);
	print_vertical(n);
	print_grid1(n);
	print_grid2(n);
	print_pyramid_left(n);
	print_pyramid_right(n);
	print_pyramid_full(n);
	print_pyramid_full_gap(n);

	return 0;
}

template <typename T>
T get_valid_input(const string& prompt)
{
	T input;
	while (true)
	{
		cout << prompt;
		if (cin >> input)
		{
			// The user entered a valid number
			break;
		}
		else
		{
			// The user did not enter a valid number
			cout << "Error: Please enter a valid input." << endl;
			cin.clear(); // Clear the error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any input in the buffer
		}
	}
	return input;
}

int get_size_bounded()
{
	int n;
	do
	{
		n = get_valid_input<int>("Size must be positive(up to 8), Size: ");
	} while (n < 1 || n > 8);
	return n;
}

void print_horizontal(int n)
{
	cout << "Horizontal print :" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "#";
	}
	cout << endl;
}

void print_vertical(int n)
{
	cout << "Vertical print :" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "#" << endl;
	}
}

void print_grid1(int n)
{
	cout << "Grid1 nxn print :" << endl;
	for (int i = 0; i < n; i++)
	{ // column
		cout << "#";
		for (int j = 0; j < n - 1; j++)
		{ // row
			cout << "#";
		}
		cout << endl;
	}
}

void print_grid2(int n)
{
	cout << "Grid2 nxn print :" << endl;
	for (int i = 0; i < n; i++) // column
	{
		for (int j = 0; j < n; j++) // row
		{
			cout << "#";
		}
		cout << endl;
	}
}

void print_pyramid_left(int n)
{
	cout << "Pyramid left print :" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i + 1; j++)
		{
			cout << "#";
		}
		cout << endl;
	}
}

void print_pyramid_right(int n)
{
	cout << "Pyramid right print :" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int c = n; c > i + 1; c--)
		{
			cout << " ";
		}
		for (int j = 0; j < i + 1; j++)
		{
			cout << "#";
		}
		cout << endl;
	}
}

void print_pyramid_full(int n)
{
	cout << "Full pyramid print :" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int c = n; c > i + 1; c--)
		{
			cout << " ";
		}
		for (int j = 0; j < i + 1; j++)
		{
			cout << "#";
		}
		for (int b = 0; b < i + 1; b++)
		{
			cout << "#";
		}
		cout << endl;
	}
}

void print_pyramid_full_gap(int n)
{
	cout << "Full pyramid with gap print :" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int c = n; c > i + 1; c--)
		{
			cout << " ";
		}
		for (int j = 0; j < i + 1; j++)
		{
			cout << "#";
		}
		for (int a = 0; a < 2; a++)
		{
			cout << " ";
		}
		for (int b = 0; b < i + 1; b++)
		{
			cout << "#";
		}
		cout << endl;
	}
}