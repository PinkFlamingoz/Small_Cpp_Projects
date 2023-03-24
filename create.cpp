#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr << "Error 1: Enter only one argument! " << endl << "Usage: ./create [filename.type]" << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}

	ofstream new_file(argv[1]); //ofstream creates a file

	if (!new_file.is_open())
	{
		cerr << "Error 2: Cant open file " << argv[1] << endl;
		return 2;
	}

	new_file.close();

	return 0;
}