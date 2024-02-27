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
#include <opencv2/photo.hpp>

using namespace cv;

using namespace std;

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int height = 400, width = 240;
    float  h_value = 10;
    int window_S = 7, window_N = 21;

    // Check for proper syntax
    if (argc < 6)
    {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw " << endl;
        return 0;
    }
    window_S = atoi(argv[3]);
    window_N = atoi(argv[4]);
    h_value = atof(argv[5]);

    // Allocate image data array
    unsigned char image_in[width][height], image_final[width][height];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb")))
    {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(image_in, sizeof(unsigned char), height * width, file);

    cv::Mat image_in_mat(cv::Size(400, 240), CV_8UC1, image_in);
    cv::Mat image_out_mat;
    cv::fastNlMeansDenoising(image_in_mat, image_out_mat, h_value, window_N, window_S);
    unsigned char **image_Y_out = new unsigned char *[image_out_mat.rows];
    for (int i = 0; i < image_out_mat.rows; i++)
    {
        image_Y_out[i] = new unsigned char[image_out_mat.cols];
        image_Y_out[i] = image_out_mat.ptr<unsigned char>(i);
    }
    for (int i  = 0; i < width; i++){
        for (int j = 0; j < height; j ++)
            image_final[i][j] = image_Y_out[i][j];
    }

    fclose(file);

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(argv[2], "wb")))
    {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(image_final, sizeof(unsigned char), width * height, file);
    cv::Mat image(cv::Size(400, 240), CV_8UC1, image_final);
    // fwrite(image_padding, sizeof(unsigned char), height_padding*width_padding, file);
    fclose(file);
    cv::imshow("test", image);
    cv::waitKey();

    return 0;
}
