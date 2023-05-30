#include <iostream>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include "basic_functions.h"

using namespace std;
// Time complexity = input length, number of steps
// Space complexity = volume of memory, space complexity is input size + auxiliary space
// Auxiliary space is the temporary space excluding the (input size) allocated by the algorithm to solve the problem, with respect to the input size.
// NOTE: How to find the big O notation
// 1. Find the fastest growing variable term
// 2. Eliminate the co-efficients/constant terms
// Example:
//
// function sum(N)
// {
//		sum=0; -------------- + 1 msek
//		for(i=0 to N) ------- + 1 msek
//		{
//			sum = sum + 1; -- + N msek
//		}
//		return sum; --------- + 1 msek
// }
//
// Time complexity = N + 3 msek // N is the variable 3 msek is the constant // if we had (2 * N + 3 msek) 2 would be the coefficient
// T = N
// O(n)

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
void merge(int start, int mid, int end, int RANDOM_ARRAY[]);
void merge_sort(int start, int end, int RANDOM_ARRAY[]);
void insertion_sort(int MAXSIZE, int RANDOM_ARRAY[]);
int partition(int start, int end, int RANDOM_ARRAY[]);
void quick_sort(int start, int end, int RANDOM_ARRAY[]);
void counting_sort(int MAXSIZE, int range, int RANDOM_ARRAY[]);
void counting_sort_positive_negative(int MAXSIZE, int min_val, int max_val, int RANDOM_ARRAY[]);
void radix_sort(int MAXSIZE, int RANDOM_ARRAY[]);
int max(int size, int array[]);
int min(int size, int array[]);
void counting_sort_radix(int MAXSIZE, int range, int divide, int RANDOM_ARRAY[]);
void shell_sort(int MAXSIZE, int RANDOM_ARRAY[]);
void swap(int &value1, int &value2);
int left_child(int i);
int right_child(int i);
void min_heapify(int i, int MAXSIZE, int RANDOM_ARRAY[]);
void heapify(int MAXSIZE, int RANDOM_ARRAY[]);
int extract_min(int &MAXSIZE, int RANDOM_ARRAY[]);
void heap_sort(int &MAXSIZE, int RANDOM_ARRAY[]);

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

	// Insertion -----------------------------------------------------------------------------------------------------
	cout << endl;
	cout << "---------------- Insertion --------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	random_array(size, RANDOM_ARRAY);
	cout << "Unsorted array: ";
	print_array(size, RANDOM_ARRAY);
	cout << endl;

	auto start3 = chrono::high_resolution_clock::now();

	insertion_sort(size, RANDOM_ARRAY);

	auto end3 = chrono::high_resolution_clock::now();

	auto elapsed_seconds3 = chrono::duration_cast<chrono::duration<double>>(end3 - start3).count();

	cout << "Sorted array:   ";
	print_array(size, RANDOM_ARRAY);

	cout << endl << "Time took for merge sort: " << elapsed_seconds3 << endl;

	// Merge -----------------------------------------------------------------------------------------------------
	cout << endl;
	cout << "---------------- Merge ------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	random_array(size, RANDOM_ARRAY);
	cout << "Unsorted array: ";
	print_array(size, RANDOM_ARRAY);
	cout << endl;

	auto start4 = chrono::high_resolution_clock::now();

	merge_sort(0, size - 1, RANDOM_ARRAY);

	auto end4 = chrono::high_resolution_clock::now();

	auto elapsed_seconds4 = chrono::duration_cast<chrono::duration<double>>(end4 - start4).count();

	cout << "Sorted array:   ";
	print_array(size, RANDOM_ARRAY);

	cout << endl << "Time took for merge sort: " << elapsed_seconds4 << endl;

	// Quick -----------------------------------------------------------------------------------------------------
	cout << endl;
	cout << "---------------- Quick ------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	random_array(size, RANDOM_ARRAY);
	cout << "Unsorted array: ";
	print_array(size, RANDOM_ARRAY);
	cout << endl;

	auto start5 = chrono::high_resolution_clock::now();

	quick_sort(0, size - 1, RANDOM_ARRAY);

	auto end5 = chrono::high_resolution_clock::now();

	auto elapsed_seconds5 = chrono::duration_cast<chrono::duration<double>>(end5 - start5).count();

	cout << "Sorted array:   ";
	print_array(size, RANDOM_ARRAY);

	cout << endl << "Time took for merge sort: " << elapsed_seconds5 << endl;

	// Count -----------------------------------------------------------------------------------------------------
	cout << endl;
	cout << "---------------- Count ------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	random_array(size, RANDOM_ARRAY);
	cout << "Unsorted array: ";
	print_array(size, RANDOM_ARRAY);
	cout << endl;

	auto start6 = chrono::high_resolution_clock::now();

	counting_sort_positive_negative(size, min(size, RANDOM_ARRAY), max(size, RANDOM_ARRAY), RANDOM_ARRAY);

	auto end6 = chrono::high_resolution_clock::now();

	auto elapsed_seconds6 = chrono::duration_cast<chrono::duration<double>>(end6 - start6).count();

	cout << "Sorted array:   ";
	print_array(size, RANDOM_ARRAY);

	cout << endl << "Time took for merge sort: " << elapsed_seconds6 << endl;

	// Radix -----------------------------------------------------------------------------------------------------
	cout << endl;
	cout << "---------------- Radix ------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	random_array(size, RANDOM_ARRAY);
	cout << "Unsorted array: ";
	print_array(size, RANDOM_ARRAY);
	cout << endl;

	auto start7 = chrono::high_resolution_clock::now();

	radix_sort(size, RANDOM_ARRAY);

	auto end7 = chrono::high_resolution_clock::now();

	auto elapsed_seconds7 = chrono::duration_cast<chrono::duration<double>>(end7 - start7).count();

	cout << "Sorted array:   ";
	print_array(size, RANDOM_ARRAY);

	cout << endl << "Time took for merge sort: " << elapsed_seconds7 << endl;

	// Shell -----------------------------------------------------------------------------------------------------
	cout << endl;
	cout << "---------------- Shell ------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	random_array(size, RANDOM_ARRAY);
	cout << "Unsorted array: ";
	print_array(size, RANDOM_ARRAY);
	cout << endl;

	auto start8 = chrono::high_resolution_clock::now();

	shell_sort(size, RANDOM_ARRAY);

	auto end8 = chrono::high_resolution_clock::now();

	auto elapsed_seconds8 = chrono::duration_cast<chrono::duration<double>>(end8 - start8).count();

	cout << "Sorted array:   ";
	print_array(size, RANDOM_ARRAY);

	cout << endl << "Time took for merge sort: " << elapsed_seconds8 << endl;

	// Heap ------------------------------------------------------------------------------------------------------
	cout << endl;
	cout << "---------------- Heap -------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	random_array(size, RANDOM_ARRAY);
	cout << "Unsorted array: ";
	print_array(size, RANDOM_ARRAY);
	cout << endl;

	heapify(size, RANDOM_ARRAY);
	cout << "Heapify array: ";
	print_array(size, RANDOM_ARRAY);
	cout << endl;

	auto start9 = chrono::high_resolution_clock::now();

	heap_sort(size, RANDOM_ARRAY);

	auto end9 = chrono::high_resolution_clock::now();

	auto elapsed_seconds9 = chrono::duration_cast<chrono::duration<double>>(end9 - start9).count();

	cout << "Sorted array:   ";
	print_array(size, RANDOM_ARRAY);

	cout << endl << "Time took for merge sort: " << elapsed_seconds9 << endl;

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

// Initialize the random array with values from -99 to 99
void random_array(int MAXSIZE, int RANDOM_ARRAY[])
{
	srand(time(nullptr));
	for (int i = 0; i < MAXSIZE; i++)
	{
		RANDOM_ARRAY[i] = rand() % 199 - 100;
	}
}

// Print the current sort of the array
void print_array(int MAXSIZE, int RANDOM_ARRAY[])
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		cout << RANDOM_ARRAY[i] << ", ";
		//if (i == (MAXSIZE - 1) / 2)
		//{
			//cout << GREEN << "|" << RESET << " ";
		//}
	}
}

// Bubble Sort
// Bubble Sort is the simplest sorting algorithm that works by repeatedly swapping the adjacent elements if they are in wrong order.
// This algorithm is suitable for small data sets.
// Its average and worst case complexity are O(n^2) where n is the number of items.
// It is known as bubble sort, because with every complete iteration the largest element bubbles up towards the last place or the highest index just like a water bubble rises up to the water surface.
void bubble_sort(int MAXSIZE, int RANDOM_ARRAY[])
{
	// DEBUG COUNTER
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
				cout << "Step " << ++counter << ":         ";
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
// Selection sort is a sorting algorithm, specifically an in - place comparison sort.
// It has O(n^2) time complexity, making it inefficient on large lists.
// The algorithm divides the input list into two parts:
//  - the sublist of items already sorted, which is built up from left to right at the front(left) of the list,
//  - and the sublist of items remaining to be sorted that occupy the rest of the list.
// Initially, the sorted sublist is empty and the unsorted sublist is the entire input list.
// The algorithm proceeds by finding the smallest(or largest, depending on sorting order) element in the unsorted sublist, exchanging(swapping) it with the leftmost unsorted element(putting it in sorted order), and moving the sublist boundaries one element to the right.
void selection_sort(int MAXSIZE, int RANDOM_ARRAY[])
{
	// DEBUG COUNTER
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
			cout << "Step " << ++counter << ":         ";
			print_array(MAXSIZE, RANDOM_ARRAY);
			cout << endl;
		}
	}
}
// O(n^2)
// Worst-case scenario: We have to iterate over each of the n elements of the array(to find the smallest unsorted element) and we must repeat this process n times, since only one element gets sorted on each pass

// Ω(n^2)
// Best-case scenario: Exactly the same! There's no way to guarantee the array is sorted until we go through this process for all the elements

// Insertion Sort
// Insertion sort is a simple sorting algorithm that works the way we sort playing cards in our hands.
// Insertion sort is a simple sorting algorithm that builds the final sorted array(or list) one item at a time.
// Time Complexity: O(n^2)
// Efficient for (quite) small data sets, much like other quadratic sorting algorithms
// More efficient in practice than most other simple quadratic(i.e., O(n^2)) algorithms such as selection sort or bubble sort
void insertion_sort(int MAXSIZE, int RANDOM_ARRAY[])
{
	// DEBUG COUNTER
	int counter = 0;

	int previous_element = 0;
	int holder = 0;

	for (int i = 1; i < MAXSIZE; i++)
	{
		holder = RANDOM_ARRAY[i]; //----------------------------------------------- Get next element in array
		previous_element = i - 1; //----------------------------------------------- Get the index of the previous element in the array
		while (previous_element >= 0 && RANDOM_ARRAY[previous_element] > holder) // Check if the index of the previous element is in the bounds of the array and check if the previous element is bigger than the next one
		{
			RANDOM_ARRAY[previous_element + 1] = RANDOM_ARRAY[previous_element]; // If they are swap them
			previous_element = previous_element - 1; //---------------------------- Decrement to get the previous element and to check for the other elements behind it
		}
		RANDOM_ARRAY[previous_element + 1] = holder; //---------------------------- Place the next element in the place of the smaller element that was behind it

		// DEBUG PRINT
		cout << "Step " << ++counter << ":         ";
		print_array(MAXSIZE, RANDOM_ARRAY);
		cout << endl;
	}
}
// O(n^2)
// Worst-case scenario: Suppose, an array is in ascending order, and you want to sort it in descending order. In this case, worst case complexity occurs. Each element has to be compared with each of the other elements so, for every nth element, (n - 1) number of comparisons are made. Thus, the total number of comparisons = n * (n - 1) ~n2

// Ω(n)
// Best-case scenario: When the array is already sorted, the outer loop runs for n number of times whereas the inner loop does not run at all. So, there are only n number of comparisons. Thus, complexity is linear.

//* Merge Sort
// Merge two sorted subarrays into a single sorted subarray
void merge(int start, int mid, int end, int RANDOM_ARRAY[])
{
	// DEBUG COUNTER
	int counter = 0;

	int left = start; //------------------------------ Starting index of left subarray
	int right = mid + 1; //--------------------------- Starting index of right subarray
	int help_index = 0; //---------------------------- Starting index of helper array
	int help_size = end - start + 1;
	int *help = new int[help_size]; //---------------- Allocate helper array for merging

	while (left <= mid && right <= end) //------------ Make sure the subarrays don't go over the size of the full array and merge the two subarrays by selecting the smallest element from each and adding it to the helper array
	{
		if (RANDOM_ARRAY[left] <= RANDOM_ARRAY[right])
		{
			help[help_index] = RANDOM_ARRAY[left];
			left++; //-------------------------------- Increase the index of the left subarray so we point to the next element
		}
		else
		{
			help[help_index] = RANDOM_ARRAY[right];
			right++; //------------------------------- Increase the index of the right subarray so we point to the next element
		}
		help_index++;

		// DEBUG COUNTER
		counter++;
	}

	while (left <= mid) //---------------------------- Copy any remaining elements from the left subarray to the helper array
	{
		help[help_index] = RANDOM_ARRAY[left];
		left++;
		help_index++;

		// DEBUG COUNTER
		counter++;
	}

	while (right <= end)  //-------------------------- Copy any remaining elements from the right subarray to the helper array
	{
		help[help_index] = RANDOM_ARRAY[right];
		right++;
		help_index++;

		// DEBUG COUNTER
		counter++;
	}

	for (int i = start; i <= end; i++) //------------- Copy the merged subarray from the helper array back to the original array
	{
		RANDOM_ARRAY[i] = help[i - start];
	}

	delete[] help; //--------------------------------- Free the memory used by the helper array

	// DEBUG PRINT
	cout << "Step " << counter << ":         ";
	print_array(end + 1, RANDOM_ARRAY);
	cout << endl;
}

// Recursively sort an array using the merge sort algorithm
void merge_sort(int start, int end, int RANDOM_ARRAY[])
{
	if (start < end) //--------------------------- If the subarray contains more than one element, recursively split it into two halves and merge them
	{
		int mid = start + (end - start) / 2;
		merge_sort(start, mid, RANDOM_ARRAY); //-- Partition left side
		merge_sort(mid + 1, end, RANDOM_ARRAY); // Partition right side
		merge(start, mid, end, RANDOM_ARRAY); //-- Merge the subarrays
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

// O(n log n)
// Worst-case scenario: We have to split n elements up and then recombine them, effectively doubling the sorted subarrays as we build them up. (combining sorted 1 - element arrays into 2 - element arrays, combining sorted 2 - element arrays into 4 - element arrays…)

// Ω(n log n)
// Best-case scenario: The array is already perfectly sorted. But we still have to split and recombine it back together with this algorithm
//* Merge Sort

//* Quick Sort
// Partition
int partition(int start, int end, int RANDOM_ARRAY[])
{
	// DEBUG COUNTER
	int counter = 0;

	int pivot = RANDOM_ARRAY[end]; //------------- Get the last element in the array as the pivot
	int index = start; //------------------------- Get the first element to compare with the pivot

	for (int i = start; i < end; i++) //---------- Compare each element with the pivot element
	{
		if (RANDOM_ARRAY[i] <= pivot) //---------- If any element is smaller or equal than the pivot, swap that element with the index element (aka put the smaller element to the left)
		{
			int help = RANDOM_ARRAY[i];
			RANDOM_ARRAY[i] = RANDOM_ARRAY[index];
			RANDOM_ARRAY[index] = help;

			index++; //--------------------------- Get the next element to compare with the pivot

			// DEBUG COUNTER
			counter++;
		}
	}

	//-------------------------------------------- Swap the pivot with the last swapped element (aka putting it in the middle (aka after the last smallest element to the pivot))
	int help = RANDOM_ARRAY[end];
	RANDOM_ARRAY[end] = RANDOM_ARRAY[index];
	RANDOM_ARRAY[index] = help;

	// DEBUG PRINT
	cout << "Step " << counter << ":         ";
	print_array(end + 1, RANDOM_ARRAY);
	cout << endl;

	return index; //------------------------------ Return the next pivot to separates the array
}

// Recursively sort an array using the quick sort algorithm
void quick_sort(int start, int end, int RANDOM_ARRAY[])
{
	if (start < end) //------------------------------------ If the subarray contains more than one element, recursively split it into two halves and merge them
	{
		int pivot = partition(start, end, RANDOM_ARRAY); // Find the pivot (aka the element to separate the next array into a smaller one) and sort by putting all the smaller elements compared to the pivot to the left and the bigger values to the right
		quick_sort(start, pivot - 1, RANDOM_ARRAY); //----- Partition left side
		quick_sort(pivot + 1, end, RANDOM_ARRAY); //------- Partition right side
	}
}
// O(n^2)
// Worst-case scenario

// Ω(n log n)
// Best-case scenario
//* Quick Sort

//* Counting Sort
// Counting sort is a sorting algorithm that sorts the elements of an array by counting the number of occurrences of each unique element in the array / list / data structure.
// The count is stored in an auxiliary array and the sorting is done by mapping the count as an index of the auxiliary array.
// This mapping is done by performing arithmetic calculations on those counts to determine the positions of each key value(unique element) in the output sequence.
// Its running time is linear in the number of items and the difference between the maximum and minimum key values, so it is only suitable for direct use in situations where the variation in keys is not significantly greater than the number of items.
// It is often used as a subroutine in another sorting algorithm, radix sort, that can handle larger keys more efficiently.
// Because counting sort uses key values as indexes into an array, it is not a comparison sort, and the Ω(n log n) lower bound for comparison sorting does not apply to it.
// Time Complexity: O(n + k) where n is the number of elements in input array and k is the range of input.
// Auxiliary Space: O(n + k)
//
// Unsorted array:     9, 0, 2, 2, 3, 3, 7, 1, 4, 9,
// Count array:        1, 1, 2, 2, 1, 0, 0, 1, 0, 2,
// Count array summed: 1, 2, 4, 6, 7, 7, 7, 8, 8, 10,
// Output array:       0, 1, 2, 2, 3, 3, 4, 7, 9, 9,
// Sorted array:       0, 1, 2, 2, 3, 3, 4, 7, 9, 9,
//
// Unsorted array:     9, 0, 4, 5, 6, 6, 9,
// Count array:        1, 0, 0, 0, 1, 1, 2, 0, 0, 2, // from 0 - 10 is our range of values that we can have // so each index (aka the size of this array) represents a value that can show up in our unsorted array, we simply increase the value for each occurrence of that value, so if 9 shows up 2 times on the 9th position of the this array we input 2
// Count array summed: 1, 1, 1, 1, 2, 3, 5, 5, 5, 7, // we cumulative sum of these counts // example: for the first element its always the same as the above ( here 1 ), next we have pos = ith element + ith - 1 element; position 2: 0 + 1 = 1; position 3: 0 + 1 = 1; position 4: 1 + 1 = 2; position 5: 1 + 2 = 3; position 6: 2 + 3 = 5; position 7: 5 + 0 = 5; position 8: 5 + 0 = 5; position 9: 5 + 2 = 7;
// Output array:       0, 4, 5, 6, 6, 9, 9,
// For the output array we have the values of the unsorted array represent the indexes of the count array summed, and the values of count array summed represent the index(position) where to place the sorted value

// So if we have 9 value of unsorted array
// Index of count array summed says output_array[--count_array[RANDOM_ARRAY[i]]] = RANDOM_ARRAY[i];
//                                  output_array[--count_array[9              ]] = 9;
//                                  output_array[--7                           ] = 9;
//                                  output_array[6                             ] = 9;
// So at the 6th index(position) of the output array place the value 9
// Output array:       0, 0, 0, 0, 0, 0, 9,
// Count array summed: 1, 1, 1, 1, 2, 3, 5, 5, 5, 7,
// Count array summed: 1, 1, 1, 1, 2, 3, 5, 5, 5, 6,

// So if we have 0 value of unsorted array
// Index of count array summed says output_array[--count_array[RANDOM_ARRAY[i]]] = RANDOM_ARRAY[i];
//                                  output_array[--count_array[0              ]] = 0;
//                                  output_array[--1                           ] = 0;
//                                  output_array[0                             ] = 0;
// So at the 0th index(position) of the output array place the value 0
// Output array:       0, 0, 0, 0, 0, 0, 9,
// Count array summed: 1, 1, 1, 1, 2, 3, 5, 5, 5, 6,
// Count array summed: 0, 1, 1, 1, 2, 3, 5, 5, 5, 6,

// So if we have 4 value of unsorted array
// Index of count array summed says output_array[--count_array[RANDOM_ARRAY[i]]] = RANDOM_ARRAY[i];
//                                  output_array[--count_array[4              ]] = 4;
//                                  output_array[--2                           ] = 4;
//                                  output_array[1                             ] = 4;
// So at the 1th index(position) of the output array place the value 4
// Output array:       0, 4, 0, 0, 0, 0, 9,
// Count array summed: 0, 1, 1, 1, 2, 3, 5, 5, 5, 6,
// Count array summed: 0, 1, 1, 1, 1, 3, 5, 5, 5, 6,

// So if we have 5 value of unsorted array
// Index of count array summed says output_array[--count_array[RANDOM_ARRAY[i]]] = RANDOM_ARRAY[i];
//                                  output_array[--count_array[5              ]] = 5;
//                                  output_array[--3                           ] = 5;
//                                  output_array[2                             ] = 5;
// So at the 2th index(position) of the output array place the value 5
// Output array:       0, 4, 5, 0, 0, 0, 9,
// Count array summed: 0, 1, 1, 1, 1, 3, 5, 5, 5, 6,
// Count array summed: 0, 1, 1, 1, 1, 2, 5, 5, 5, 6,

// So if we have 6 value of unsorted array
// Index of count array summed says output_array[--count_array[RANDOM_ARRAY[i]]] = RANDOM_ARRAY[i];
//                                  output_array[--count_array[6              ]] = 6;
//                                  output_array[--5                           ] = 6;
//                                  output_array[4                             ] = 6;
// So at the 4th index(position) of the output array place the value 6
// Output array:       0, 4, 5, 0, 6, 0, 9,
// Count array summed: 0, 1, 1, 1, 1, 2, 5, 5, 5, 6,
// Count array summed: 0, 1, 1, 1, 1, 2, 4, 5, 5, 6,

// So if we have 6 value of unsorted array
// Index of count array summed says output_array[--count_array[RANDOM_ARRAY[i]]] = RANDOM_ARRAY[i];
//                                  output_array[--count_array[6              ]] = 6;
//                                  output_array[--4                           ] = 6;
//                                  output_array[3                             ] = 6;
// So at the 3th index(position) of the output array place the value 6
// Output array:       0, 4, 5, 6, 6, 0, 9,
// Count array summed: 0, 1, 1, 1, 1, 2, 4, 5, 5, 6,
// Count array summed: 0, 1, 1, 1, 1, 2, 3, 5, 5, 6,

// So if we have 9 value of unsorted array
// Index of count array summed says output_array[--count_array[RANDOM_ARRAY[i]]] = RANDOM_ARRAY[i];
//                                  output_array[--count_array[9              ]] = 9;
//                                  output_array[--6                           ] = 9;
//                                  output_array[5                             ] = 9;
// So at the 5th index(position) of the output array place the value 9
// Output array:       0, 4, 5, 6, 6, 9, 9,
// Count array summed: 0, 1, 1, 1, 1, 2, 3, 5, 5, 6,
// Count array summed: 0, 1, 1, 1, 1, 2, 3, 5, 5, 5,
void counting_sort(int MAXSIZE, int range, int RANDOM_ARRAY[])
{
	int *output_array = new int[MAXSIZE];

	int *count_array = new int[range];
	for (int i = 0; i < range; i++) //--------------------------------- Initialize count array with zeros
	{
		count_array[i] = 0;
	}

	for (int i = 0; i < MAXSIZE; i++) //------------------------------- Count the number of occurrences of each value
	{
		++count_array[RANDOM_ARRAY[i]];
	}

	// DEBUG PRINT
	cout << "Count array: ";
	print_array(range, count_array);
	cout << endl;

	for (int i = 1; i < range; i++) //--------------------------------- Modify the count array to contain the cumulative sum of counts, to get the positions of elements to be stored in the output array
	{
		count_array[i] = count_array[i] + count_array[i - 1];
	}

	// DEBUG PRINT
	cout << "Count array: ";
	print_array(range, count_array);
	cout << endl;

	for (int i = 0; i < MAXSIZE; i++) //------------------------------- Place the values in the output array in sorted order
	{
		output_array[--count_array[RANDOM_ARRAY[i]]] = RANDOM_ARRAY[i];
	}

	// DEBUG PRINT
	cout << "Output array: ";
	print_array(MAXSIZE, output_array);
	cout << endl;

	for (int i = 0; i < MAXSIZE; i++)  //------------------------------ Copy the sorted values back into the original array
	{
		RANDOM_ARRAY[i] = output_array[i];
	}

	delete[] output_array;
	delete[] count_array;
}

// For negative and positive numbers, it does this by subtracting the minimum value from each number before counting it, and then adding the minimum value back when placing the number in the output array.
void counting_sort_positive_negative(int MAXSIZE, int min_val, int max_val, int RANDOM_ARRAY[])
{
	int *output_array = new int[MAXSIZE];

	int range = max_val - min_val + 1;
	int *count_array = new int[range];
	for (int i = 0; i < range; i++) //------------------------------------------- Initialize count array with zeros
	{
		count_array[i] = 0;
	}

	for (int i = 0; i < MAXSIZE; i++) //----------------------------------------- Count the number of occurrences of each value
	{
		++count_array[RANDOM_ARRAY[i] - min_val];
	}

	for (int i = 1; i < range; i++) //------------------------------------------- Modify the count array to contain the cumulative sum of counts, to get the positions of elements to be stored in the output array
	{
		count_array[i] += count_array[i - 1];
	}

	for (int i = MAXSIZE - 1; i >= 0; i--) 	//----------------------------------- Place the values in the output array in sorted order
	{
		output_array[--count_array[RANDOM_ARRAY[i] - min_val]] = RANDOM_ARRAY[i];
	}

	for (int i = 0; i < MAXSIZE; i++) //----------------------------------------- Copy the sorted values back into the original array
	{
		RANDOM_ARRAY[i] = output_array[i];
	}

	delete[] output_array;
	delete[] count_array;
}
// O(n+k)
// Worst-case scenario

// O(n+k)
// Best-case scenario
//* Counting Sort

//* Radix Sort
// Radix sort is a non-comparative sorting algorithm.
// It avoids comparison by creating and distributing elements into buckets according to their radix.
// For elements with more than one significant digit, this bucketing process is repeated for each digit, while preserving the ordering of the prior step, until all digits have been considered.
// For this reason, radix sort has also been called bucket sort and digital sort.
// Typically Radix sort uses counting sort as a subroutine to sort.
// Radix sort has linear time complexity which is better than O(n log n) of comparative sorting algorithms.
// Time complexity : O(d(n + k))
// Where d is the no. of max digits of the largest no. in the digit, n is the no. of elements in the list and k is the range of unique elements.

// This version of the radix_sort function first finds the minimum and maximum values in the array.
// If the minimum value is non-negative, it applies the counting_sort_radix function as before.
// If the minimum value is negative, it splits the array into positive and negative numbers, sorts each of these arrays separately using radix sort, and then combines the sorted arrays.
// When it combines the sorted arrays, it negates the negative numbers again to restore their original sign, and arranges them in decreasing order so that they precede the positive numbers in the sorted array.

// Radix Sort
void radix_sort(int MAXSIZE, int RANDOM_ARRAY[])
{
	//int m = max(MAXSIZE, RANDOM_ARRAY);

	//for (int divide = 1; m / divide > 0; divide *= 10)
	//{
	//	counting_sort_radix(MAXSIZE, 10, divide, RANDOM_ARRAY);
	//}

	int min_val = *min_element(RANDOM_ARRAY, RANDOM_ARRAY + MAXSIZE);
	int max_val = *max_element(RANDOM_ARRAY, RANDOM_ARRAY + MAXSIZE);

	if (min_val >= 0) //---------------------------------------------- If array contains only positive numbers
	{
		for (int divide = 1; max_val / divide > 0; divide *= 10)
		{
			counting_sort_radix(MAXSIZE, 10, divide, RANDOM_ARRAY);
		}
	}
	else
	{
		vector<int> negatives, positives;

		for (int i = 0; i < MAXSIZE; i++) //-------------------------- Split the array into positive and negative numbers
		{
			if (RANDOM_ARRAY[i] < 0)
			{
				negatives.push_back(-RANDOM_ARRAY[i]); //------------- Radix sort is unable to handle negative numbers directly because it operates on individual digits, starting from the least significant digit. For negative numbers, it is unclear what it means to sort by individual digits. To resolve this, we take the absolute value of each negative number when storing it in the negatives vector. We do this by applying the unary minus operator - to RANDOM_ARRAY[i]
			}
			else
			{
				positives.push_back(RANDOM_ARRAY[i]);
			}
		}
		//------------------------------------------------------------ Sort the positive and negative arrays
		radix_sort(positives.size(), positives.data());
		radix_sort(negatives.size(), negatives.data());
		//------------------------------------------------------------ Combine sorted arrays
		for (int i = 0; i < negatives.size(); i++)
		{
			RANDOM_ARRAY[i] = -negatives[negatives.size() - 1 - i]; // We use -negatives[negatives.size() - 1 - i] to take the negative of each number (i.e., restore its original sign) and to index the negatives vector in reverse order (i.e., from the largest to the smallest number). The reason we order the negatives in reverse is because, after sorting, the largest negative number (which is closest to zero) should be placed first in the sorted array, and the smallest negative number (which is furthest from zero) should be placed last among the negative numbers.
		}

		for (int i = 0; i < positives.size(); i++)
		{
			RANDOM_ARRAY[i + negatives.size()] = positives[i];
		}
	}
}
// If m = 802;
// 802 / 1 = 802 > 0;
// 802 / 10 = 80 > 0;
// 802 / 100 = 8 > 0;
// 802 / 1000 = 0 > 0;

// The - sign in -negatives[negatives.size() - 1 - i] is used to restore the original negative sign of the numbers.
// This was initially reversed in the line negatives.push_back(-RANDOM_ARRAY[i]) to make sorting of negative numbers possible.
// The expression negatives.size() - 1 - i inside the square brackets is used to index the negatives vector in reverse order.
// The negatives.size() - 1 expression gives you the last index in the negatives vector(since array indices in C++ start from 0), and -i is used to traverse the vector backwards from the last index to the first index as i increases from 0 to negatives.size() - 1.

// Counting sort radix
void counting_sort_radix(int MAXSIZE, int range, int divide, int RANDOM_ARRAY[])
{
	cout << endl;

	int *output_array = new int[MAXSIZE];

	int *count_array = new int[range];
	for (int i = 0; i < range; i++) //--------------------------------------------------- Initialize count array with zeros
	{
		count_array[i] = 0;
	}

	for (int i = 0; i < MAXSIZE; i++) //------------------------------------------------- Count the number of occurrences of each value
	{
		count_array[(RANDOM_ARRAY[i] / divide) % 10]++;
	}

	// DEBUG PRINT
	cout << "Count array: ";
	print_array(range, count_array);
	cout << endl;

	for (int i = 1; i < range; i++) //--------------------------------------------------- Modify the count array to contain the cumulative sum of counts, to get the positions of elements to be stored in the output array
	{
		count_array[i] = count_array[i] + count_array[i - 1];
	}

	// DEBUG PRINT
	cout << "Count array: ";
	print_array(range, count_array);
	cout << endl;

	for (int i = MAXSIZE - 1; i >= 0; i--) //-------------------------------------------- Place the values in the output array in sorted order
	{
		output_array[count_array[(RANDOM_ARRAY[i] / divide) % 10] - 1] = RANDOM_ARRAY[i];
		count_array[(RANDOM_ARRAY[i] / divide) % 10]--;
	}

	// DEBUG PRINT
	cout << "Output array: ";
	print_array(MAXSIZE, output_array);
	cout << endl << endl;

	for (int i = 0; i < MAXSIZE; i++)  //------------------------------------------------ Copy the sorted values back into the original array
	{
		RANDOM_ARRAY[i] = output_array[i];
	}

	delete[] output_array;
	delete[] count_array;
}

// output_array[count_array[(RANDOM_ARRAY[i] / divide) % 10] - 1] = RANDOM_ARRAY[i];
// output_array[count_array[(802             / 1     ) % 10] - 1] = 802;
// output_array[count_array[(802                     ) % 10] - 1] = 802;
// output_array[count_array[2                              ] - 1] = 802;

// output_array[count_array[(RANDOM_ARRAY[i] / divide) % 10] - 1] = RANDOM_ARRAY[i];
// output_array[count_array[(802             / 10    ) % 10] - 1] = 802;
// output_array[count_array[(80                      ) % 10] - 1] = 802;
// output_array[count_array[0                              ] - 1] = 802;

// output_array[count_array[(RANDOM_ARRAY[i] / divide) % 10] - 1] = RANDOM_ARRAY[i];
// output_array[count_array[(802             / 100   ) % 10] - 1] = 802;
// output_array[count_array[(8                       ) % 10] - 1] = 802;
// output_array[count_array[8                              ] - 1] = 802;

// Get the max element in the array
int max(int size, int array[])
{
	int max = array[0];
	for (int i = 1; i < size; i++)
	{
		if (max < array[i])
		{
			max = array[i];
		}
	}
	return max;
}

// Get the min element in the array
int min(int size, int array[])
{
	int min = array[0];
	for (int i = 1; i < size; i++)
	{
		if (min > array[i])
		{
			min = array[i];
		}
	}
	return min;
}
// O(n+k)
// Worst-case scenario

// O(n+k)
// Best-case scenario
//* Radix Sort

// Shell Sort
// ShellSort is an in-place comparison sort.
// It is mainly a variation of sorting by exchange (bubble sort) or sorting by insertion (insertion sort).
// This algorithm avoids large shifts as in case of insertion sort, if the smaller value is to the far right and has to be moved to the far left.
// The idea of shell sort is to allow exchange of far items.
// This spacing is termed as interval or gap.
// ShellSort is more efficient compared to Insertion Sort or Bubble sort specially when –
// 1. Smaller value elements are towards the end of the array / list
// 2. Large sized array / list
// 3. Efficiency depends on how we select the GAP / interval
void shell_sort(int MAXSIZE, int RANDOM_ARRAY[])
{
	// DEBUG COUNTER
	int counter = 0;

	for (int gap = MAXSIZE / 2; gap > 0; gap /= 2) //------------------------- Initialize the value of gap/interval( aka do this until the gap is 0) If we have size = 10, we will iterate until 10 / 2 = 5; 5 / 2 = 2; 2 / 2 = 1; 1 / 2 = 0;
	{
		for (int j = gap; j < MAXSIZE; j += 1) //----------------------------- Compare two elements at the distance of the gap at every iteration (start from the gap, increase it by 1 for the next element)
		{
			int temp = RANDOM_ARRAY[j];
			int i = 0;

			for (i = j; i >= gap && RANDOM_ARRAY[i - gap] > temp; i -= gap) // If element at the left is larger than the element at the right preform swap
			{
				RANDOM_ARRAY[i] = RANDOM_ARRAY[i - gap];

				// DEBUG PRINT
				cout << "Step " << ++counter << ":         ";
				print_array(MAXSIZE, RANDOM_ARRAY);
				cout << endl;
			}

			RANDOM_ARRAY[i] = temp;
		}
	}
}
// THERE IS ALWAYS A GAP OF SOME VALUE BETWEEN ELEMENT COMPARISONS
// i = j; i >= gap && RANDOM_ARRAY[i - gap] > temp[j]; i -= gap
// RANDOM_ARRAY[i] = RANDOM_ARRAY[i - gap];
// RANDOM_ARRAY[i] = temp;

// GAP = 5; j = 5;
// i = 5; 5 >= 5   && RANDOM_ARRAY[0]       > temp[5]; 0;
// RANDOM_ARRAY[5] = RANDOM_ARRAY[0]; IF ABOVE TRUE THEN SWAP
// i = 0; 0 >= 5 X
// RANDOM_ARRAY[0] = temp[5]; WHEN WE FINISH THE INNER LOOP

// GAP = 5; j = 6;
// i = 6; 6 >= 5   && RANDOM_ARRAY[1]       > temp[6]; 1;
// RANDOM_ARRAY[6] = RANDOM_ARRAY[1];
// i = 1; 1 >= 5 X
// RANDOM_ARRAY[1] = temp[6];

// GAP = 5; j = 7;
// i = 7; 7 >= 5   && RANDOM_ARRAY[2]       > temp[7]; 2;
// RANDOM_ARRAY[7] = RANDOM_ARRAY[2];
// i = 2; 2 >= 5 X
// RANDOM_ARRAY[2] = temp[7];

// GAP = 5; j = 9;
// i = 9; 9 >= 5   && RANDOM_ARRAY[4]       > temp[9]; 4;
// RANDOM_ARRAY[9] = RANDOM_ARRAY[4];
// i = 4; 4 >= 5 X
// RANDOM_ARRAY[4] = temp[9];

// GAP = 2; j = 2;
// i = 2; 2 >= 2   && RANDOM_ARRAY[0]       > temp[2]; 0;
// RANDOM_ARRAY[2] = RANDOM_ARRAY[0];
// i = 0; 0 >= 2 X
// RANDOM_ARRAY[0] = temp[2];

// GAP = 2; j = 3;
// i = 3; 3 >= 2   && RANDOM_ARRAY[1]       > temp[3]; 1;
// RANDOM_ARRAY[3] = RANDOM_ARRAY[1];
// i = 1; 1 >= 2 X
// RANDOM_ARRAY[1] = temp[3];

// GAP = 2; j = 4;
// i = 4; 4 >= 2   && RANDOM_ARRAY[2]       > temp[4]; 2;
// RANDOM_ARRAY[4] = RANDOM_ARRAY[2];
// i = 2; 2 >= 2   && RANDOM_ARRAY[0]       > temp[4]; 0;
// RANDOM_ARRAY[2] = RANDOM_ARRAY[0];
// i = 0; 0 >= 2 X
// RANDOM_ARRAY[0] = temp[4];

// O(n^2)
// Worst-case scenario

// O(n log n)
// Best-case scenario

//* Heap sort
// Swap values
void swap(int &value1, int &value2)
{
	int temp = value1;
	value1 = value2;
	value2 = temp;
}

// Get the index of a left child
int left_child(int i)
{
	return  (2 * i) + 1;
}

// Get the index of a right child
int right_child(int i)
{
	return (2 * i) + 2;
}

// Min heapify
void min_heapify(int i, int MAXSIZE, int RANDOM_ARRAY[])
{
	int left_index = left_child(i);
	int right_index = right_child(i);
	int smallest = i;

	if (left_index < MAXSIZE && RANDOM_ARRAY[left_index] < RANDOM_ARRAY[smallest]) //-- Check if the left child is smaller than the new root, if it is make the smallest index be that left child
	{
		smallest = left_index;
	}

	if (right_index < MAXSIZE && RANDOM_ARRAY[right_index] < RANDOM_ARRAY[smallest]) // Check if the right child is smaller than the new root or its sibling (if the left child previously was smaller), if it is make the smallest index be that right child
	{
		smallest = right_index;
	}

	if (smallest != i) //-------------------------------------------------------------- Check if the smallest value is at the root position
	{
		swap(RANDOM_ARRAY[i], RANDOM_ARRAY[smallest]);
		min_heapify(smallest, MAXSIZE, RANDOM_ARRAY); //------------------------------- Recursively call the same function but for the swapped element, keep in mind after the swap we have now on the position of the smallest the value that was previously on the root
	}
}

// Heapify the array before sorting
void heapify(int MAXSIZE, int RANDOM_ARRAY[])
{
	for (int i = MAXSIZE / 2 - 1; i >= 0; i--) // Heapify all nodes from bottom to top and exclude the leaf level
	{
		min_heapify(i, MAXSIZE, RANDOM_ARRAY);
	}
}

// Extract min heap
int extract_min(int &MAXSIZE, int RANDOM_ARRAY[])
{
	if (MAXSIZE == 0)
	{
		return 0;
	}

	if (MAXSIZE == 1) //------------------------ If we have only one element
	{
		MAXSIZE--;
		return RANDOM_ARRAY[0];
	}

	//------------------------------------------ If we have more than one element
	int root = RANDOM_ARRAY[0];
	RANDOM_ARRAY[0] = RANDOM_ARRAY[MAXSIZE - 1];
	RANDOM_ARRAY[MAXSIZE - 1] = 0;
	MAXSIZE--;
	min_heapify(0, MAXSIZE, RANDOM_ARRAY); //--- Recreate the new heap data structure starting from the root
	return root;
}

// Heap sort
void heap_sort(int &MAXSIZE, int RANDOM_ARRAY[])
{
	int temp_size = MAXSIZE;

	int *temp = new int[MAXSIZE];
	for (int i = 0; i < MAXSIZE; i++)
	{
		temp[i] = extract_min(temp_size, RANDOM_ARRAY);
	}

	for (int i = 0; i < MAXSIZE; i++)
	{
		RANDOM_ARRAY[i] = temp[i];
	}

	delete[] temp;
}
// O(n log n)
// Worst-case scenario:

// Ω(n log n)
// Best-case scenario:
//* Heap sort