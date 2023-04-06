#include <iostream>
#include <math.h>
#include "basic_functions.h"

using namespace std;

// Functions
string get_user_text();
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calculate_grade(int letters, int words, int sentences);
void print_results(int letters, int words, int sentences, int result);

int main()
{
	string text = get_user_text(); //-------------------------- Get user input

	int letters = count_letters(text); //---------------------- Count the letters
	int words = count_words(text); //-------------------------- Count the words
	int sentences = count_sentences(text);	//----------------- Count the sentences

	int result = calculate_grade(letters, words, sentences); // Calculate grade

	print_results(letters, words, sentences, result); //------- Print results

	return 0; //----------------------------------------------- Success
}

// Get the user input
string get_user_text()
{
	string text = get_valid_input<string>("Enter Text:");
	return text;
}

// Count the letters by counting each alphabetical character in the string
int count_letters(string text)
{
	int count = 0;
	int length = text.length();

	for (int i = 0; i < length; i++)
	{
		if (isalpha(text[i]))
		{
			count++;
		}
	}
	return count;
}

// Count the words
int count_words(string text)
{
	int count = 0;
	int length = text.length();
	int i = 0;

	for (i; i < length; i++)
	{
		if (isspace(text[i]) == isspace(text[i + 1])) //-- We use this to skip over multiple spaces in between words. We also get a true here if both are not spaces, because we get false == false, but it doesnt matter.
		{
			count += 0;
		}
		else if (isspace(text[i])) // We count the space thats in between words.
		{
			count++;
		}
	}
	return count + 1; //---------------------------------- We add the plus one to include the word at the begging that we never encounter a space for.
}
/* This is if we dont have the get_valid_input_function
while (isspace(text[i])) // We use this to skip over if we have one or more spaces in the beginning of a sentence.
{
	i++;
}

for (int b = i; b < length; b++)
{
	if (isspace(text[b]) == isspace(text[b + 1])) // We use this to skip over multiple spaces in between words. We also get a true here if both are not spaces, because we get false == false, but it doesnt matter.
	{
		count += 0;
	}
	else if (isspace(text[b]) && (b != length - 1)) // We count the space thats in between words only if that space is not the last space of the sentence. We do this for example if the user typed a extra spaces at the end of a sentence.
	{
		count++;
	}
}
return count + 1; // We add the plus one to include the word at the begging that we never encounter a space for.
*/

// Count the sentences by counting if a character is a '. ! ?' and make sure that they dont count when they follow each other
int count_sentences(string text)
{
	int count = 0;
	int length = text.length();
	for (int i = 0; i < length; i++)
	{
		char current_char = text[i];
		char next_char = i < length - 1 ? text[i + 1] : '\0'; //-------------- Handle end of string
		if (current_char == '.' || current_char == '?' || current_char == '!')
		{
			if (next_char != '.' && next_char != '?' && next_char != '!')
			{
				count++;
			}
		}
	}
	return count;
}

// Calculate the grade
int calculate_grade(int letters, int words, int sentences)
{
	float l = (static_cast<float>(letters) / static_cast<float>(words)) * 100; //-- Where l is the average number of letters per 100 words in the text
	float s = (static_cast<float>(sentences) / static_cast<float>(words)) * 100; // Where s is the average number of sentences per 100 words in the text

	float result = (0.0588 * l) - (0.296 * s) - 15.8;
	result = round(result);
	return result;
}

// Print the results
void print_results(int letters, int words, int sentences, int result)
{
	cout << letters << " Letters!" << endl;
	cout << words << " Words!" << endl;
	cout << sentences << " Sentences!" << endl;
	if (result < 1)
	{
		cout << "Before Grade 1" << endl;
	}
	else if (result > 16)
	{
		cout << "Grade 16+" << endl;
	}
	else
	{
		cout << "Grade " << result << endl;
	}
}