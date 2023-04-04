#include <iostream>
#include <fstream>
#include "bmp.h"
#include "basic_functions.h"

using namespace std;

// Functions
void colorize(int height, int width, RGBTRIPLE **&image);
bool is_it_a_24_bit_uncompressed_BMP_4_0(BITMAPFILEHEADER bitmap_file_header, BITMAPINFOHEADER bitmap_info_header);

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 3)
	{
		cerr << "Error 1: Enter only input bmp image and output bmp image name! " << endl << "Usage: ./change_pixel_color_of_bmp [old_bmp_image.bmp] [new_bmp_image.bmp]" << endl << "You entered " << argc - 1 << " arguments." << endl;
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

	// Get old_bmp_image's BITMAP FILE HEADER
	BITMAPFILEHEADER bitmap_file_header{};
	old_bmp_image.read(reinterpret_cast<char *>(&bitmap_file_header), sizeof(BITMAPFILEHEADER));

	// Get old_bmp_image's BITMAP INFO HEADER
	BITMAPINFOHEADER bitmap_info_header{};
	old_bmp_image.read(reinterpret_cast<char *>(&bitmap_info_header), sizeof(BITMAPINFOHEADER));

	// Ensure old_bmp_image is (likely) a 24-bit uncompressed BMP 4.0
	if (!is_it_a_24_bit_uncompressed_BMP_4_0(bitmap_file_header, bitmap_info_header))
	{
		old_bmp_image.close();
		return 3;
	}

	// Get the bits of the image
	int height = abs(bitmap_info_header.biHeight); //---------------------- Set hight for allocating memmory
	int width = bitmap_info_header.biWidth; //----------------------------- Set width for allocating memmory
	RGBTRIPLE **image = nullptr;
	allocate_memory_2D_array<RGBTRIPLE, int, int>(image, height, width); // Allocate Memory for image

	int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4; //------------ Determine padding for scanlines

	for (int i = 0; i < height; i++) //------------------------------------ Iterate over old_bmp_image's scanlines
	{
		// read row into pixel array
		old_bmp_image.read(reinterpret_cast<char *>(image[i]), sizeof(RGBTRIPLE) * width);

		// skip over padding
		old_bmp_image.seekg(padding, ios::cur);
	}
	//* Read the bits of the old file and store them in the Bit structure variables ---------------------------------------------------------------------------

	// Change the collor
	colorize(height, width, image);

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

	// Write new pixels to new_bmp_image
	for (int i = 0; i < height; i++)
	{
		// write row to new_bmp_image
		new_bmp_image.write(reinterpret_cast<char *>(image[i]), sizeof(RGBTRIPLE) * width);

		// write padding at end of row
		for (int c = 0; c < padding; c++)
		{
			new_bmp_image.put(0x00);
		}
	}
	//* Write the bits for the new file from the previously made Bit structure variables ----------------------------------------------------------------------

	free_allocate_memory_2D_array<RGBTRIPLE, int>(image, height); // Free memory for image
	old_bmp_image.close(); //--------------------------------------- Close old_bmp_image
	new_bmp_image.close(); //--------------------------------------- Close new_bmp_image

	return 0; //---------------------------------------------------- Success
}
// A digital image file is just a sequence of bits, arranged in some fashion.
// A 24-bit BMP file, then, is essentially just a sequence of bits, (almost) every 24 of which happen to represent some pixel's color.
// But a BMP file also contains some "metadata," information like an image's height and width.
// That metadata is stored at the beginning of the file in the form of two data structures generally referred to as "headers".
// The first of these headers, called BITMAPFILEHEADER, is 14 bytes long. (Recall that 1 byte equals 8 bits.)
// The second of these headers, called BITMAPINFOHEADER, is 40 bytes long.
// Immediately following these headers is the actual bitmap: an array of bytes, triples of which represent a pixel's color.
// You could represent a bitmap as a 2-dimensional array of pixels: where the image is an array of rows, each row is an array of pixels.

// Change the colors of the pixles
void colorize(int height, int width, RGBTRIPLE **&image)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00)
			{
				image[i][j].rgbtRed = 0x50;
				image[i][j].rgbtGreen = 0xC8;
				image[i][j].rgbtBlue = 0x78;
			}
		}
	}
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