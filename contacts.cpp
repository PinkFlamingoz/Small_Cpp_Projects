#include <iostream>
#include <limits>

using namespace std;

string get_input_name();
int get_input_age();
long long get_input_number();
void print_confirmation(string name, int age, long long number);

int main() {
	// Get input
	string name = get_input_name();
	int age = get_input_age();
	long long number = get_input_number();

	// Print input for confirmation
	print_confirmation(name, age, number);
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

string get_input_name() {
	string name = get_valid_input<string>("Enter name: ");
	return name;
}

int get_input_age() {
	int age = get_valid_input<int>("Enter age: ");
	return age;
}

long long get_input_number() {
	long long number = get_valid_input<long long>("Enter number: ");
	return number;
}

void print_confirmation(string name, int age, long long number) {
	cout << "Name: " << name << endl << "Age: " << age << endl << "Number: " << number << endl;
}