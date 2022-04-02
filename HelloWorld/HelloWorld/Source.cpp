#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opencv2/opencv.hpp> // Include 3rd pty openCV library
#include <iostream>
#include <sstream>

#pragma warning(disable : 4996)

void convert_image(int* x1); // Declare functions to convert image to txt files
void imgdata(int* x1); // Declare function to store image count and slide time in a txt file

using namespace std;
using namespace cv; // Use the CV namespace

void main(void)
{
	int x;

	printf("\nThis program will convert your images into readable text files containing 12-bit RGB data.\n");
	printf("\nPlease ensure your image files are:\n1) 32x32 pixels\n2) in the same folder as the source file\n3) In png format\n4) Named as 1.png, 2.png etc\n");
	printf("\nHow many images do you want to convert? (Max 15) ");
	fflush(stdin);
	scanf_s("%d", &x); // Store number of images in x
	convert_image(&x); // Call function to convert x amount of images
	imgdata(&x); // Call function to store image count and slide time in a txt file
}

void convert_image(int* x1)
{
	int i, j, y = *x1;
	char output_fn[100]; // Initialise the output file name array
	char r_hex[2];
	char g_hex[2];
	char b_hex[2];
	string images[50];
	Mat image; //taking an image matrix//

	for (y = 1; y < *x1 + 1; y++)
	{
		stringstream img;
		img << y << "\.png" << endl;

		string filename;
		img >> filename;
		images[y] = filename;
	}

	for (y = 1; y < *x1 + 1; y++)
	{
		sprintf_s(output_fn, "D:/%d", y);
		strcat_s(output_fn, ".txt");

		FILE* output_file;
		output_file = fopen(output_fn, "w");

		if (output_file == NULL)
		{
			printf("Cannot write to output file %s\n", output_fn);
			exit(1);
		}

		for (i = 0; i < 32; i++)
		{
			for (j = 0; j < 32; j++)
			{
				image = imread(images[y]);//loading an image//
				int b = image.at<Vec3b>(i, j)[0];//getting the pixel values//
				int g = image.at<Vec3b>(i, j)[1];//getting the pixel values//
				int r = image.at<Vec3b>(i, j)[2];//getting the pixel values//

				r = r / 16;
				g = g / 16;
				b = b / 16;



				sprintf_s(r_hex, "%X", r);
				sprintf_s(g_hex, "%X", g);
				sprintf_s(b_hex, "%X", b);

				fputs(r_hex, output_file);
				fputs(g_hex, output_file);
				fputs(b_hex, output_file);
			}
		}

		fclose(output_file);
	}
}

void imgdata(int* x1)
{
	int slide_time;
	char s_time[20], totalimg[20];
	FILE* imgdata;

	sprintf_s(totalimg, "%X", *x1);

	printf_s("\nHow many seconds do you want each image to show for (Max 15)? (If converting only one image, press 1): ");
	fflush(stdin);
	scanf_s("%d", &slide_time);
	sprintf_s(s_time, "%X", slide_time);

	imgdata = fopen("D:/imgdata.txt", "w");

	fputs(totalimg, imgdata);
	fputs(s_time, imgdata);

	fclose(imgdata);
}