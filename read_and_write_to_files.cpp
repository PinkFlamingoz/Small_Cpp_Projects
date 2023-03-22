#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "basic_get_functions.h"

using namespace std;

struct Contact
{
	string name = "";
	long long phone = 0;
};

string file_name = "test.txt";

Contact get_contact(string prompt);
void write_to_a_file(Contact person);
void read_form_a_file();
string get_delete_name();
void delete_from_file(string name_to_delete);
void get_data_from_a_file(vector<string> &contacts);
void get_data_from_a_file2(string contacts_array[], int line_count);
void print(vector<string> &contacts, string contacts_array[], int line_count);

int main()
{
	Contact person = get_contact("Enter Contact: ");
	write_to_a_file(person);
	read_form_a_file();
	string name = get_delete_name();
	delete_from_file(name);
	vector<string> contacts;
	get_data_from_a_file(contacts);
	ifstream file(file_name);
	int line_count = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n');
	string *contacts_array = new string[line_count];
	get_data_from_a_file2(contacts_array, line_count);
	print(contacts, contacts_array, line_count);
	delete[]contacts_array;

	return 0;
}

Contact get_contact(string prompt)
{
	cout << prompt << endl;
	Contact person;

	person.name = get_valid_input<string>("Enter name: ");
	do
	{
		person.phone = get_valid_input<long long>("Enter phone: ");
	} while (person.phone < 1);

	return person;
}

string get_delete_name()
{
	string name = get_valid_input<string>("Delete a contact: ");
	return name;
}

void write_to_a_file(Contact person)
{
	// Writing to a file
	//ofstream file(file_name);
	// Writing to a file in append mode
	ofstream file(file_name, ios::app);
	if (file.is_open())
	{
		file << person.name << " : " << person.phone << endl;
		file.close();
	}
	else
	{
		cout << "Error: Failed to open file " << file_name << endl;
		return;
	}
}

void read_form_a_file()
{
	 // Reading from a file
	string line;
	ifstream file(file_name);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			cout << line << endl;
		}
		file.close();
	}
	else
	{
		cout << "Error: Unable to open file " << file_name << endl;
		return;
	}
}

void delete_from_file(string name_to_delete)
{
	// Open the input and output files
	ifstream file(file_name);
	ofstream temp_file("temp.txt");

	// Check if the files were opened successfully
	if (!file.is_open())
	{
		cout << "Error: Failed to open input file " << file_name << endl;
		return;
	}
	if (!temp_file.is_open())
	{
		cout << "Error: Failed to open output file temp.txt" << endl;
		return;
	}

	// Read each line from the input file
	string line;
	bool found = false;
	while (getline(file, line))
	{
		if (line.substr(0, line.find(":") - 1) == name_to_delete)
		{
			found = true;
		}
		else
		{
			temp_file << line << endl;
		}
	}

	// Close the input and output files
	file.close();
	temp_file.close();

	// Delete the original file if the name was found and rewrite it with the output file
	if (found)
	{
		remove(file_name.c_str()); // remove the original file
		rename("temp.txt", file_name.c_str()); // rename the output file to the original name
	}
	else
	{
		remove("temp.txt"); // delete the output file if the name was not found
	}
}

void get_data_from_a_file(vector<string> &contacts)
{
	string line;
	ifstream file(file_name);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			contacts.push_back(line);
		}
		file.close();
	}
	else
	{
		cout << "Error: Unable to open file " << file_name << endl;
		return;
	}
}
void get_data_from_a_file2(string contacts_array[], int line_count)
{
	string line;
	ifstream file(file_name);
	if (file.is_open())
	{
		int i = 0;
		while (getline(file, line) && i < line_count)
		{
			contacts_array[i] = line; // >> this command only reads till a white space so we cant use this
			i++;
		}
		file.close();
	}
	else
	{
		cout << "Error: Unable to open file " << file_name << endl;
		return;
	}
}
void print(vector<string> &contacts, string contacts_array[], int line_count)
{
	// Print the contents of the vector
	cout << "Contents of vector:" << endl;
	for (const auto &contact : contacts)
	{
		cout << contact << endl;
	}

	// Print the contents of the array
	cout << "Contents of array:" << endl;
	for (int i = 0; i < line_count; i++)
	{
		cout << contacts_array[i] << endl;
	}
}