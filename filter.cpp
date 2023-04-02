#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>
#include "bmp.h"
#include "basic_functions.h"

using namespace std;

// Functions
bool check_correct_filter(string option);
bool is_it_a_24_bit_uncompressed_BMP_4_0(BITMAPFILEHEADER bitmap_file_header, BITMAPINFOHEADER bitmap_info_header);
void filter(string option, int height, int width, RGBTRIPLE **&image);
void cap_to_max_value(int &R, int &G, int &B);
void set_the_new_RGB_values(int R, int G, int B, int i, int j, RGBTRIPLE **&image);
void copy_image_pixels(int height, int width, RGBTRIPLE **&image, RGBTRIPLE **&image_copy);
void grayscale(int height, int width, RGBTRIPLE **&image);
void sepia(int height, int width, RGBTRIPLE **&image);
void reflect(int height, int width, RGBTRIPLE **&image);
void blur(int height, int width, RGBTRIPLE **&image);
void edges(int height, int width, RGBTRIPLE **&image);

// Globals
vector<string> FILTERS = { "g","s","r","b","e" };

int main(int argc, char *argv[])
{
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------
	if (argc != 4)
	{
		cerr << "Error 1: Enter the filter, input bmp image and output bmp image name! " << endl << "Usage: ./filter [filter tag] [old_bmp_image.bmp] [new_bmp_image.bmp]" << endl << "You entered " << argc - 1 << " arguments." << endl;
		return 1;
	}

	// Make sure the user enters correct filter
	string option = argv[1];
	if (!check_correct_filter(option))
	{
		return 4;
	}
	//* Ensure proper usage -----------------------------------------------------------------------------------------------------------------------------------

	//* Open files --------------------------------------------------------------------------------------------------------------------------------------------

	// Open input file
	ifstream old_bmp_image(argv[2], ios::binary);
	if (!old_bmp_image.is_open())
	{
		cerr << "Error 2: Cant open file " << argv[2] << endl;
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

	// Apply Filter
	filter(option, height, width, image);

	//* Write the bits for the new file from the previously made Bit structure variables ----------------------------------------------------------------------

	// Create output file if is_it_a_24_bit_uncompressed_BMP_4_0 of old_bmp image is true
	ofstream new_bmp_image(argv[3], ios::binary);
	if (!new_bmp_image.is_open())
	{
		cerr << "Error 2: Cant create file " << argv[3] << endl;
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

// Check input for options
bool check_correct_filter(string option)
{
	// Make sure user enters correct filter, find will return the last element in the vector array if it doesnt find the value that the user inputed
	transform(option.begin(), option.end(), option.begin(), ::tolower);
	if (find(FILTERS.begin(), FILTERS.end(), option) == FILTERS.end())
	{
		cerr << "Error 4: Incorrect filter type. " << endl;
		cout << "To use Grayscale enter command:  g" << endl;
		cout << "To use Sepia enter command:      s" << endl;
		cout << "To use Reflection enter command: r" << endl;
		cout << "To use Blur enter command:       b" << endl;
		cout << "To use Edges enter command:      e" << endl;

		return false;
	}
	return true;
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

// Apply filter
void filter(string option, int height, int width, RGBTRIPLE **&image)
{
	// Filter image
	switch (option[0])
	{
		// Grayscale
		case 'g':
		{
			grayscale(height, width, image);
			break;
		}
		// Sepia
		case 's':
		{
			sepia(height, width, image);
			break;
		}
		// Reflection
		case 'r':
		{
			reflect(height, width, image);
			break;
		}
		// Blur
		case 'b':
		{
			blur(height, width, image);
			break;
		}
		// Edges
		case 'e':
		{
			edges(height, width, image);
			break;
		}
	}
}

// If or color get a value more than 255 cap it to 255
void cap_to_max_value(int &R, int &G, int &B)
{
	R > 255 ? R = 255 : R;
	G > 255 ? G = 255 : G;
	B > 255 ? B = 255 : B;
}

// Set the new RBG values
void set_the_new_RGB_values(int R, int G, int B, int i, int j, RGBTRIPLE **&image)
{
	image[i][j].rgbtRed = R;
	image[i][j].rgbtGreen = G;
	image[i][j].rgbtBlue = B;
}

// Copy image pixels
void copy_image_pixels(int height, int width, RGBTRIPLE **&image, RGBTRIPLE **&image_copy)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			image_copy[i][j] = image[i][j];
		}
	}
}

// Convert image to grayscale
// If the red, green, and blue values are all set to 0x00 (hexadecimal for 0), then the pixel is black.
// And if all values are set to 0xff (hexadecimal for 255), then the pixel is white.
// So long as the red, green, and blue values are all equal, the result will be varying shades of gray along the black-white spectrum, with higher values meaning lighter shades (closer to white) and lower values meaning darker shades (closer to black).
// To ensure each pixel of the new image still has the same general brightness or darkness as the old image, we can take the average of the red, green, and blue values to determine what shade of grey to make the new pixel.
void grayscale(int height, int width, RGBTRIPLE **&image)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float red = image[i][j].rgbtRed;
			float green = image[i][j].rgbtGreen;
			float blue = image[i][j].rgbtBlue;
			int average = round((red + green + blue) / 3.0);
			set_the_new_RGB_values(average, average, average, i, j, image);
		}
	}
}

// Convert image to sepia
// An image can be converted to sepia by taking each pixel, and computing new red, green, and blue values based on the original values of the three.
// There are a number of algorithms for converting an image to sepia, we will use the following in the function.
// The result of each of these formulas may not be an integer, but each value could be rounded to the nearest integer.
// It’s also possible that the result of the formula is a number greater than 255, the maximum value for an 8-bit color value.
// In that case, the red, green, and blue values should be capped at 255
void sepia(int height, int width, RGBTRIPLE **&image)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int sepia_Red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
			int sepia_Green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
			int sepia_Blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
			cap_to_max_value(sepia_Red, sepia_Green, sepia_Blue);
			set_the_new_RGB_values(sepia_Red, sepia_Green, sepia_Blue, i, j, image);
		}
	}
}

// Reflect image horizontally
// We do this by reversing the pixel order for each row in the image.
void reflect(int height, int width, RGBTRIPLE **&image)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width / 2; j++)
		{
			RGBTRIPLE help;
			help = image[i][j];
			image[i][j] = image[i][width - j - 1];
			image[i][width - j - 1] = help;
		}
	}
}

// Blur image
// We’ll use the “box blur,” which works by taking each pixel and, for each color value, giving it a new value by averaging the color values of neighboring pixels.
void blur(int height, int width, RGBTRIPLE **&image)
{
	RGBTRIPLE **image_copy = nullptr;
	allocate_memory_2D_array<RGBTRIPLE, int, int>(image_copy, height, width);

	copy_image_pixels(height, width, image, image_copy); //---------------------------- We have to make a temporary copy of the image because we edit each pixel for the original image, and we need the surrounding pixels unchanged to compute the new RGB values

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float reds = 0;
			float greens = 0;
			float blues = 0;
			float pixel_count = 0;
			for (int c = -1; c < 2; c++)
			{
				for (int d = -1; d < 2; d++)
				{
					if (c + i < 0 || c + i >= height || d + j < 0 || d + j >= width)
					{
						continue;
					}
					reds += image_copy[c + i][d + j].rgbtRed;                        // Get the RGB values around the pixel location at image_copy[i][j]
					greens += image_copy[c + i][d + j].rgbtGreen;                    // Example :
					blues += image_copy[c + i][d + j].rgbtBlue;                      //  [G][G]X
					pixel_count++;                                                   //  [G][T]X
				}                                                                    //  [G][G]X
			}
			int new_red = round(reds / pixel_count); //-------------------------------- Compute the average of all the gathered reds, greens and blues for the pixel location at image_copy[i][j]
			int new_green = round(greens / pixel_count);
			int new_blue = round(blues / pixel_count);
			set_the_new_RGB_values(new_red, new_green, new_blue, i, j, image); //------ Set the new values of that pixel in the original image
		}
	}

	free_allocate_memory_2D_array<RGBTRIPLE, int>(image_copy, height);
}

// Detect edges, one way to achieve this effect is by applying the Sobel operator to the image. https://en.wikipedia.org/wiki/Sobel_operator
// Like image blurring, edge detection also works by taking each pixel, and modifying it based on the 3x3 grid of pixels that surrounds that pixel.
// But instead of just taking the average of the nine pixels, the Sobel operator computes the new value of each pixel by taking a weighted sum of the values for the surrounding pixels.
// And since edges between objects could take place in both a vertical and a horizontal direction, we’ll actually compute two weighted sums: one for detecting edges in the x direction, and one for detecting edges in the y direction.
//
// In short, for each of the three color values for each pixel, we’ll compute two values Gx and Gy.
// To compute Gx for the red channel value of a pixel, for instance, we’ll take the original red values for the nine pixels that form a 3x3 box around the pixel, multiply them each by the corresponding value in the Gx matrix, and take the sum of the resulting values.
//
// Why these particular values for the matrix?
// In the Gx direction, for instance, we’re multiplying the pixels to the right of the target pixel by a positive number, and multiplying the pixels to the left of the target pixel by a negative number.
// When we take the sum, if the pixels on the right are a similar color to the pixels on the left, the result will be close to 0 (the numbers cancel out).
// But if the pixels on the right are very different from the pixels on the left, then the resulting value will be very positive or very negative, indicating a change in color that likely is the result of a boundary between objects.
// And a similar argument holds true for calculating edges in the y direction.
//
// Using these matrices, we can generate a Gx and Gy value for each of the red, green, and blue channels for a pixel.
// But each channel can only take on one value, not two : so we need some way to combine Gx and Gy into a single value.
// The Sobel filter algorithm combines Gx and Gy into a final value by calculating the square root of Gx^2 + Gy^2.
// And since channel values can only take on integer values from 0 to 255, the resulting value is rounded to the nearest integer and capped at 255!
void edges(int height, int width, RGBTRIPLE **&image)
{
	float G_x[3][3] = { {-1, 0, 1},
						{-2, 0, 2},
						{-1, 0, 1}
	};
	float G_y[3][3] = { {-1, -2, -1},
						{0, 0, 0},
						{1, 2, 1}
	};

	RGBTRIPLE **image_copy = nullptr;
	allocate_memory_2D_array<RGBTRIPLE, int, int>(image_copy, height, width);

	copy_image_pixels(height, width, image, image_copy); //---------------------------- We have to make a temporary copy of the image because we edit each pixel for the original image, and we need the surrounding pixels unchanged to compute the new RGB values

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float reds_x = 0;
			float greens_x = 0;
			float blues_x = 0;
			float reds_y = 0;
			float greens_y = 0;
			float blues_y = 0;
			for (int c = -1; c < 2; c++)
			{
				for (int d = -1; d < 2; d++)
				{
					if (c + i < 0 || c + i >= height || d + j < 0 || d + j >= width)
					{
						continue;
					}
					reds_x += image_copy[c + i][d + j].rgbtRed * G_x[c + 1][d + 1];                     // Get the RGB values around the pixel location at image_copy[i][j]
					greens_x += image_copy[c + i][d + j].rgbtGreen * G_x[c + 1][d + 1];                 // Example :
					blues_x += image_copy[c + i][d + j].rgbtBlue * G_x[c + 1][d + 1];					//  [G][G]X
					reds_y += image_copy[c + i][d + j].rgbtRed * G_y[c + 1][d + 1];						//  [G][T]X
					greens_y += image_copy[c + i][d + j].rgbtGreen * G_y[c + 1][d + 1];					//  [G][G]X
					blues_y += image_copy[c + i][d + j].rgbtBlue * G_y[c + 1][d + 1];
				}
			}
			int new_red = round(sqrt(pow(reds_x, 2) + pow(reds_y, 2))); //-------------------------------- Compute all the gathered reds, greens and blues for the pixel location at image_copy[i][j]
			int new_green = round(sqrt(pow(greens_x, 2) + pow(greens_y, 2)));
			int new_blue = round(sqrt(pow(blues_x, 2) + pow(blues_y, 2)));
			cap_to_max_value(new_red, new_green, new_blue); //-------------------------------------------- Cap the values so we dont get anything abouve 255
			set_the_new_RGB_values(new_red, new_green, new_blue, i, j, image); //------------------------- Set the new values of that pixel in the original image
		}
	}

	free_allocate_memory_2D_array<RGBTRIPLE, int>(image_copy, height);
}
// To get the wanted RGB values we can check for each target an artificial box around that target, we will traverse around the target by -1 and +1 values
// We set a nested for loop to loop around the target  going -1 and +1 directions
// We can use an if statement to check if the pixel exists, to check if its in the bounds of the array we can just see if the indexes go over or match the height or width or fall below 0, if any pixel matches these statements, we skip this pixel
//
// T = Target, G = Get these pixels, X = Pixles dont exist, C - Current check
//
//     0  1  2  3  4  5          |     0  1  2  3  4  5          |     0  1  2  3  4  5           |     0  1  2  3  4  5           |     0  1  2  3  4  5           |     0  1  2  3  4  5          |     0  1  2  3  4  5          |     0  1  2  3  4  5          |     0  1  2  3  4  5          |     0  1  2  3  4  5
//   X X  X                      |        X  X  X                |                 X  X X         |                                |                                |                               |                               |                               |                               |
// 0 X[T][G][ ][ ][ ][ ]         | 0  [ ][G][T][G][ ][ ]         | 0  [ ][ ][ ][ ][G][T]X         | 0  [ ][ ][ ][ ][ ][ ]          | 0  [ ][ ][ ][ ][ ][ ]          | 0  [ ][ ][ ][ ][ ][ ]         | 0  [ ][ ][ ][ ][ ][ ]         | 0 X[G][G][ ][ ][ ][ ]         | 0  [ ][ ][ ][ ][ ][ ]         | 0  [G][G][G][ ][ ][ ]
// 1 X[G][G][ ][ ][ ][ ]         | 1  [ ][G][G][G][ ][ ]         | 1  [ ][ ][ ][ ][G][G]X         | 1  [ ][ ][ ][ ][G][G]X         | 1  [ ][ ][ ][ ][ ][ ]          | 1  [ ][ ][ ][ ][ ][ ]         | 1  [ ][ ][ ][ ][ ][ ]         | 1 X[T][G][ ][ ][ ][ ]         | 1  [ ][G][G][G][ ][ ]         | 1  [G][T][G][ ][ ][ ]
// 2  [ ][ ][ ][ ][ ][ ]         | 2  [ ][ ][ ][ ][ ][ ]         | 2  [ ][ ][ ][ ][ ][ ]          | 2  [ ][ ][ ][ ][G][T]X         | 2  [ ][ ][ ][ ][ ][ ]          | 2  [ ][ ][ ][ ][ ][ ]         | 2  [ ][ ][ ][ ][ ][ ]         | 2 X[G][G][ ][ ][ ][ ]         | 2  [ ][G][T][G][ ][ ]         | 2  [G][G][G][ ][ ][ ]
// 3  [ ][ ][ ][ ][ ][ ]         | 3  [ ][ ][ ][ ][ ][ ]         | 3  [ ][ ][ ][ ][ ][ ]          | 3  [ ][ ][ ][ ][G][G]X         | 3  [ ][ ][ ][ ][G][G]X         | 3  [ ][ ][G][G][G][ ]         | 3 X[G][G][ ][ ][ ][ ]         | 3  [ ][ ][ ][ ][ ][ ]         | 3  [ ][G][G][G][ ][ ]         | 3  [ ][ ][ ][ ][ ][ ]
// 4  [ ][ ][ ][ ][ ][ ]         | 4  [ ][ ][ ][ ][ ][ ]         | 4  [ ][ ][ ][ ][ ][ ]          | 4  [ ][ ][ ][ ][ ][ ]          | 4  [ ][ ][ ][ ][G][T]X         | 4  [ ][ ][G][T][G][ ]         | 4 X[T][G][ ][ ][ ][ ]         | 4  [ ][ ][ ][ ][ ][ ]         | 4  [ ][ ][ ][ ][ ][ ]         | 4  [ ][ ][ ][ ][ ][ ]
//                               |                               |                                |                                |                 X  X X         |           X  X  X             |   X X  X                      |                               |                               |
// If target is at 00:           | If target is at 02:           | If target is at 05:
// i = 0; j = 0;                 | i = 0; j = 2;                 | i = 0; j = 5;
// We need the pixles:           | We need the pixles:           | We need the pixles:
// 00, 01                        | 01, 02, 03                    | 04, 05
// 10, 11                        | 11, 12, 13                    | 14, 15
//                               |                               |
// Cycle 1:                      | Cycle 1:                      | Cycle 1:
// i = 0;                        | i = 0;                        | i = 0;
// j = 0;                        | j = 2;                        | j = 5;
// c = -1; c < 2;                | c = -1; c < 2;                | c = -1; c < 2;
// d = -1; d < 2;                | d = -1; d < 2;                | d = -1; d < 2;
//                               |                               |
// Check if exists               | Check if exists               | Check if exists
// pixle [c + i][d + j]          | pixle [c + i][d + j]          | pixle [c + i][d + j]
// All have to be F              | All have to be F              | All have to be F
//                               |                               |
// [c + i] = -1 + 0 = -1;        | [c + i] = -1 + 0 = -1;        | [c + i] = -1 + 0 = -1;
// [d + j] = -1 + 0 = -1;        | [d + j] = -1 + 2 = 1;         | [d + j] = -1 + 5 = 4;
//                               |                               |
//                 -1 0  1       |                   1  2  3     |                   4  5 6
// c(-1 < 0)  T  -1 C X  X       | c(-1 < 0)  T  -1  C  X  X     | c(-1 < 0)  T  -1  C  X X
// c(-1 >= 5) F   0 X[T][G]      | c(-1 >= 5) F   0 [G][T][G]    | c(-1 >= 5) F   0 [G][T]X
// d(-1 < 0)  T   1 X[G][G]      | d(1 < 0)   F   1 [G][G][G]    | d(4 < 0)   F   1 [G][G]X
// d(-1 >= 6) F                  | d(1 >= 6)  F                  | d(4 >= 6)  F
//                               |                               |
// SKIP;                         | SKIP;                         | SKIP;
//                               |                               |
// d++;                          | d++;                          | d++;
// [c + i] = -1 + 0 = -1;        | [c + i] = -1 + 0 = -1;        | [c + i] = -1 + 0 = -1;
// [d + j] = 0 + 0 = 0;          | [d + j] = 0 + 2 = 2;          | [d + j] = 0 + 5 = 5;
//                               |                               |
//                 -1 0  1       |                   1  2  3     |                   4  5 6
// c(-1 < 0)  T  -1 X C  X       | c(-1 < 0)  T  -1  X  C  X     | c(-1 < 0)  T  -1  X  C X
// c(-1 >= 5) F   0 X[T][G]      | c(-1 >= 5) F   0 [G][T][G]    | c(-1 >= 5) F   0 [G][T]X
// d(0 < 0)   F   1 X[G][G]      | d(2 < 0)   F   1 [G][G][G]    | d(5 < 0)   F   1 [G][G]X
// d(0 >= 6)  F                  | d(2 >= 6)  F                  | d(5 >= 6)  F
//                               |                               |
// SKIP;                         | SKIP;                         | SKIP;
//                               |                               |
// d++;                          | d++;                          | d++;
// [c + i] = -1 + 0 = -1;        | [c + i] = -1 + 0 = -1;        | [c + i] = -1 + 0 = -1;
// [d + j] = 1 + 0 = 1;          | [d + j] = 1 + 2 = 3;          | [d + j] = 1 + 5 = 6;
//                               |                               |
//                 -1 0  1       |                   1  2  3     |                   4  5 6
// c(-1 < 0)  T  -1 X X  C       | c(-1 < 0)  T  -1  X  X  C     | c(-1 < 0)  T  -1  X  X C
// c(-1 >= 5) F   0 X[T][G]      | c(-1 >= 5) F   0 [G][T][G]    | c(-1 >= 5) F   0 [G][T]X
// d(1 < 0)   F   1 X[G][G]      | d(3 < 0)   F   1 [G][G][G]    | d(6 < 0)   F   1 [G][G]X
// d(1 >= 6)  F                  | d(3 >= 6)  F                  | d(6 >= 6)  T
//                               |                               |
// SKIP;                         | SKIP;                         | SKIP;
//                               |                               |
// Cycle 2: c++;                 | Cycle 2: c++;                 | Cycle 2: c++;
// [c + i] = 0 + 0 = 0;          | [c + i] = 0 + 0 = 0;          | [c + i] = 0 + 0 = 0;
// [d + j] = -1 + 0 = -1;        | [d + j] = -1 + 2 = 1;         | [d + j] = -1 + 5 = 4;
//                               |                               |
//                 -1 0  1       |                   1  2  3     |                   4  5 6
// c(0 < 0)   F  -1 X X  X       | c(0 < 0)   F  -1  X  X  X     | c(0 < 0)   F  -1  X  X X
// c(0 >= 5)  F   0 C[T][G]      | c(0 >= 5)  F   0 [C][T][G]    | c(0 >= 5)  F   0 [C][T]X
// d(-1 < 0)  T   1 X[G][G]      | d(1 < 0)   F   1 [G][G][G]    | d(4 < 0)   F   1 [G][G]X
// d(-1 >= 6) F                  | d(1 >= 6)  F                  | d(4 >= 6)  F
//                               |                               |
// SKIP;                         | GET RGB VALUES FOR 01;        | GET RGB VALUES FOR 04;
//                               |                               |
// d++;                          | d++;                          | d++;
// [c + i] = 0 + 0 = 0;          | [c + i] = 0 + 0 = 0;          | [c + i] = 0 + 0 = 0;
// [d + j] = 0 + 0 = 0;          | [d + j] = 0 + 2 = 2;          | [d + j] = 0 + 5 = 5;
//                               |                               |
//                  -1 0  1      |                    1  2  3    |                    4  5 6
// c(0 < 0)   F   -1 X X  X      | c(0 < 0)   F   -1  X  X  X    | c(0 < 0)   F   -1  X  X X
// c(0 >= 5)  F    0 X[C][G]     | c(0 >= 5)  F    0 [G][C][G]   | c(0 >= 5)  F    0 [G][C]X
// d(0 < 0)   F    1 X[G][G]     | d(2 < 0)   F    1 [G][G][G]   | d(5 < 0)   F    1 [G][G]X
// d(0 >= 6)  F                  | d(2 >= 6)  F                  | d(5 >= 6)  F
//                               |                               |
// GET RGB VALUES FOR 00;        | GET RGB VALUES FOR 02;        | GET RGB VALUES FOR 05;
//                               |                               |
// d++;                          | d++;                          | d++;
// [c + i] = 0 + 0 = 0;          | [c + i] = 0 + 0 = 0;          | [c + i] = 0 + 0 = 0;
// [d + j] = 1 + 0 = 1;          | [d + j] = 1 + 2 = 3;          | [d + j] = 1 + 5 = 6;
//                               |                               |
//                  -1 0  1      |                    1  2  3    |                    4  5 6
// c(0 < 0)   F   -1 X X  X      | c(0 < 0)   F   -1  X  X  X    | c(0 < 0)   F   -1  X  X X
// c(0 >= 5)  F    0 X[T][C]     | c(0 >= 5)  F    0 [G][T][C]   | c(0 >= 5)  F    0 [G][T]C
// d(1 < 0)   F    1 X[G][G]     | d(3 < 0)   F    1 [G][G][G]   | d(6 < 0)   F    1 [G][G]X
// d(1 >= 6)  F                  | d(3 >= 6)  F                  | d(6 >= 6)  T
//                               |                               |
// GET RGB VALUES FOR 01;        | GET RGB VALUES FOR 03;        | SKIP;
//                               |                               |
// Cycle 3: c++;                 | Cycle 3: c++;                 | Cycle 3: c++;
// [c + i] = 1 + 0 = 1;          | [c + i] = 1 + 0 = 1;          | [c + i] = 1 + 0 = 1;
// [d + j] = -1 + 0 = -1;        | [d + j] = -1 + 2 = 1;         | [d + j] = -1 + 5 = 4;
//                               |                               |
//                 -1 0  1       |                   1  2  3     |                   4  5 6
// c(1 < 0)   F  -1 X X  X       | c(1 < 0)   F  -1  X  X  X     | c(1 < 0)   F  -1  X  X X
// c(1 >= 5)  F   0 X[T][G]      | c(1 >= 5)  F   0 [G][T][G]    | c(1 >= 5)  F   0 [G][T]X
// d(-1 < 0)  T   1 C[G][G]      | d(1 < 0)   F   1 [C][G][G]    | d(4 < 0)   F   1 [C][G]X
// d(-1 >= 6) F                  | d(1 >= 6)  F                  | d(4 >= 6)  F
//                               |                               |
// SKIP;                         | GET RGB VALUES FOR 11;        | GET RGB VALUES FOR 14;
//                               |                               |
// d++;                          | d++;                          | d++;
// [c + i] = 1 + 0 = 1;          | [c + i] = 1 + 0 = 1;          | [c + i] = 1 + 0 = 1;
// [d + j] = 0 + 0 = 0;          | [d + j] = 0 + 2 = 2;          | [d + j] = 0 + 5 = 6;
//                               |                               |
//                  -1 0  1      |                    1  2  3    |                    4  5 6
// c(1 < 0)   F   -1 X X  X      | c(1 < 0)   F   -1  X  X  X    | c(1 < 0)   F   -1  X  X X
// c(1 >= 5)  F    0 X[T][G]     | c(1 >= 5)  F    0 [G][T][G]   | c(1 >= 5)  F    0 [G][T]X
// d(0 < 0)   F    1 X[C][G]     | d(2 < 0)   F    1 [G][C][G]   | d(5 < 0)   F    1 [G][C]X
// d(0 >= 6)  F                  | d(2 >= 6)  F                  | d(5 >= 6)  F
//                               |                               |
// GET RGB VALUES FOR 10;        | GET RGB VALUES FOR 12;        | GET RGB VALUES FOR 15;
//                               |                               |
// d++;                          | d++;                          | d++;
// [c + i] = 1 + 0 = 1;          | [c + i] = 1 + 0 = 1;          | [c + i] = 1 + 0 = 1;
// [d + j] = 1 + 0 = 1;          | [d + j] = 1 + 2 = 3;          | [d + j] = 1 + 5 = 6;
//                               |                               |
//                  -1 0  1      |                   1  2  3     |                    4  5 6
// c(1 < 0)   F   -1 X X  X      | c(1 < 0)   F  -1  X  X  X     | c(1 < 0)   F   -1  X  X X
// c(1 >= 5)  F    0 X[T][G]     | c(1 >= 5)  F   0 [G][T][G]    | c(1 >= 5)  F    0 [G][T]X
// d(1 < 0)   F    1 X[G][C]     | d(3 < 0)   F   1 [G][G][C]    | d(6 < 0)   F    1 [G][G]C
// d(1 >= 6)  F                  | d(3 >= 6)  F                  | d(6 >= 6)  T
//                               |                               |
// GET RGB VALUES FOR 11;        | GET RGB VALUES FOR 13;        | SKIP;
// GO TO NEXT PIXLES;            | GO TO NEXT PIXLES;            | GO TO NEXT PIXLES;