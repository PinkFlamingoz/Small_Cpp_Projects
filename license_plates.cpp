#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr << "Error 1: Enter only one argument! " << endl << "Usage: ./licence [filename.type] " << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}

	ifstream plates_file(argv[1]);

	if (!plates_file.is_open())
	{
		cerr << "Error 2: Cant open file " << argv[1] << endl;
		return 2;
	}

	string line;
	vector <string> plates;
	int i = 0;

	while (getline(plates_file, line))
	{
		plates.push_back(line);
		i++;
	}

	plates_file.close();

	for (int i = 0; i < 8; i++)
	{
		cout << plates[i] << endl;
	}

	return 0;
}