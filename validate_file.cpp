#include <iostream>
#include <fstream>

using namespace std;

void check(uint8_t buffer[], bool &pdf, bool &jpg, bool &exe);
void print(bool pdf, bool jpg, bool exe, char *argv[]);

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr << "Error 1: Enter only one argument! " << endl << "Usage: ./validate_pdf [filename.type]" << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}

	ifstream file_to_test(argv[1], ios::binary);

	if (!file_to_test.is_open())
	{
		cerr << "Error 2:Cant open file " << argv[1] << endl;
		return 2;
	}

	bool pdf = true;
	bool jpg = true;
	bool exe = true;

	uint8_t buffer[4]{};
	file_to_test.read(reinterpret_cast<char *>(buffer), 4);
	file_to_test.close();

	check(buffer, pdf, jpg, exe);
	print(pdf, jpg, exe, argv);
}

void check(uint8_t buffer[], bool &pdf, bool &jpg, bool &exe)
{
	int length_of_signiture = 4;

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