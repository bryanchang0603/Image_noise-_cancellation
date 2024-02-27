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
    int height_padding = 402, width_padding = 242;
    float sin_sum_H = 0;
    float cos_sum_H = 0;

    // Check for proper syntax
    if (argc < 3)
    {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw " << endl;
        return 0;
    }

    // Allocate image data array
    unsigned char image_in[width][height][BytesPerPixel];
    unsigned char *image_HSV;
    unsigned char *image_out;
    unsigned char image_H[width][height];
    unsigned char image_padding_H[width_padding][height_padding];
    unsigned char temp;

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb")))
    {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(image_in, sizeof(unsigned char), height * width * BytesPerPixel, file);
    // covert RGB to BGR to suit opencv's format
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            temp = image_in[i][j][0];
            image_in[i][j][0] = image_in[i][j][2];
            image_in[i][j][2] = temp;
        }
    }
    cv::Mat image(cv::Size(400, 240), CV_8UC3, image_in);

    cv::cvtColor(image, image, COLOR_RGB2HSV);
    image_HSV = image.data;

    // zero padding
    for (int i = 0; i < width; i++)
    {
        // image_padding_H[i][0] = 0;
        // image_padding_H[i][width_padding - 1] = 0;
        image_padding_H[i][0] = image_HSV[(i * 400) * 3];
        image_padding_H[i][width_padding - 1] = image_HSV[(i * 400 + 239) * 3];
    }

    for (int j = 0; j < height; j++)
    {
        // image_padding_H[0][j] = 0;
        // image_padding_H[height_padding - 1][j] = 0;
        image_padding_H[0][j] = image_HSV[(j)*3];
        image_padding_H[height_padding - 1][j] = image_HSV[(239 * 400 + j) * 3];
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image_H[i][j] = image_HSV[(i * 400 + j) * 3];
            image_padding_H[i + 1][j + 1] = image_H[i][j];
        }
    }

    fclose(file);

    for (int i = 0; i < width; i++) // i is column j is row
    {
        for (int j = 0; j < height; j++)
        {
            sin_sum_H = 0;
            cos_sum_H = 0;
            for (int i_pad = 0; i_pad < (3); i_pad++)
            {
                for (int j_pad = 0; j_pad < (3); j_pad++)
                {
                    sin_sum_H += sin(2 * (float)image_padding_H[i + i_pad][j + j_pad] * M_PI / 180);
                    cos_sum_H += cos(2 * (float)image_padding_H[i + i_pad][j + j_pad] * M_PI / 180);
                    // cout << i + i_pad << "|" << j + j_pad << endl;
                }
            }
            int degree_adjusted = ((int)(atan2(sin_sum_H, cos_sum_H) * 180 / M_PI) + 360) % 360 / 2;
            image_HSV[(i * 400 + j) * 3] = (unsigned char)(degree_adjusted);
        }
    }

    cv::Mat mat_HSV(cv::Size(400, 240), CV_8UC3, image_HSV);
    cv::cvtColor(mat_HSV, mat_HSV, COLOR_HSV2RGB);
    image_out = mat_HSV.data;

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(argv[2], "wb")))
    {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            temp = image_in[i][j][2];
            image_in[i][j][2] = image_in[i][j][0];
            image_in[i][j][0] = temp;
        }
    }
    fwrite(image_out, sizeof(unsigned char), width * height * BytesPerPixel, file);
    // fwrite(image_padding, sizeof(unsigned char), height_padding*width_padding, file);
    fclose(file);

    cv::cvtColor(image, image, COLOR_BGR2RGB);
    cv::imshow("test", mat_HSV);
    cv::waitKey();

    return 0;
}
