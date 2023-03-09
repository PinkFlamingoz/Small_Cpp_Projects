#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <string>

using namespace std;

int get_number();
void random_array();
bool linear_search(int number);

const int MAXSIZE = 1000000;
int RANDOM_ARRAY[MAXSIZE];

int main() {
	random_array();
	int number = get_number();

	auto start = chrono::high_resolution_clock::now();

	linear_search(number);

	auto end = chrono::high_resolution_clock::now();

	auto elapsed_seconds = chrono::duration_cast<chrono::duration<double>>(end - start).count();

	cout << "Time took: " << elapsed_seconds << endl;

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

int get_number() {
	int number;
	do {
		number = get_valid_input<int>("Enter number: ");
	} while (number < 1 || number > MAXSIZE);
	return number;
}

void random_array() {
	srand(time(nullptr));
	for (int i = 0; i < MAXSIZE; i++) {
		RANDOM_ARRAY[i] = rand() % MAXSIZE;
	}
}

bool linear_search(int number) {
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (RANDOM_ARRAY[i] == number)
		{
			cout << "Found: " << RANDOM_ARRAY[i] << endl;
			return 0;
		}
	}
	cout << "Not found! " << endl;
	return 1;
}

// O(n)
// Worst-case scenario: We have to look through the entire array of n elements, either because the target element is the last element of the array or doesn’t exist in the array at all

// Ω(1)
// Best-case scenario: The target element is the first element of the array, and so we can stop looking immediately after we start