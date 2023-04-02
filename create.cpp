#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 2)
	{
		cerr << "Error 1: Enter only one argument! " << endl << "Usage: ./create [filename.type]" << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	ofstream new_file(argv[1]); //---------------------------- ofstream creates a file called whatever input is in argv[1], new_file is a pointer to that file

	if (!new_file.is_open()) //------------------------------- Check if there was an error
	{
		cerr << "Error 2: Cant create file " << argv[1] << endl;
		return 2;
	}

	new_file.close(); //-------------------------------------- Close the file to free up memory

	return 0; //---------------------------------------------- Success
}