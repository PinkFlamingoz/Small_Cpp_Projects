#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "wav.h"

using namespace std;

// Functions
bool check_format_for_wav(WAVHEADER header);
int32_t get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 3)
	{
		cerr << "Error 1: Enter only input wav and output wav name! " << endl << "Usage: ./reverse_wav_audio [old_wav.wav] [new_wav.wav] " << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	//* Open files --------------------------------------------------------------------------------------------------------------------------------------------

	// Open old_wav file
	ifstream old_wav_file(argv[1], ios::binary);
	if (!old_wav_file.is_open())
	{
		cerr << "Error 2: Cant open file " << argv[1] << endl;
		return 2;
	}
	//* Open files --------------------------------------------------------------------------------------------------------------------------------------------

	//* Read and write header of a wav files ------------------------------------------------------------------------------------------------------------------
	WAVHEADER header{};
	old_wav_file.read(reinterpret_cast<char *>(&header), sizeof(WAVHEADER));

	// Check if its a wav file
	if (!check_format_for_wav(header))
	{
		old_wav_file.close();
		return 3;
	}

	// Create new_wav file
	ofstream new_wav_file(argv[2], ios::binary);
	if (!new_wav_file.is_open())
	{
		cerr << "Error 2: Cant create file " << argv[2] << endl;
		old_wav_file.close();
		return 2;
	}

	new_wav_file.write(reinterpret_cast<char *>(&header), sizeof(WAVHEADER));
	//* Read and write header of a wav files ------------------------------------------------------------------------------------------------------------------

	//* Read and write samples of a wav files -----------------------------------------------------------------------------------------------------------------
	int32_t block_size = get_block_size(header); //----------------------------- Get the block size
	vector<int16_t> buffer(block_size); //-------------------------------------- Make a vector array to hold the sample data

	old_wav_file.seekg(block_size, ios::end); //-------------------------------- Tell the file pointer to point at (at beginning of the last audio block) the end of the file with an offset of block_size, this means the file will point block_size bytes before the end (if block_size is a positive number, if its a negative number it will point block_size bytes after the end)
	while (old_wav_file.tellg() - streamoff(block_size) > sizeof(WAVHEADER)) //- Do this until we reach the beginning of the header bytes of the old_wavfile
	{
		old_wav_file.seekg(-2 * block_size, ios::cur); //----------------------- The input pointer may need to be moved back two block sizes after each read, one to move back to where the fread began, and the second to move to the previous, unread block.
		old_wav_file.read(reinterpret_cast<char *>(buffer.data()), block_size);
		new_wav_file.write(reinterpret_cast<char *>(buffer.data()), block_size);
	}
	//* Read and write samples of a wav files -----------------------------------------------------------------------------------------------------------------

	old_wav_file.close(); // Close old_bmp_image
	new_wav_file.close(); // Close new_bmp_image

	return 0; //------------ Success
}

// Check if its a wav file
bool check_format_for_wav(WAVHEADER header)
{
	if (header.format[0] != 'W' && header.format[1] != 'A' && header.format[2] != 'V' && header.format[3] != 'E')
	{
		cerr << "Error 3: Unsupported file format." << endl;
		return false;
	}
	return true;
}

// Get the block size == NumChannels * BitsPerSample/8
int32_t get_block_size(WAVHEADER header)
{
	return header.blockAlign;
}