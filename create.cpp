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

	string file_name = argv[1];

	ofstream new_file(file_name); //ofstream creates a file

	if (!new_file.is_open())
	{
		cerr << "Error 2: Can't open file " << file_name << endl;
		return 2;
	}

	new_file.close();

	return 0;
}