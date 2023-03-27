#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 2)
	{
		cerr << "Error 1: Enter only one argument! " << endl << "Usage: ./licence [filename.type] " << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	ifstream plates_file(argv[1]); //------------------------- Create a pointer to a file that the user entered

	if (!plates_file.is_open()) //---------------------------- Check if there was an error
	{
		cerr << "Error 2: Cant open file " << argv[1] << endl;
		return 2;
	}

	string buffer = "";
	vector <string> plates;
	int count = 0;

	while (getline(plates_file, buffer)) //------------------- While we keep reading from the file add each line from the file to the string buffer
	{
		plates.push_back(buffer); //-------------------------- Add the text in the buffer to the vector array
		count++; //------------------------------------------- Count how many new lines we have in the file
	}

	plates_file.close(); //----------------------------------- Close the file to free up memory

	for (int i = 0; i < count; i++) //------------------------ Print the plates in the vector array
	{
		cout << plates[i] << endl;
	}

	return 0; //---------------------------------------------- Success
}