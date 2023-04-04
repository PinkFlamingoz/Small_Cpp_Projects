#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "basic_functions.h"

using namespace std;

// Structures
struct Contact
{
	string name = "";
	long long phone = 0;
};

// Functions
Contact get_contact(string prompt);
string get_delete_name();
void write_to_a_file(Contact person);
void read_form_a_file();
void delete_from_file(string name_to_delete);
void get_data_from_a_file(vector<string> &contacts);
void get_data_from_a_file2(string contacts_array[], int line_count);
void print(vector<string> &contacts, string contacts_array[], int line_count);

// Globals
string file_name = "test.txt";

int main()
{
	Contact person = get_contact("Enter Contact: "); //------------------------------------------- Get the contact that we want to enter into the file

	write_to_a_file(person); //------------------------------------------------------------------- Write the contact into the file

	read_form_a_file(); //------------------------------------------------------------------------ Print out the contacts from the file

	string name = get_delete_name(); //----------------------------------------------------------- Get the name of the contact we want to delete from the file
	delete_from_file(name); //-------------------------------------------------------------------- Delete that name in the file by making a temporery file with that name not in it and then just rename it to the original name

	vector<string> contacts; //------------------------------------------------------------------- Create a vector array to store the contacts from the file
	get_data_from_a_file(contacts); //------------------------------------------------------------ Push the contacts into the vector array

	ifstream file(file_name); //------------------------------------------------------------------ Open the file so we can count how many new lines it has (in such way we count how many contacts we have)
	int line_count = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n'); // Count the lines with the function count
	string *contacts_array = new string[line_count]; //------------------------------------------- Make a dynamic array with that size

	get_data_from_a_file2(contacts_array, line_count); //----------------------------------------- Push the contacts in the dynamic array

	print(contacts, contacts_array, line_count); //----------------------------------------------- Print the contents of the vector array and dynamic array

	delete[]contacts_array; //-------------------------------------------------------------------- Free up the allocated memory

	file.close(); //------------------------------------------------------------------------------ Close the file to free up memory

	return 0; //---------------------------------------------------------------------------------- Success
}
// The count function takes three arguments: a pair of iterators that define a range to search, and a value to count.
// In this case, the first iterator is created by constructing an istreambuf_iterator<char> object from the file input stream.
// This iterator reads characters from the file one at a time, and it's used as the starting point for the range to search.
// The second iterator is the default constructor for istreambuf_iterator<char>, which creates an end-of-stream iterator.
// This iterator is used to mark the end of the range to search.
// The third argument is the value to count, which is the newline character '\n'.

// Get the contact that we want to enter into the file
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

// Get the name we want to delete from the file
string get_delete_name()
{
	string name = get_valid_input<string>("Delete a contact: ");
	return name;
}

// Write the contact to a file
void write_to_a_file(Contact person)
{
	// Writing to a file
	// ofstream file(file_name);

	// Writing to a file in append mode
	ofstream file(file_name, ios::app);
	if (!file.is_open())
	{
		cerr << "Error: Failed to open file " << file_name << endl;
		return;
	}
	file << person.name << " : " << person.phone << endl;
	file.close();
}

// Read the contacts from a file
void read_form_a_file()
{
	// Reading from a file
	string buffer = "";
	ifstream file(file_name);
	if (!file.is_open())
	{
		cerr << "Error: Cant open file " << file_name << endl;
		return;
	}
	while (getline(file, buffer))
	{
		cout << buffer << endl;
	}
	file.close();
}

// Delete a contact from a file
void delete_from_file(string name_to_delete)
{
	// Open the input and output files
	ifstream file(file_name);
	ofstream temp_file("temp.txt");

	// Check if the files were opened successfully
	if (!file.is_open())
	{
		cerr << "Error: Failed to open input file " << file_name << endl;
		return;
	}
	if (!temp_file.is_open())
	{
		cerr << "Error: Failed to open output file temp.txt" << endl;
		return;
	}

	// Read each line from the input file
	string buffer = "";
	bool found = false;
	while (getline(file, buffer))
	{
		if (buffer.substr(0, buffer.find(":") - 1) == name_to_delete)
		{
			found = true; // If we find a name to delete, change the found to true so we can rename the temp file to the original and if not just delete the temp file
		}
		else
		{
			temp_file << buffer << endl;
		}
	}
	// substr string buffer, finds the position of the first occurrence of the character ':' in the string using the find method,
	// and then extracts a substring from the beginning of the original string up to one character before the position of the ':' character.

	file.close(); //----- Close the input
	temp_file.close(); // Close output files

	// Delete the original file if the name was found and rewrite it with the temp file
	if (found)
	{
		remove(file_name.c_str()); //------------ Remove the original file
		rename("temp.txt", file_name.c_str()); // Rename the output file to the original name
	}
	else
	{
		remove("temp.txt"); //------------------- Delete the output file if the name was not found
	}
}

// Get contacts from the file and push each new line into the vector array
void get_data_from_a_file(vector<string> &contacts)
{
	string buffer = "";
	ifstream file(file_name);
	if (!file.is_open())
	{
		cerr << "Error: Cant open file " << file_name << endl;
		return;
	}
	while (getline(file, buffer))
	{
		contacts.push_back(buffer);
	}
	file.close();
}

// Get contacts from the file array and push each new line into the dynamic array
void get_data_from_a_file2(string contacts_array[], int line_count)
{
	string buffer = "";
	ifstream file(file_name);
	if (!file.is_open())
	{
		cerr << "Error: Cant open file " << file_name << endl;
		return;
	}
	int i = 0;
	while (getline(file, buffer) && i < line_count)
	{
		contacts_array[i] = buffer; // ">>" this command only reads till a white space so we cant use this
		i++;
	}
	file.close();
}

// Print the contents of both arrays
void print(vector<string> &contacts, string contacts_array[], int line_count)
{
	cout << "Contents of vector:" << endl; // Print the contents of the vector
	for (const auto &contact : contacts)
	{
		cout << contact << endl;
	}

	cout << "Contents of array:" << endl; //- Print the contents of the array
	for (int i = 0; i < line_count; i++)
	{
		cout << contacts_array[i] << endl;
	}
}

// Get/Put And Other Special Operations
//
// The class ifstream has an internal get position that contains the location of the element / character to be read in the file in the next input operation.
// The class ofstream has an internal put position that contains the location of the element / character to be written in the next output operation.
// Incidentally, fstream has both get and put positions.
// To facilitate reading and writing using these positions, we have a few member functions that are used to observe and modify these positions.
// These functions are listed below :
//
// Functions	            Description
// tellg()	                Returns current position of get pointer
// tellp()	                Returns current position of put pointer
// seekg(position)	        Moves get a pointer to specified location counting from the beginning of the file
// seekg(offset, direction)	Moves get a pointer to offset value relative to the point given by parameter direction.
// seekp(position)	        Moves put a pointer to specified location counting from the beginning of the file
// seekp(offset, direction)	Moves put a pointer to offset value relative to the point given by parameter direction.
//
// The parameter direction given in the above function prototypes is an enumerated type of type seekdir and it determines the point from which the offset is counted.
// It can have the following values.
//
// ios::beg	Offset from beginning of the stream
// ios::cur	Offset from current position
// ios::end	Offset from the end of the stream
//
// ****************************************************************************************************************************************************************************
//
// File State Slags
//
// There are some member functions that are used to check the state of the file. All these functions return a Boolean value.
//
// Function	Description
// eof()	Returns true if the end of file is reached while reading the file.
// fail()	Returns true when read / write operation fails or format error occurs
// bad()	Returns true if reading from or writing to a file fail.
// good()	Returns  false  in the same cases in which calling any of the above functions would return true.
//
// ****************************************************************************************************************************************************************************
//
// The general syntax to open a file with the stream is:
//
// void open(const char *filename, ios::open mode mode)
//
// filename = > The string containing path and name of the file to be opened.
// mode = > Optional parameter indicating the mode in which the file is to be opened.
// C++ supports various modes in which the file can be opened. We can also specify a combination of these modes using the OR operator.
//
// File mode	Description
// ios::in	    Opens the file in input mode for reading.
// ios::out	    Opens the file in output mode for writing data to file.
// ios::ate	    Set initial position at the end of the file. If the end of file flag is not set, the initial position is set to the beginning of the file.
// ios::trunc	If the file is opened for writing and already has contents, the contents are truncated.
// ios::app	    Opens the file in append mode such that all contents are appended at the end of the file.
// ios::binary	Opens file in binary mode.
//
// file.open("myfile.dat", ios::in|ios::out|ios::app|ios::binary);
// fstream file("myfile.dat", |ios::app|ios::binary);
//
// Class	Default mode
// Ifstream	ios::in
// ofstream	ios::out
// fstream	ios::in | ios::out
//
// ****************************************************************************************************************************************************************************
//
// get size of file in bytes:
//
// infile.seekg(0, infile.end);
// long size = infile.tellg();
// infile.seekg(0);
//
// char *buffer = new char[size]; Allocate memory for file content
//
// infile.read(buffer, size);     Read content of infile:
//
// outfile.write(buffer, size);   Write to outfile:
//
// delete[] buffer;               Release dynamically-allocated memory:
//
// outfile.close();
// infile.close();
//
// Manual way to count the new lines in a file
//
// int count = 0;
// while (getline(infile, buffer))
// {
//	 count++; //------------------------------------------- Count how many new lines we have in the file
// }