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
#include <fstream>
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
	fstream file_out;
	int BytesPerPixel;
	int height = 340, width = 596;


	// Allocate image data array
	unsigned char image_in[width][height];
	unsigned char image_out[width][height];
	int greyscale_count[256] = {};
	float greyscale_prob[256] = {};
	float greyscale_prob_CDF[256] = {};
	float greyscale_prob_total = 0;
	int total_pixel = 0;

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(argv[1], "rb")))
	{
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	fread(image_in, sizeof(unsigned char), width * height, file);
	fclose(file);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			greyscale_count[(int)image_in[i][j]]++;
			//cout << (int)image_in[i][j]<<endl;
		}
	}

	for (int i = 0; i < 256; i++)
	{
		// cout <<greyscale_count[i] << endl;
		total_pixel += greyscale_count[i];
		greyscale_prob[i] = ((float)greyscale_count[i]) / (float)(height * width);
		greyscale_prob_total += greyscale_prob[i];
		greyscale_prob_CDF[i] = greyscale_prob_total;
		file_out << i << ","
				 << greyscale_prob_CDF[i]
				 << endl;
		//cout << greyscale_prob_CDF[i] << endl;
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int greyscale_intensity = image_in[i][j];
			image_out[i][j] = (unsigned char)(floor(200 * greyscale_prob_CDF[greyscale_intensity]));
		}
	}

	// Write image data (filename specified by second argument) from image data matrix

	// if (!(file = fopen(argv[2], "wb")))
	// {
	// 	cout << "Cannot open file: " << argv[2] << endl;
	// 	exit(1);
	// }
	// fwrite(image_out, sizeof(unsigned char), height * width, file);
	// fwrite(image_padding, sizeof(unsigned char), height_padding*width_padding, file);
	cv::Mat image(cv::Size(width, height), CV_8UC1, image_out);
    cv::imshow("test", image);
	// fclose(file);
	cv::waitKey();

	return 0;
}
