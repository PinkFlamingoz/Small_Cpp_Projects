#include <iostream>
#include <limits>

using namespace std;

string get_user_password();
bool check_password(string password);
void print_error(bool uppercase, bool lowercase, bool number, bool symbol, bool length);

int main() {
	// Get password input
	// Check for password validation
	// Print results
	string password = get_user_password();

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

string get_user_password() {
	string password;
	do {
		password = get_valid_input<string>("Enter password: ");
	} while (!check_password(password));
	return password;
}

bool check_password(string password) {
	bool uppercase = false;
	bool lowercase = false;
	bool number = false;
	bool symbol = false;
	bool length = false;
	bool valid = false;

	int password_length = password.length();
	for (int i = 0; i < password_length; i++) {
		if (isupper(password[i])) {
			uppercase = true;
		}
		if (islower(password[i])) {
			lowercase = true;
		}
		if (isdigit(password[i])) {
			number = true;
		}
		if (!isalnum(password[i])) {
			symbol = true;
		}
		if (password_length >= 8) {
			length = true;
		}
	}
	print_error(uppercase, lowercase, number, symbol, length);
	if (uppercase && lowercase && number && symbol && length) {
		valid = true;
		cout << "Password is valid!" << endl;
	}

	return valid;
}

void print_error(bool uppercase, bool lowercase, bool number, bool symbol, bool length) {
	if (!uppercase) {
		cout << "Password needs one upper case!" << endl;
	}
	if (!lowercase) {
		cout << "Password needs one lower case!" << endl;
	}
	if (!number) {
		cout << "Password needs one number!" << endl;
	}
	if (!symbol) {
		cout << "Password needs one symbol!" << endl;
	}
	if (!length) {
		cout << "Password needs to be at least 8 characters!" << endl;
	}
}