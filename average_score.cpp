#include<iostream>
#include<limits>

using namespace std;

int get_number_of_subjects();
void enter_scores(int number, float scores[]);
float get_average(int number, float scores[]);
void print_average(int number, float scores[]);

int main() {
	const int number_of_subjects = get_number_of_subjects();
	float* scores = new float[number_of_subjects];
	// The error message "C++ expression must have a constant value" typically occurs when you try to use a variable where a constant value is required, such as when defining the size of an array.
	// To fix this error, you can use dynamic memory allocation to create an array of the appropriate size at runtime.
	enter_scores(number_of_subjects, scores);
	print_average(number_of_subjects, scores);
	delete[] scores;
	// Here, we have used the new operator to allocate an array of floats of size numberOfSubjects at runtime. Once we are done using the array, we use the delete[] operator to free the allocated memory.
	return 0;
}

template <typename T>
T get_valid_input(const string& prompt) {
	T input;
	while (true) {
		cout << prompt;
		if (cin >> input) {
			// The user entered a valid number
			break;
		}
		else {
			// The user did not enter a valid number
			cout << "Error: Please enter a valid input." << endl;
			cin.clear(); // Clear the error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any input in the buffer
		}
	}
	return input;
}

int get_number_of_subjects() {
	int number = 0;
	do
		number = get_valid_input<int>("Number of subjects?: ");
	while (number < 1);
	return number;
}

void enter_scores(int number, float scores[]) {
	for (int i = 0; i < number; i++) {
		scores[i] = get_valid_input<float>("Enter grade: ");
	}
}

float get_average(int number, float scores[]) {
	float sum = 0;
	for (int i = 0; i < number; i++) {
		sum += scores[i];
	}
	return sum / (float)number;
}

void print_average(int number, float scores[]) {
	for (int i = 0; i < number; i++) {
		cout << "Grade " << i + 1 << ": " << scores[i] << "\n";
	}
	cout << "Average is: " << get_average(number, scores) << "\n";
}