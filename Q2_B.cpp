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
    float filter_sum = 0, filter_weight = 0, filter_weight_single = 0;
    float sigma_c = 3, sigma_s = 3;

    // Check for proper syntax
    sigma_c = atof(argv[3]);
    sigma_s = atof(argv[4]);


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

    fclose(file);

    for (int i = 0; i < width; i++) // i is column j is row
    {
        for (int j = 0; j < height; j++)
        {
            filter_sum = 0;
            filter_weight = 0;
            for (int i_pad = 0; i_pad < (padding_side * 2 + 1); i_pad++)
            {
                for (int j_pad = 0; j_pad < (padding_side * 2 + 1); j_pad++)
                {
                    float encl_distance = (pow(i_pad - 2, 2)+ pow(j_pad - 2 , 2))/(2 * pow(sigma_c, 2));
                    float grayscale_diff = pow((image_padding[i+2][j+2] - image_padding[i + i_pad][j + j_pad]),2) / 
                    (2 * pow(sigma_s, 2));
                    filter_weight_single = exp(-encl_distance - grayscale_diff);
                    filter_sum += image_padding[i + i_pad][j + j_pad] * filter_weight_single;
                    filter_weight +=filter_weight_single;
                    
                }
            }
            image_out[i][j] = (int)(filter_sum / filter_weight);
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
    fclose(file);

    cv::Mat image(cv::Size(400, 240), CV_8UC1, image_out);
    cv::imshow("test", image);
    cv::waitKey();

    return 0;
}
