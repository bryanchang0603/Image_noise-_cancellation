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

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int height = 400, width = 240;
    int padding_side = 2;
    int padding_area = (2 * padding_side + 1) * (2 * padding_side + 1);
    int height_padding = height + (2 * padding_side), width_padding = width + (2 * padding_side);
    float filter_sum = 0;

    // Check for proper syntax
    if (argc < 3)
    {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw " << endl;
        return 0;
    }

    // Allocate image data array
    unsigned char image_in[width][height];
    unsigned char image_out[width][height], image_padding[width_padding][height_padding];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb")))
    {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(image_in, sizeof(unsigned char), height * width, file);

    // zero padding
    for (int i = 0; i < width; i++)
    {
        image_padding[i][0] = 0;
        image_padding[i][1] = 0;
        image_padding[i][width_padding - 1] = 0;
        image_padding[i][width_padding - 2] = 0;
    }

    for (int j = 0; j < height; j++)
    {
        image_padding[0][j] = 0;
        image_padding[2][j] = 0;
        image_padding[height_padding - 1][j] = 0;
        image_padding[height_padding - 2][j] = 0;
    }

	for (int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			image_padding[i+2][j+2] = image_in[i][j];
		}
	}

    std::fclose(file);

    for (int i = 0; i < width; i++) // i is column j is row
    {
        for (int j = 0; j < height; j++)
        {
            filter_sum = 0;
            //first row
            filter_sum += image_padding[i][j] * 1;
            filter_sum += image_padding[i][j+1] * 4;
            filter_sum += image_padding[i][j+2] * 7;
            filter_sum += image_padding[i][j+3] * 4;
            filter_sum += image_padding[i][j+4] * 1;
            //second row
            filter_sum += image_padding[i+1][j] * 4;
            filter_sum += image_padding[i+1][j+1] * 16;
            filter_sum += image_padding[i+1][j+2] * 26;
            filter_sum += image_padding[i+1][j+3] * 16;
            filter_sum += image_padding[i+1][j+4] * 4;
            //thrid row
            filter_sum += image_padding[i+2][j] * 7;
            filter_sum += image_padding[i+2][j+1] * 26;
            filter_sum += image_padding[i+2][j+2] * 41;
            filter_sum += image_padding[i+2][j+3] * 26;
            filter_sum += image_padding[i+2][j+4] * 7;
            //forth row
            filter_sum += image_padding[i+3][j] * 4;
            filter_sum += image_padding[i+3][j+1] * 16;
            filter_sum += image_padding[i+3][j+2] * 26;
            filter_sum += image_padding[i+3][j+3] * 16;
            filter_sum += image_padding[i+3][j+4] * 4;
            //fifth row
            filter_sum += image_padding[i+4][j] * 1;
            filter_sum += image_padding[i+4][j+1] * 4;
            filter_sum += image_padding[i+4][j+2] * 7;
            filter_sum += image_padding[i+4][j+3] * 4;
            filter_sum += image_padding[i+4][j+4] * 1;

            filter_sum = filter_sum / 273;
            image_out[i][j] = (int)filter_sum;
        }
    }

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(argv[2], "wb")))
    {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(image_out, sizeof(unsigned char), width * height, file);
    // fwrite(image_padding, sizeof(unsigned char), height_padding*width_padding, file);
    std::fclose(file);

    cv::Mat image(cv::Size(400, 240), CV_8UC1, image_out);
    cv::cvtColor(image, image, COLOR_BGR2RGB);
    cv::imshow("test", image);
    cv::waitKey();

    return 0;
}
