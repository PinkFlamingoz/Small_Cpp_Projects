#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// typedefs
typedef uint8_t BYTE;

// Globals
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 2)
	{
		cerr << "Error 1: Enter only the file you want to recover the images from! " << endl << "Usage: ./recover_jpg_images [Memory card]" << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	//* Open files --------------------------------------------------------------------------------------------------------------------------------------------

	// Open input file
	ifstream memory_card(argv[1], ios::binary);
	if (!memory_card.is_open())
	{
		cerr << "Error 2: Cant open file " << argv[1] << endl;
		return 2;
	}
	//* Open files --------------------------------------------------------------------------------------------------------------------------------------------

	// Create a storage space for the name of the image, so we can update that name as the images are recovered, increasing the counter as more images are found
	string image_name = "";
	int counter = 0;
	sprintf(&image_name[0], "%03i.jpg", counter); // Set the name of the first image

	// Create the first recoverd image
	ofstream recovered_image(image_name, ios::binary);
	if (!recovered_image.is_open())
	{
		cerr << "Error 2: Cant create file " << image_name << endl;
		memory_card.close();
		return 2;
	}

	// Conditions to check if we have the first image
	bool first_jpg = true;
	bool found = false;

	// Read from the memory card and create a image as we discover images
	BYTE buffer[BLOCK_SIZE]{}; //------------------------------------------------------------------------ Buffer to hold 512 Bytes of data

	while (memory_card.read(reinterpret_cast<char *>(buffer), BLOCK_SIZE)) //---------------------------- Read the data from the memory card till you have nothing more to read
	{
		if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // Check if its the start of a jpg
		{
			found = true; //----------------------------------------------------------------------------- We use this so we dont write in the starting surprises at the beginning of the memory card :D, but to start writing when we find the first image bits.

			// Initial first image
			if (first_jpg) //---------------------------------------------------------------------------- Write the first image we find
			{
				recovered_image.write(reinterpret_cast<char *>(buffer), BLOCK_SIZE);
				first_jpg = false; //-------------------------------------------------------------------- Initially this is true to get the first image data, after that this signifies the end of the bytes of the first image and tells the code to create a new file and to start adding data to that one
			}
			// The rest of the images
			else
			{
				recovered_image.close(); //-------------------------------------------------------------- Close recovered_image

				counter++; //---------------------------------------------------------------------------- Get the number for the next image
				sprintf(&image_name[0], "%03i.jpg", counter); //----------------------------------------- Set the name of the next image

				recovered_image.open(image_name, ios::binary); //---------------------------------------- Reassign the pointer to the next image
				if (!recovered_image.is_open())
				{
					cerr << "Error 2: Cant create file " << image_name << endl;
					memory_card.close();
					return 2;
				}

				recovered_image.write(reinterpret_cast<char *>(buffer), BLOCK_SIZE); //------------------ Write the first bytes of this next image
			}
		}
		else if (found) //------------------------------------------------------------------------------- Continue adding bytes until we find the next signature bytes
		{
			recovered_image.write(reinterpret_cast<char *>(buffer), BLOCK_SIZE);
		}
	}

	memory_card.close(); //---- Close memory_card
	recovered_image.close(); // Close recovered_image

	return 0; //--------------- Success
}

// The sprintf function will format the string "%03i.jpg" with the value of counter as an integer, and write it to the memory location specified by &image_name[0].
// This results in a string with a format like 001.jpg, 002.jpg, 003.jpg, and so on.
// The string &image_name[0] represents the memory address of the first character of the string.
// This is used as the first argument to sprintf, indicating where the formatted string should be written.
// The second argument "%03i.jpg" specifies the format of the output string.
// %03i means that the next argument after the format string, counter, will be printed with a minimum width of 3 digits and leading zeros if necessary, and will be interpreted as an integer.
// .jpg is a literal string that will be appended to the end of the formatted output.