#include<iostream>
#include<limits>
#include<string>
#include<math.h>

using namespace std;

string get_user_text();
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calculate_grade(int letters, int words, int sentences);
void print_results(int letters, int words, int sentences, int result);

int main() {
	// Get user input
	string text = get_user_text();
	// Count the letters, words, sentences
	int letters = count_letters(text);
	int words = count_words(text);
	int sentences = count_sentences(text);
	// Calculate grade
	int result = calculate_grade(letters, words, sentences);
	// Print results
	print_results(letters, words, sentences, result);

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

string get_user_text() {
	string text = get_valid_input<string>("Enter Text:");
	return text;
}

int count_letters(string text) {
	int count = 0;
	int lenght = text.length();

	for (int i = 0; i < lenght; i++) {
		if (isalpha(text[i])) {
			count++;
		}
	}
	return count;
}

int count_words(string text) {
	int count = 0;
	int lenght = text.length();
	int i = 0;
	while (isspace(text[i])) { // We use this to skip over if we have one or more spaces in the beginning of a sentence.
		i++;
	}

	for (i; i < lenght; i++) {
		if (isspace(text[i]) == isspace(text[i + 1])) { // We use this to skip over multiple spaces in between words. We also get a true here if both are not spaces, because we get false == false, but it doesnt matter.
			count += 0;
		}
		else if (isspace(text[i]) && (i != lenght - 1)) { // We count the space thats in between words only if that space is not the last space of the sentence. We do this for example if the user typed a extra spaces at the end of a sentence.
			count++;
		}
	}
	return count + 1; // We add the plus one to include the word at the begging that we never encounter a space for.
}

int count_sentences(string text) {
	int count = 0;
	int lenght = text.length();
	for (int i = 0; i < lenght; i++) {
		if (text[i] == text[i + 1]) { // We use this to skip over if we have multiple ... or ??? or !!! in one line.
			count += 0;
		}
		else if ((text[i] - text[i + 1]) == 13) { // A very non effcient way to check if we have the sequence of !. = -13; .?=-17; !?=-30; also the opposites, so if we have in a sentece ?!? it doenst count them as 3 seperate but only one.
			count += 0;
		}
		else if ((text[i] - text[i + 1]) == 17) {
			count += 0;
		}
		else if ((text[i] - text[i + 1]) == 30) {
			count += 0;
		}
		else if ((text[i] - text[i + 1]) == -13) {
			count += 0;
		}
		else if ((text[i] - text[i + 1]) == -17) {
			count += 0;
		}
		else if ((text[i] - text[i + 1]) == -30) {
			count += 0;
		}
		else if (text[i] == '!') {
			count++;
		}
		else if (text[i] == '?') {
			count++;
		}
		else if (text[i] == '.') {
			count++;
		}
	}
	return count;
}
int calculate_grade(int letters, int words, int sentences) {
	float l = (static_cast<float>(letters) / static_cast<float>(words)) * 100; // Where l is the average number of letters per 100 words in the text
	float s = (static_cast<float>(sentences) / static_cast<float>(words)) * 100; // Where s is the average number of sentences per 100 words in the text

	float result = (0.0588 * l) - (0.296 * s) - 15.8;
	result = round(result);
	return result;
}

void print_results(int letters, int words, int sentences, int result) {
	cout << letters << " Letters!" << endl;
	cout << words << " Words!" << endl;
	cout << sentences << " Sentences!" << endl;
	if (result < 1) {
		cout << "Before Grade 1" << endl;
	}
	else if (result > 16) {
		cout << "Grade 16+" << endl;
	}
	else {
		cout << "Grade " << result << endl;
	}
}