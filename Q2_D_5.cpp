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
    int BytesPerPixel = 3;
    int height = 400, width = 240;
    int padding_side = 1;
    int padding_area = (2 * padding_side + 1) * (2 * padding_side + 1);
    int height_padding = 402, width_padding = 242;
    float filter_sum_R = 0, filter_sum_G = 0, filter_sum_B = 0;

    // Check for proper syntax
    if (argc < 3)
    {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw " << endl;
        return 0;
    }

    // Allocate image data array
    unsigned char image_in[width][height][BytesPerPixel];
    unsigned char image_out[width][height][BytesPerPixel];
    unsigned char   image_padding_R[width_padding][height_padding], 
                    image_padding_G[width_padding][height_padding],
                    image_padding_B[width_padding][height_padding];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb")))
    {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(image_in, sizeof(unsigned char), height * width * BytesPerPixel, file);

    // zero padding
    for (int i = 0; i < width; i++)
    {
        image_padding_R[i][0] = 0;
        image_padding_R[i][width_padding - 1] = 0;
        image_padding_G[i][0] = 0;
        image_padding_G[i][width_padding - 1] = 0;
        image_padding_B[i][0] = 0;
        image_padding_B[i][width_padding - 1] = 0;
    }

    for (int j = 0; j < height; j++)
    {
        image_padding_R[0][j] = 0;
        image_padding_R[height_padding - 1][j] = 0;
        image_padding_G[0][j] = 0;
        image_padding_G[height_padding - 1][j] = 0;
        image_padding_B[0][j] = 0;
        image_padding_B[height_padding - 1][j] = 0;
    }

	for (int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			image_padding_R[i+1][j+1] = image_in[i][j][0];
            image_padding_G[i+1][j+1] = image_in[i][j][1];
            image_padding_B[i+1][j+1] = image_in[i][j][2];
		}
	}

    fclose(file);

    for (int i = 0; i < width; i++) // i is column j is row
    {
        for (int j = 0; j < height; j++)
        {
            filter_sum_R = 0;
            filter_sum_G = 0;
            filter_sum_B = 0;
            for (int i_pad = 0; i_pad < (padding_side * 2 + 1); i_pad++)
            {
                for (int j_pad = 0; j_pad < (padding_side * 2 + 1); j_pad++)
                {
                    filter_sum_R += image_padding_R[i + i_pad][j + j_pad];
                    filter_sum_G += image_padding_G[i + i_pad][j + j_pad];
                    filter_sum_B += image_padding_B[i + i_pad][j + j_pad];
                    //cout << i + i_pad << "|" << j + j_pad << endl;
                }
            }
            filter_sum_R = filter_sum_R / padding_area;
            filter_sum_G = filter_sum_G / padding_area;
            filter_sum_B = filter_sum_B / padding_area;
            image_out[i][j][0] = (int)filter_sum_R;
            image_out[i][j][1] = (int)filter_sum_G;
            image_out[i][j][2] = (int)filter_sum_B;
        }
    }

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(argv[2], "wb")))
    {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(image_out, sizeof(unsigned char), width * height * BytesPerPixel, file);
    // fwrite(image_padding, sizeof(unsigned char), height_padding*width_padding, file);
    fclose(file);

    cv::Mat image(cv::Size(400, 240), CV_8UC3, image_out);
    cv::cvtColor(image, image, COLOR_BGR2RGB);
    cv::imshow("test", image);
    cv::waitKey();

    return 0;
}
