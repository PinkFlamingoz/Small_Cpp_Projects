#include <iostream>
#include <fstream>

using namespace std;

// Functions
void check(uint8_t buffer[], bool &pdf, bool &jpg, bool &exe);
void print(bool pdf, bool jpg, bool exe, char *argv[]);

int main(int argc, char *argv[])
{   //* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 2)
	{
		cerr << "Error 1: Enter only one argument! " << endl << "Usage: ./validate_file [filename.type]" << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	ifstream file_to_test(argv[1], ios::binary); //--------------------- Set a pointer to a file and open it in binary mode

	if (!file_to_test.is_open()) //------------------------------------- Check if there was an error
	{
		cerr << "Error 2: Cant open file " << argv[1] << endl;
		return 2;
	}

	bool pdf = true;
	bool jpg = true;
	bool exe = true;

	uint8_t buffer[sizeof(int)]{}; //----------------------------------- Initialize a buffer to store the bits with size of int is 4 bytes thats 32bits
	file_to_test.read(reinterpret_cast<char *>(buffer), sizeof(int)); // Read and transfer the bits
	file_to_test.close(); //-------------------------------------------- Close the file to free up memory

	check(buffer, pdf, jpg, exe);//------------------------------------- Check what type is the file
	print(pdf, jpg, exe, argv); //-------------------------------------- Print the results

	return 0; //-------------------------------------------------------- Success
}

// Compare the buffer bits with the signature bits of a file
void check(uint8_t buffer[], bool &pdf, bool &jpg, bool &exe)
{
	int length_of_signiture = sizeof(int);

	uint8_t signature_PDF[] = { 37, 80, 68, 70 };
	uint8_t signature_JPG[] = { 255, 216, 255, 224 };
	uint8_t signature_EXE[] = { 77, 90, 144, 0 };

	for (int i = 0; i < length_of_signiture; i++)
	{
		if (buffer[i] != signature_PDF[i] && pdf == true)
		{
			pdf = false;
		}
		if (buffer[i] != signature_JPG[i] && jpg == true)
		{
			jpg = false;
		}
		if (buffer[i] != signature_EXE[i] && exe == true)
		{
			exe = false;
		}
		cout << "Buffer " << i << ": " << static_cast<int>(buffer[i]) << endl;
	}
}

// Print the results
void print(bool pdf, bool jpg, bool exe, char *argv[])
{
	if (pdf)
	{
		cout << "This " << argv[1] << " is a .pdf file" << endl;
	}
	else if (jpg)
	{
		cout << "This " << argv[1] << " is a .jpg file" << endl;
	}
	else if (exe)
	{
		cout << "This " << argv[1] << " is a .exe file" << endl;
	}
	else
	{
		cout << "Cant determine type of file " << argv[1] << endl;
	}
}