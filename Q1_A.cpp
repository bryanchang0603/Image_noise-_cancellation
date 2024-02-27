// # EE569 Homework Assignment #1
// # Date: Jan 29, 2023
// # Name: Baosheng Chang
// # ID: 9660914048
// # email: baosheng@usc.edu
// #
// # Operating Environment: MacOS Monterey, M1 chip
// ========================================================================

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
using namespace cv;

using namespace std;
const int RGB_channel = 3;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int height = 420, width = 288;
	int height_padding = 422, width_padding = 290;

	// Check for proper syntax
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw " << endl;
		return 0;
	}

	// Allocate image data array
	unsigned char image_in[width][height];
	unsigned char image_out[width][height][RGB_channel], image_padding[width_padding][height_padding];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(argv[1], "rb")))
	{
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	fread(image_in, sizeof(unsigned char), height * width * BytesPerPixel, file);

	// zero padding
	for (int i = 0; i < 288; i++)
	{
		image_padding[i][0] = 0;
		image_padding[i][width_padding - 1] = 0;
	}

	for (int j = 0; j < 420; j++)
	{
		image_padding[0][j] = 0;
		image_padding[height_padding - 1][j] = 0;
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			image_padding[i + 1][j + 1] = image_in[i][j];
		}
	}

	fclose(file);

	for (int i = 0; i < width; i++) // i is column j is row
	{
		for (int j = 0; j < height; j++)
		{
			int mode_i = i % 2;
			int mode_j = j % 2;
			if (mode_i == mode_j)
			{ // green
				if (mode_i == 1)
				{
					image_out[i][j][0] = (unsigned char)round(((float)image_padding[i][j + 1] +
															   (float)image_padding[i + 2][j + 1]) /
															  2); // R
					image_out[i][j][1] = image_in[i][j];		  // G
					image_out[i][j][2] = (unsigned char)round(((float)image_padding[i + 1][j] +
															   (float)image_padding[i + 1][j + 2]) /
															  2); // B
				}
				else
				{
					image_out[i][j][0] = (unsigned char)round(((float)image_padding[i+1][j] +
															   (float)image_padding[i + 1][j + 2]) /
															  2); // R
					image_out[i][j][1] = image_in[i][j];		  // G
					image_out[i][j][2] = (unsigned char)round(((float)image_padding[i][j + 1] +
															   (float)image_padding[i + 2][j + 1]) /
															  2); // B
				}
			}
			else if (mode_i == 0 && mode_j == 1)
			{										 // red
				image_out[i][j][0] = image_in[i][j]; // r
				image_out[i][j][1] = (unsigned char)round(((float)image_padding[i + 1][j] +
														   (float)image_padding[i + 1][j + 2] +
														   (float)image_padding[i][j + 1] +
														   (float)image_padding[i + 2][j + 1]) /
														  4); // G
				image_out[i][j][2] = (unsigned char)round(((float)image_padding[i][j] +
														   (float)image_padding[i][j + 2] +
														   (float)image_padding[i + 2][j] +
														   (float)image_padding[i + 2][j + 2]) /
														  4); // B
			}
			else
			{ // blue
				image_out[i][j][0] = (unsigned char)round(((float)image_padding[i][j] +
														   (float)image_padding[i][j + 2] +
														   (float)image_padding[i + 2][j] +
														   (float)image_padding[i + 2][j + 2]) /
														  4); // r
				//cout << (image_padding[i + 1][j + 1]) << "|" << image_in[i][j] << endl;
				image_out[i][j][1] = (unsigned char)round(((float)image_padding[i + 1][j] +
														   (float)image_padding[i + 1][j + 2] +
														   (float)image_padding[i][j + 1] +
														   (float)image_padding[i + 2][j + 1]) /
														  4); // G
				image_out[i][j][2] = image_in[i][j];		  // b
			}
			// cout <<i << "," << j << ":" << image_out[i][j][0] << "|" << image_out[i][j][1] << "|" << image_out[i][j][2] << endl;
		}
	}

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file = fopen(argv[2], "wb")))
	{
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(image_out, sizeof(unsigned char), height * width * RGB_channel, file);
	// fwrite(image_padding, sizeof(unsigned char), height_padding*width_padding, file);
	cv::Mat image(cv::Size(height, width), CV_8UC3, image_out);
	cvtColor(image, image, COLOR_BGR2RGB);
	cv::imshow("test", image);
	fclose(file);
	cv::waitKey();

	return 0;
}
