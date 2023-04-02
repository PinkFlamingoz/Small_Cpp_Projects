#include <iostream>
#include <fstream>
#include "bmp.h"

using namespace std;

// Functions
bool is_it_a_24_bit_uncompressed_BMP_4_0(BITMAPFILEHEADER bitmap_file_header, BITMAPINFOHEADER bitmap_info_header);

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 3)
	{
		cerr << "Error 1: Enter only input bmp image and output bmp image name! " << endl << "Usage: ./flip_bmp_images [old_bmp_image.bmp] [new_bmp_image.bmp]" << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	//* Open files --------------------------------------------------------------------------------------------------------------------------------------------

	// Open input file
	ifstream old_bmp_image(argv[1], ios::binary);
	if (!old_bmp_image.is_open())
	{
		cerr << "Error 2: Cant open file " << argv[1] << endl;
		return 2;
	}
	//* Open files --------------------------------------------------------------------------------------------------------------------------------------------

	//* Read the bits of the old file and store them in the Bit structure variables ---------------------------------------------------------------------------

	// Read old_bmp_image's BITMAPFILEHEADER
	BITMAPFILEHEADER bitmap_file_header{};
	old_bmp_image.read(reinterpret_cast<char *>(&bitmap_file_header), sizeof(BITMAPFILEHEADER));

	// Read old_bmp_image's BITMAPINFOHEADER
	BITMAPINFOHEADER bitmap_info_header{};
	old_bmp_image.read(reinterpret_cast<char *>(&bitmap_info_header), sizeof(BITMAPINFOHEADER));

	// Ensure old_bmp_image is (likely) a 24-bit uncompressed BMP 4.0
	if (!is_it_a_24_bit_uncompressed_BMP_4_0(bitmap_file_header, bitmap_info_header))
	{
		old_bmp_image.close();
		return 3;
	}
	//* Read the bits of the old file and store them in the Bit structure variables ---------------------------------------------------------------------------

	// Flip the image
	bitmap_info_header.biHeight *= -1;

	//* Write the bits for the new file from the previously made Bit structure variables ----------------------------------------------------------------------

	// Create output file if is_it_a_24_bit_uncompressed_BMP_4_0 of old_bmp image is true
	ofstream new_bmp_image(argv[2], ios::binary);
	if (!new_bmp_image.is_open())
	{
		cerr << "Error 2: Cant create file " << argv[2] << endl;
		old_bmp_image.close();
		return 2;
	}

	// Write new_bmp_image's BITMAPFILEHEADER
	new_bmp_image.write(reinterpret_cast<const char *>(&bitmap_file_header), sizeof(BITMAPFILEHEADER));

	// Write new_bmp_image's BITMAPINFOHEADER
	new_bmp_image.write(reinterpret_cast<const char *>(&bitmap_info_header), sizeof(BITMAPINFOHEADER));

	// Get and write the bits of the image from the old to the new
	int height = abs(bitmap_info_header.biHeight); //--------------------------------- Set hight to iterate over
	int width = bitmap_info_header.biWidth; //---------------------------------------- Set width to iterate over

	int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4; //----------------------- Determine padding for scanlines

	for (int i = 0; i < height; i++) //----------------------------------------------- Iterate over old_bmp_image's scanlines
	{
		for (int j = 0; j < width; j++) //-------------------------------------------- Iterate over pixels in scanline
		{
			// Temporary storage
			RGBTRIPLE triple{};

			// Read RGB triple from old_bmp_image
			old_bmp_image.read(reinterpret_cast<char *>(&triple), sizeof(RGBTRIPLE));

			// Write RGB triple to new_bmp_image
			new_bmp_image.write(reinterpret_cast<const char *>(&triple), sizeof(RGBTRIPLE));
		}

		// Skip over padding, if any
		old_bmp_image.seekg(padding, ios::cur);

		// Then add it back (to demonstrate how)
		for (int c = 0; c < padding; c++)
		{
			new_bmp_image.put(0x00);
		}
	}
	//* Write the bits for the new file from the previously made Bit structure variables ----------------------------------------------------------------------

	old_bmp_image.close(); // Close old_bmp_image
	new_bmp_image.close(); // Close new_bmp_image

	return 0; //------------- Success
}

// Ensure old_bmp_image is (likely) a 24-bit uncompressed BMP 4.0
bool is_it_a_24_bit_uncompressed_BMP_4_0(BITMAPFILEHEADER bitmap_file_header, BITMAPINFOHEADER bitmap_info_header)
{
	if (bitmap_file_header.bfType != 0x4d42 ||
		bitmap_file_header.bfOffBits != 54 ||
		bitmap_info_header.biSize != 40 ||
		bitmap_info_header.biBitCount != 24 ||
		bitmap_info_header.biCompression != 0)
	{
		cerr << "Error 3: Unsupported file format." << endl;
		return false;
	}
	return true;
}

// In the given code, abs is used to calculate the absolute value of bi.biHeight, which is the height of the image in pixels.
// This is necessary because BMP files can store images with either a "top-down" or "bottom-up" orientation.
// A positive value for bi.biHeight indicates a "bottom-up" image, while a negative value indicates a "top-down" image.
// By taking the absolute value of bi.biHeight, the code ensures that the loop that reads the image data will iterate over the correct number of scanlines regardless of the image orientation.
//
// ********************************************************************************************************************************************************************************************
//
// In the BMP file format, image data is stored in a series of scanlines.
// Each scanline contains a sequence of pixels, and each pixel contains one or more color components, depending on the pixel format used.
// In order to ensure that each scanline is aligned to a certain boundary(typically a multiple of 4 bytes),
// BMP files may include padding bytes at the end of each scanline.
//
// The padding is added so that the width of each scanline is a multiple of 4 bytes.
// This is important for performance reasons, as many graphics processing algorithms(e.g.image filters, compression) can operate more efficiently on memory blocks that are aligned to 4 - byte boundaries.
//
// The number of padding bytes for each scanline is calculated as (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4, and is stored in the variable padding.
// The code then skips over the padding bytes in the input file using the fseek function,
// and writes new padding bytes to the output file using a loop that writes zeroes.
//
// Skipping over the padding bytes is important, as they are not part of the actual image data and would otherwise be written to the output file as garbage data.
//
// The seekg function to move the input position indicator of an input file stream old_bmp_image by a certain number of bytes relative to its current position.
// In particular, padding is the number of bytes to move, and ios::cur specifies the reference point from which to move the input position indicator, which is the current position.
// Therefore, this line of code moves the input position indicator of the old_bmp_image file stream padding bytes forward from its current position.
// This line of code is typically used when working with bitmap image files that have padding bytes at the end of each row to ensure that each row of pixels is aligned on a specific byte boundary.
// By moving the input position indicator forward by the padding value, the code can skip over these padding bytes and correctly read the next row of pixels in the bitmap image.