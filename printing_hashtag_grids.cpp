#include <iostream>
#include "basic_functions.h"

using namespace std;

// Functions
int get_size_bounded();
void print_horizontal(int n);
void print_vertical(int n);
void print_grid1(int n);
void print_grid2(int n);
void print_pyramid_left(int n);
void print_pyramid_right(int n);
void print_top_pyramid_left(int n);
void print_top_pyramid_right(int n);
void print_pyramid_full(int n);
void print_pyramid_full_down(int n);
void print_pyramid_full_gap(int n);
void print_pyramid_full_gap_down(int n);
void print_pyramid_single(int n);
void print_pyramid_single_down(int n);
void print_pyramid_pascal(int n);
void print_diamond(int n);

int main()
{
	// Get the bounded size
	int n = get_size_bounded();

	// Print the pyramids
	print_horizontal(n);
	print_vertical(n);
	print_grid1(n);
	print_grid2(n);
	print_pyramid_left(n);
	print_pyramid_right(n);
	print_top_pyramid_left(n);
	print_top_pyramid_right(n);
	print_pyramid_full(n);
	print_pyramid_full_down(n);
	print_pyramid_full_gap(n);
	print_pyramid_full_gap_down(n);
	print_pyramid_single(n);
	print_pyramid_single_down(n);
	print_pyramid_pascal(n);
	print_diamond(n);

	// Success
	return 0;
}

// Get the bounded size
int get_size_bounded()
{
	int n;
	do
	{
		n = get_valid_input<int>("Size must be positive(up to 11), Size: ");
	} while (n < 1 || n > 11);
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
	{
		cout << "#";
		for (int j = 0; j < n - 1; j++)
		{
			cout << "#";
		}
		cout << endl;
	}
}

void print_grid2(int n)
{
	cout << "Grid2 nxn print :" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
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

void print_top_pyramid_left(int n)
{
	cout << "Pyramid top left print :" << endl;
	for (int i = n; i > 0; i--)
	{
		for (int j = i; j > 0; j--)
		{
			cout << "#";
		}
		cout << endl;
	}
}

void print_top_pyramid_right(int n)
{
	cout << "Pyramid top right print :" << endl;
	for (int i = n; i > 0; i--)
	{
		for (int c = n - i; c > 0; c--)
		{
			cout << " ";
		}
		for (int j = i; j > 0; j--)
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

void print_pyramid_full_down(int n)
{
	cout << "Full pyramid print :" << endl;
	for (int i = n; i > 0; i--)
	{
		for (int c = n - i; c > 0; c--)
		{
			cout << " ";
		}
		for (int j = i; j > 0; j--)
		{
			cout << "#";
		}
		for (int b = i; b > 0; b--)
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

void print_pyramid_full_gap_down(int n)
{
	cout << "Full pyramid with gap print :" << endl;
	for (int i = n; i > 0; i--)
	{
		for (int c = n - i; c > 0; c--)
		{
			cout << " ";
		}
		for (int j = i; j > 0; j--)
		{
			cout << "#";
		}
		for (int a = 0; a < 2; a++)
		{
			cout << " ";
		}
		for (int b = i; b > 0; b--)
		{
			cout << "#";
		}
		cout << endl;
	}
}

void print_pyramid_single(int n)
{
	cout << "Single pyramid print :" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int c = n; c > i + 1; c--)
		{
			cout << " ";
		}
		for (int j = 0; j < i + 1; j++)
		{
			cout << "# ";
		}
		cout << endl;
	}
}

void print_pyramid_single_down(int n)
{
	cout << "Single pyramid down print :" << endl;
	for (int i = n; i > 0; i--)
	{
		for (int c = n - i; c > 0; c--)
		{
			cout << " ";
		}
		for (int j = i; j > 0; j--)
		{
			cout << "# ";
		}
		cout << endl;
	}
}

void print_pyramid_pascal(int n)
{
	cout << "Pascal triangle print :" << endl;
	for (int i = 1; i <= n; i++)
	{
		int x = 1;
		for (int c = n; c >= i; c--)
		{
			cout << " ";
		}
		for (int j = 1; j <= i; j++)
		{
			cout << x << " ";
			x = x * (i - j) / j;
		}
		cout << endl;
	}
}

void print_diamond(int n)
{
	cout << "Diamond print :" << endl;
	for (int i = 0; i < n; i++) // Top Half of diamond
	{
		for (int j = 0; j < (2 * n); j++)
		{
			if (i + j <= n - 1)
			{
				cout << "#";
			}
			else
			{
				cout << " ";
			}
			if ((i + n) <= j)
			{
				cout << "#";
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < n; i++) // Bottom Half of diamond
	{
		for (int j = 0; j < (2 * n); j++)
		{
			if (i >= j)
			{
				cout << "#";
			}
			else
			{
				cout << " ";
			}
			if (i >= (2 * n - 1) - j)
			{
				cout << "#";
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
}