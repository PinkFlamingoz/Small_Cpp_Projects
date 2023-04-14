#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include "basic_functions.h"

using namespace std;

// Globals
constexpr auto GREEN = "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m";
constexpr auto RESET = "\e[0;39m";

const int BOUND = 50;

// Functions
int get_size();
void random_array(int MAXSIZE, int RANDOM_ARRAY[]);
void print_array(int MAXSIZE, int RANDOM_ARRAY[]);
void bubble_sort(int MAXSIZE, int RANDOM_ARRAY[]);
void selection_sort(int MAXSIZE, int RANDOM_ARRAY[]);
void merge(int start_point, int mid_point, int end_point, int RANDOM_ARRAY[]);
void merge_sort(int start_point, int end_point, int RANDOM_ARRAY[]);
void insertion_sort(int MAXSIZE, int RANDOM_ARRAY[]);

int main()
{
	int size = get_size();
	int *RANDOM_ARRAY = new int[size];

	// Bubble -----------------------------------------------------------------------------------------------------
	cout << endl;
	cout << "---------------- Bubble -----------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	random_array(size, RANDOM_ARRAY);
	cout << "Unsorted array: ";
	print_array(size, RANDOM_ARRAY);
	cout << endl;

	auto start1 = chrono::high_resolution_clock::now();

	bubble_sort(size, RANDOM_ARRAY);

	auto end1 = chrono::high_resolution_clock::now();

	auto elapsed_seconds1 = chrono::duration_cast<chrono::duration<double>>(end1 - start1).count();

	cout << "Sorted array:   ";
	print_array(size, RANDOM_ARRAY);

	cout << endl << "Time took for bubble sort: " << elapsed_seconds1 << endl;

	// Selection -----------------------------------------------------------------------------------------------------
	cout << endl;
	cout << "---------------- Selection --------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	random_array(size, RANDOM_ARRAY);
	cout << "Unsorted array: ";
	print_array(size, RANDOM_ARRAY);
	cout << endl;

	auto start2 = chrono::high_resolution_clock::now();

	selection_sort(size, RANDOM_ARRAY);

	auto end2 = chrono::high_resolution_clock::now();

	auto elapsed_seconds2 = chrono::duration_cast<chrono::duration<double>>(end2 - start2).count();

	cout << "Sorted array:   ";
	print_array(size, RANDOM_ARRAY);

	cout << endl << "Time took selection sort: " << elapsed_seconds2 << endl;

	// Merge -----------------------------------------------------------------------------------------------------
	cout << endl;
	cout << "---------------- Merge ------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	random_array(size, RANDOM_ARRAY);
	cout << "Unsorted array: ";
	print_array(size, RANDOM_ARRAY);
	cout << endl;

	auto start3 = chrono::high_resolution_clock::now();

	merge_sort(0, size - 1, RANDOM_ARRAY);

	auto end3 = chrono::high_resolution_clock::now();

	auto elapsed_seconds3 = chrono::duration_cast<chrono::duration<double>>(end3 - start3).count();

	cout << "Sorted array:   ";
	print_array(size, RANDOM_ARRAY);

	cout << endl << "Time took for merge sort: " << elapsed_seconds3 << endl;

	// Insertion -----------------------------------------------------------------------------------------------------
	cout << endl;
	cout << "---------------- Insertion --------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	random_array(size, RANDOM_ARRAY);
	cout << "Unsorted array: ";
	print_array(size, RANDOM_ARRAY);
	cout << endl;

	auto start4 = chrono::high_resolution_clock::now();

	insertion_sort(size, RANDOM_ARRAY);

	auto end4 = chrono::high_resolution_clock::now();

	auto elapsed_seconds4 = chrono::duration_cast<chrono::duration<double>>(end4 - start4).count();

	cout << "Sorted array:   ";
	print_array(size, RANDOM_ARRAY);

	cout << endl << "Time took for merge sort: " << elapsed_seconds4 << endl;

	delete[] RANDOM_ARRAY;

	return 0;
}

// Get the size of the array with a limit of the BOUND
int get_size()
{
	int number = 0;
	do
	{
		number = get_valid_input<int>("Enter size of array: ");
	} while (number < 2 || number > BOUND);
	return number;
}

// Initialize the random array with values from 0 to 99
void random_array(int MAXSIZE, int RANDOM_ARRAY[])
{
	srand(time(nullptr));
	for (int i = 0; i < MAXSIZE; i++)
	{
		RANDOM_ARRAY[i] = rand() % 100;
	}
}

// Print the current sort of the array
void print_array(int MAXSIZE, int RANDOM_ARRAY[])
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		cout << RANDOM_ARRAY[i] << ", ";
		if (i == (MAXSIZE - 1) / 2)
		{
			cout << GREEN << "|" << RESET << " ";
		}
	}
}

// Bubble Sort
void bubble_sort(int MAXSIZE, int RANDOM_ARRAY[])
{
	int counter = 0;
	int swap_counter = -1; //------------------------------ Set swap counter to a non-zero value
	int help = 0;
	while (swap_counter != 0) //--------------------------- Repeat until the swap counter is 0
	{
		swap_counter = 0; //------------------------------- Reset swap counter to 0
		for (int i = 0; i < MAXSIZE - 1; i++)
		{
			if (RANDOM_ARRAY[i] > RANDOM_ARRAY[i + 1]) //-- Look at each adjacent pair, if two adjacent elements are not in order, swap them
			{
				help = RANDOM_ARRAY[i];
				RANDOM_ARRAY[i] = RANDOM_ARRAY[i + 1];
				RANDOM_ARRAY[i + 1] = help;
				swap_counter++; //------------------------- Add one to the swap counter

				// DEBUG PRINT
				counter++;
				cout << "Step " << counter << ":         ";
				print_array(MAXSIZE, RANDOM_ARRAY);
				cout << endl;
			}
		}
	}
}

// O(n^2)
// Worst-case scenario: The array is in reverse order; we have to "bubble" each of the n elements all the way across the array, and since we can only fully bubble one element into position per pass, we must do this n times

// Ω(n)
// Best-case scenario: The array is already perfectly sorted, and we make no swaps on the first pass

// Selection Sort
void selection_sort(int MAXSIZE, int RANDOM_ARRAY[])
{
	int counter = 0;
	int smallest_value = 0;
	int help = 0;
	for (int i = 0; i < MAXSIZE; i++)
	{
		smallest_value = i; //------------------------------------ We get the first element in the array
		for (int j = i + 1; j < MAXSIZE; j++) //------------------ j = i + 1 is used to compare the next number of the array and not to compare it with itself and not to repeat the same comparisons, its always +1 of the previous element, i represents the first value of the unsorted element
		{
			if (RANDOM_ARRAY[smallest_value] > RANDOM_ARRAY[j]) // We compare that element with the rest of the array to see if its the smallest
			{
				smallest_value = j;	//---------------------------- If we find a smaller one we make that the smallest
			}
		}
		if (smallest_value != i) //------------------------------- If the smallest value is not on the same position in the array then swap it
		{
			help = RANDOM_ARRAY[i];
			RANDOM_ARRAY[i] = RANDOM_ARRAY[smallest_value];
			RANDOM_ARRAY[smallest_value] = help;

			// DEBUG PRINT
			counter++;
			cout << "Step " << counter << ":         ";
			print_array(MAXSIZE, RANDOM_ARRAY);
			cout << endl;
		}
	}
}
// O(n^2)
// Worst-case scenario: We have to iterate over each of the n elements of the array(to find the smallest unsorted element) and we must repeat this process n times, since only one element gets sorted on each pass

// Ω(n^2)
// Best-case scenario: Exactly the same! There's no way to guarantee the array is sorted until we go through this process for all the elements

// Merge Sort
// Merge two sorted subarrays into a single sorted subarray
void merge(int start_point, int mid_point, int end_point, int RANDOM_ARRAY[])
{
	int counter = 0;
	int left_index = start_point;
	int right_index = mid_point + 1;
	int help_index = 0;
	int help_size = end_point - start_point + 1;
	int *help = new int[help_size]; //---------------------------- Allocate helper array for merging

	while (left_index <= mid_point && right_index <= end_point) // Merge the two subarrays by selecting the smallest element from each and adding it to the helper array
	{
		if (RANDOM_ARRAY[left_index] <= RANDOM_ARRAY[right_index])
		{
			help[help_index] = RANDOM_ARRAY[left_index];
			left_index++;
			help_index++;
			counter++;
		}
		else
		{
			help[help_index] = RANDOM_ARRAY[right_index];
			right_index++;
			help_index++;
			counter++;
		}
	}

	while (left_index <= mid_point) //---------------------------- Copy any remaining elements from the left subarray to the helper array
	{
		help[help_index] = RANDOM_ARRAY[left_index];
		left_index++;
		help_index++;
		counter++;
	}

	while (right_index <= end_point)  //-------------------------- Copy any remaining elements from the right subarray to the helper array
	{
		help[help_index] = RANDOM_ARRAY[right_index];
		right_index++;
		help_index++;
		counter++;
	}

	for (int i = start_point; i <= end_point; i++) //------------- Copy the merged subarray from the helper array back to the original array
	{
		RANDOM_ARRAY[i] = help[i - start_point];
	}
	delete[] help; // Free the memory used by the helper array

	// DEBUG PRINT
	cout << "Step " << counter << ":         ";
	print_array(end_point + 1, RANDOM_ARRAY);
	cout << endl;
}

// Recursively sort an array using the merge sort algorithm
void merge_sort(int start_point, int end_point, int RANDOM_ARRAY[])
{
	int mid_point = 0;
	if (start_point < end_point) //---------------------------- If the subarray contains more than one element, recursively split it into two halves and merge them
	{
		mid_point = (start_point + end_point) / 2;
		merge_sort(start_point, mid_point, RANDOM_ARRAY);
		merge_sort(mid_point + 1, end_point, RANDOM_ARRAY);
		merge(start_point, mid_point, end_point, RANDOM_ARRAY);
	}
}
// Unsorted array: 66, 92, 86, 96, 75, | 61, 31, 84, 98, 92,
// Step 2:         66, | 92,
// Step 3 :        66, 86, | 92,
// Step 2 :        66, 86, 92, | 75, 96,
// Step 5 :        66, 75, 86, | 92, 96,
// Step 2 :        66, 75, 86, 92, | 96, 31, 61,
// Step 3 :        66, 75, 86, 92, | 96, 31, 61, 84,
// Step 2 :        66, 75, 86, 92, 96, | 31, 61, 84, 92, 98,
// Step 5 :        66, 75, 86, 92, 96, | 31, 61, 84, 92, 98,
// Step 10 :       31, 61, 66, 75, 84, | 86, 92, 92, 96, 98,
// Sorted array :  31, 61, 66, 75, 84, | 86, 92, 92, 96, 98,
//
// O(n log n)
// Worst-case scenario: We have to split n elements up and then recombine them, effectively doubling the sorted subarrays as we build them up. (combining sorted 1 - element arrays into 2 - element arrays, combining sorted 2 - element arrays into 4 - element arrays…)

// Ω(n log n)
// Best-case scenario: The array is already perfectly sorted. But we still have to split and recombine it back together with this algorithm

// Insertion Sort
void insertion_sort(int MAXSIZE, int RANDOM_ARRAY[])
{
	int counter = 0;
	int previous_element = 0;
	int holder = 0;

	for (int i = 1; i < MAXSIZE; i++)
	{
		holder = RANDOM_ARRAY[i]; //----------------------------------------------- Get next element in array
		previous_element = i - 1; //----------------------------------------------- Get the index of the previous element in the array
		while (previous_element >= 0 && RANDOM_ARRAY[previous_element] > holder) // Check if the index of the previous elemet is in the bounds of the array and check if the previous element is bigger than the next one
		{
			RANDOM_ARRAY[previous_element + 1] = RANDOM_ARRAY[previous_element]; // If they are swap them
			previous_element = previous_element - 1; //---------------------------- Decrement to get the previous element and to check for the other elements behind it
		}
		RANDOM_ARRAY[previous_element + 1] = holder; //---------------------------- Place the next element in the place of the smaller element that was behind it

		// DEBUG PRINT
		counter++;
		cout << "Step " << counter << ":         ";
		print_array(MAXSIZE, RANDOM_ARRAY);
		cout << endl;
	}
}

// O(n^2)
// Worst-case scenario: Suppose, an array is in ascending order, and you want to sort it in descending order. In this case, worst case complexity occurs. Each element has to be compared with each of the other elements so, for every nth element, (n - 1) number of comparisons are made. Thus, the total number of comparisons = n * (n - 1) ~n2

// Ω(n)
// Best-case scenario: When the array is already sorted, the outer loop runs for n number of times whereas the inner loop does not run at all. So, there are only n number of comparisons. Thus, complexity is linear.