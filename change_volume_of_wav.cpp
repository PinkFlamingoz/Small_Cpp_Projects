#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Globals
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 4)
	{
		cerr << "Error 1: Enter only input wav and output wav name, with the factor! " << endl << "Usage: ./change_volume_of_wav [old_wav.wav] [new_wav.wav] [Factor]" << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	//* Open files --------------------------------------------------------------------------------------------------------------------------------------------

	// Open old_wav file
	ifstream old_wav_file(argv[1], ios::binary);
	if (!old_wav_file.is_open())
	{
		cerr << "Error 2:Cant open file " << argv[1] << endl;
		return 2;
	}

	// Open new_wav file
	ofstream new_wav_file(argv[2], ios::binary);
	if (!new_wav_file.is_open())
	{
		cerr << "Error 2:Cant open file " << argv[2] << endl;
		return 2;
	}
	//* Open files --------------------------------------------------------------------------------------------------------------------------------------------

	// Get the factor
	float factor = stof(argv[3]);

	//* Read and write header of a wav files ------------------------------------------------------------------------------------------------------------------
	uint8_t header[HEADER_SIZE]{};
	old_wav_file.read(reinterpret_cast<char *>(header), HEADER_SIZE);
	new_wav_file.write(reinterpret_cast<char *>(header), HEADER_SIZE);
	//* Read and write header of a wav files ------------------------------------------------------------------------------------------------------------------

	//* Read and write samples of a wav files -----------------------------------------------------------------------------------------------------------------
	int16_t buffer = 0;
	while (old_wav_file.read(reinterpret_cast<char *>(&buffer), sizeof(int16_t)))
	{
		buffer *= factor;
		new_wav_file.write(reinterpret_cast<char *>(&buffer), sizeof(int16_t));
	}
	//* Read and write samples of a wav files -----------------------------------------------------------------------------------------------------------------

	old_wav_file.close(); //--------------------------------------- Close old_bmp_image
	new_wav_file.close(); //--------------------------------------- Close new_bmp_image

	return 0; //--------------------------------------------------- Success
}
// WAV files are a common file format for representing audio.
// WAV files store audio as a sequence of “samples”: numbers that represent the value of some audio signal at a particular point in time.
// WAV files begin with a 44-byte “header” that contains information about the file itself, including the size of the file, the number of samples per second, and the size of each sample.
// After the header, the WAV file contains a sequence of samples, each a single 2-byte (16-bit) integer representing the audio signal at a particular point in time.
// Scaling each sample value by a given factor has the effect of changing the volume of the audio.Multiplying each sample value by 2.0, for example, will have the effect of doubling the volume of the origin audio.Multiplying each sample by 0.5, meanwhile, will have the effect of cutting the volume in half.