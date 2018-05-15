// Smyth, Ravela        CS546 Section 14860  5/1/18
// Third Laboratory Assignment - Map NYC Taxi Destinations

#include <iostream>
#include <fstream>
#include <cmath>
#include "windows.h"
using namespace std;

// The following defines the size of the square image in pixels.
#define IMAGE_SIZE 1024

#define NORTH 40.830509
#define SOUTH 40.700455
#define WEST -74.045033
#define EAST -73.914979


int main(int argc, char* argv[])
{

	BITMAPFILEHEADER bmFileHeader;

	BITMAPINFOHEADER bmInfoHeader;

	char colorTable[1024];
	// The following defines the array which holds the image.  
	char bits[IMAGE_SIZE][IMAGE_SIZE] = { 0 };

	int i, j;

	// Input file
	ifstream infile("L2Data10K.dat", ios::in | ios::binary);

	float longitude;
	float latitude;

	infile.seekg(0, ios::beg);
	while (!infile.eof())
	{

		infile.read((char*)&latitude, sizeof(float));
		infile.read((char*)&longitude, sizeof(float));


		if ((latitude >= SOUTH && latitude <= NORTH) && (longitude >= WEST && longitude <= EAST))
		{

			//min and max of old coordinates system
			// Math.abs((value - min) / (max - min));

			//min and max of new coordinate system
			//destX = xPercent*(Math.abs(max-min)) + min;

			float xPercentage = (fabs(longitude) - fabs(WEST)) / (fabs(EAST) - fabs(WEST));
			float newLongitude = ceil(fabs(xPercentage) * 1024);

			float yPercentage = (latitude - SOUTH) / (NORTH - SOUTH);
			float newLatitude = ceil(yPercentage * 1024);

			bits[(int)newLatitude][(int)newLongitude] = 255;
		}
	}
		// Define and open the output file. 
		ofstream bmpOut("foo.bmp", ios::out + ios::binary);
		if (!bmpOut) {
			cout << "...could not open file, ending.";
			return -1;
		}
		
		// Initialize the bit map file header with static values.
		bmFileHeader.bfType = 0x4d42;
		bmFileHeader.bfReserved1 = 0;
		bmFileHeader.bfReserved2 = 0;
		bmFileHeader.bfOffBits = sizeof(bmFileHeader) + sizeof(bmInfoHeader) + sizeof(colorTable);
		bmFileHeader.bfSize = bmFileHeader.bfOffBits + sizeof(bits);
	
		// Initialize the bit map information header with static values.
		bmInfoHeader.biSize = 40;
		bmInfoHeader.biWidth = IMAGE_SIZE;
		bmInfoHeader.biHeight = IMAGE_SIZE;
		bmInfoHeader.biPlanes = 1;
		bmInfoHeader.biBitCount = 8;
		bmInfoHeader.biCompression = 0;
		bmInfoHeader.biSizeImage = IMAGE_SIZE * IMAGE_SIZE;
		bmInfoHeader.biXPelsPerMeter = 2835;  // magic number, see Wikipedia entry
		bmInfoHeader.biYPelsPerMeter = 2835;
		bmInfoHeader.biClrUsed = 256;
		bmInfoHeader.biClrImportant = 0;
	
		for (i = 0; i < 256; i++) {
			j = i * 4;
			colorTable[j] = colorTable[j + 1] = colorTable[j + 2] = colorTable[j + 3] = i;
			// for your edification, try setting one of the first three values to 255 instead of i
			// and see what it does to the generated bit map.
		}
	
		// Write out the bit map.  
		char* workPtr;
		workPtr = (char*)&bmFileHeader;
		bmpOut.write(workPtr, 14);
		workPtr = (char*)&bmInfoHeader;
		bmpOut.write(workPtr, 40);
		workPtr = &colorTable[0];
		bmpOut.write(workPtr, sizeof(colorTable));
		workPtr = &bits[0][0];
		bmpOut.write(workPtr, IMAGE_SIZE*IMAGE_SIZE);
		bmpOut.close();
	
	
		// Now let's look at our creation.
		system("mspaint foo.bmp");
		infile.close();
		// Done.
		return 0;
}
