#include<iostream>
#include<limits>

using namespace std;
string get_user_input();
bool check_alphabetic_order(string text);
string convert_to_uppercase(string text);
void print_result(bool result);

int main() {
	// Get user string
	string text = get_user_input();
	// Convert all to upper
	string formated = convert_to_uppercase(text);
	// Check if it is in alphabetical order
	bool result = check_alphabetic_order(formated);
	// Print true or false
	print_result(result);

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

string get_user_input() {
	string text = get_valid_input<string>("Enter string of text: ");
	return text;
}

string convert_to_uppercase(string text) {
	int length = text.length();
	for (int i = 0; i < length; i++) {
		text[i] = toupper(text[i]);
	}
	return text;
}

bool check_alphabetic_order(string text) {
	int length = text.length();
	for (int i = 0; i < length - 1; i++) {
		if (text[i] > text[i + 1]) {
			return false;
		}
	}
	return true;
}

void print_result(bool result) {
	if (result) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}
}