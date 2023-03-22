#include <iostream>
#include <fstream>
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

int main()
{
	Contact person = get_contact("Enter Contact: ");
	write_to_a_file(person);
	read_form_a_file();
	string name = get_delete_name();
	delete_from_file(name);

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
		if (line.find(name_to_delete) == string::npos)
		{
			temp_file << line << endl;
		}
		else
		{
			found = true;
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