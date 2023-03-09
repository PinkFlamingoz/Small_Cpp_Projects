#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <string>

using namespace std;

constexpr auto GREEN = "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m";
constexpr auto RESET = "\e[0;39m";

void random_array();
void print_array();
void bubble_sort();
void selection_sort();
void merge(int start_point, int mid_point, int end_point, int RANDOM_ARRAY[]);
void merge_sort(int start_point, int end_point, int RANDOM_ARRAY[]);

const int MAXSIZE = 10;
int RANDOM_ARRAY[MAXSIZE];

int main() {
	// Bubble -----------------------------------------------------------------------------------------------------
	cout << endl;
	cout << "---------------- Bubble -----------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	random_array();
	cout << "Unsorted array: ";
	print_array();
	cout << endl;

	auto start1 = chrono::high_resolution_clock::now();

	bubble_sort();

	auto end1 = chrono::high_resolution_clock::now();

	auto elapsed_seconds1 = chrono::duration_cast<chrono::duration<double>>(end1 - start1).count();

	cout << "Sorted array:   ";
	print_array();

	cout << endl << "Time took for bubble sort: " << elapsed_seconds1 << endl;

	// Selection -----------------------------------------------------------------------------------------------------
	cout << endl;
	cout << "---------------- Selection --------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	random_array();
	cout << "Unsorted array: ";
	print_array();
	cout << endl;

	auto start2 = chrono::high_resolution_clock::now();

	selection_sort();

	auto end2 = chrono::high_resolution_clock::now();

	auto elapsed_seconds2 = chrono::duration_cast<chrono::duration<double>>(end2 - start2).count();

	cout << "Sorted array:   ";
	print_array();

	cout << endl << "Time took selection sort: " << elapsed_seconds2 << endl;

	// Merge -----------------------------------------------------------------------------------------------------
	cout << endl;
	cout << "---------------- Merge ------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	random_array();
	cout << "Unsorted array: ";
	print_array();
	cout << endl;

	auto start3 = chrono::high_resolution_clock::now();

	merge_sort(0, MAXSIZE - 1, RANDOM_ARRAY);

	auto end3 = chrono::high_resolution_clock::now();

	auto elapsed_seconds3 = chrono::duration_cast<chrono::duration<double>>(end3 - start3).count();

	cout << "Sorted array:   ";
	print_array();

	cout << endl << "Time took for merge sort: " << elapsed_seconds3 << endl;

	return 0;
}

void random_array() {
	srand(time(nullptr));
	for (int i = 0; i < MAXSIZE; i++) {
		RANDOM_ARRAY[i] = rand() % MAXSIZE;
	}
}

void print_array() {
	for (int i = 0; i < MAXSIZE; i++) {
		cout << RANDOM_ARRAY[i] << ", ";
		if (i == (MAXSIZE - 1) / 2) {
			cout << GREEN << "|" << RESET << " ";
		}
	}
}

void bubble_sort() {
	int counter = 0;
	int swap_counter = -1;											// Set swap counter to a non-zero value
	int help = 0;
	while (swap_counter != 0) {										// Repeat until the swap counter is 0
		swap_counter = 0;											// Reset swap counter to 0
		for (int i = 0; i < MAXSIZE - 1; i++) {
			if (RANDOM_ARRAY[i] > RANDOM_ARRAY[i + 1]) {			// Look at each adjacent pair
				help = RANDOM_ARRAY[i];
				RANDOM_ARRAY[i] = RANDOM_ARRAY[i + 1];				// If two adjacent elements are not in order, swap them
				RANDOM_ARRAY[i + 1] = help;
				swap_counter++;										// Add one to the swap counter
				// DEBUG PRINT
				counter++;
				cout << "Step " << counter << ":         ";
				print_array();
				cout << endl;
			}
		}
	}
}
// O(n^2)
// Worst-case scenario: The array is in reverse order; we have to “bubble” each of the n elements all the way across the array, and since we can only fully bubble one element into position per pass, we must do this n times

// Ω(n)
// Best-case scenario: The array is already perfectly sorted, and we make no swaps on the first pass

void selection_sort() {
	int counter = 0;
	int smallest_value = 0;
	int help = 0;
	for (int i = 0; i < MAXSIZE; i++) {
		smallest_value = i;											// We get the first element in the array
		for (int j = i + 1; j < MAXSIZE; j++) {						// j = i + 1 is used to compare the next number of the array and not to compare it with itself and not to repeat the same comparisons, its always +1 of the previous element, i represents the first value of the unsorted element
			if (RANDOM_ARRAY[smallest_value] > RANDOM_ARRAY[j]) {	// We compare that element with the rest of the array to see if its the smallest
				smallest_value = j;									// If we find a smaller one we make that the smallest
			}
		}
		if (smallest_value != i) {                                  // If the smallest value is not on the same position in the array then swap it
			help = RANDOM_ARRAY[i];
			RANDOM_ARRAY[i] = RANDOM_ARRAY[smallest_value];
			RANDOM_ARRAY[smallest_value] = help;
			// DEBUG PRINT
			counter++;
			cout << "Step " << counter << ":         ";
			print_array();
			cout << endl;
		}
	}
}
// O(n^2)
// Worst-case scenario: We have to iterate over each of the n elements of the array(to find the smallest unsorted element) and we must repeat this process n times, since only one element gets sorted on each pass

// Ω(n^2)
// Best-case scenario:  Exactly the same! There’s no way to guarantee the array is sorted until we go through this process for all the elements

void merge(int start_point, int mid_point, int end_point, int RANDOM_ARRAY[]) {
	int left_index = start_point;
	int right_index = mid_point + 1;
	int help_index = 0;
	int help[MAXSIZE] = {};

	while (left_index <= mid_point && right_index <= end_point) {
		if (RANDOM_ARRAY[left_index] <= RANDOM_ARRAY[right_index]) {
			help[help_index] = RANDOM_ARRAY[left_index];
			left_index++;
			help_index++;
		}
		else {
			help[help_index] = RANDOM_ARRAY[right_index];
			right_index++;
			help_index++;
		}
	}

	while (left_index <= mid_point) {
		help[help_index] = RANDOM_ARRAY[left_index];
		left_index++;
		help_index++;
	}

	while (right_index <= end_point) {
		help[help_index] = RANDOM_ARRAY[right_index];
		right_index++;
		help_index++;
	}

	for (int i = start_point; i <= end_point; i++) {
		RANDOM_ARRAY[i] = help[i - start_point];
	}
	// DEBUG PRINT
	//	cout << "Step:           ";
	//	print_array();
	//	cout << endl;
}

void merge_sort(int start_point, int end_point, int RANDOM_ARRAY[]) {
	int mid_point = 0;
	if (start_point < end_point) {
		mid_point = (start_point + end_point) / 2;
		merge_sort(start_point, mid_point, RANDOM_ARRAY);
		merge_sort(mid_point + 1, end_point, RANDOM_ARRAY);
		merge(start_point, mid_point, end_point, RANDOM_ARRAY);
	}
}
// O(n log n)
// Worst-case scenario: We have to split n elements up and then recombine them, effectively doubling the sorted subarrays as we build them up. (combining sorted 1 - element arrays into 2 - element arrays, combining sorted 2 - element arrays into 4 - element arrays…)

// Ω(n log n)
// Best-case scenario: The array is already perfectly sorted. But we still have to split and recombine it back together with this algorithm