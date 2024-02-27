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
#include <vector>
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
    int BytesPerPixel = 3;
    int height = 422, width = 750;


    // Allocate image data array
    unsigned char image_in[422][750][BytesPerPixel];  // 0 is R | 1 is G | 2 is B;
    unsigned char image_out[422][750][BytesPerPixel]; // 0 is R | 1 is G | 2 is B;
    unsigned char image_Y[422][750];
    float image_U[422][750];
    float image_V[422][750];
    int Y_count[256] = {};
    float Y_prob[256] = {};
    float Y_prob_CDF[256] = {};
    float Y_prob_total = 0;
    int total_pixel = 0;

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb")))
    {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(image_in, sizeof(unsigned char), 750 * 422 * BytesPerPixel, file);

    for (int i = 0; i < 422; i++)
    {
        for (int j = 0; j < 750; j++)
        {
            unsigned int r_val = image_in[i][j][0], g_val = image_in[i][j][1], b_val = image_in[i][j][2];
            int Y_val = floor((0.257 * r_val) + (0.504 * g_val) + (0.098 * b_val) + 16);
            float U_val = -(0.148 * r_val) - (0.291 * g_val) + (0.439 * b_val) + 128;
            float V_val = (0.439 * r_val) - (0.368 * g_val) - (0.071 * b_val) + 128;
            image_Y[i][j] = (unsigned char)Y_val;
            image_U[i][j] = U_val;
            image_V[i][j] = V_val;
        }
    }

    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
    clahe->setClipLimit(atoi(argv[3]));                              // 3
    clahe->setTilesGridSize(cv::Size(atoi(argv[4]), atoi(argv[4]))); // 20
    cv::Mat image_Y_Mat(cv::Size(750, 422), CV_8UC1, image_Y);
    clahe->apply(image_Y_Mat, image_Y_Mat);
    unsigned char **image_Y_out = new unsigned char *[image_Y_Mat.rows];
    for (int i = 0; i < image_Y_Mat.rows; i++)
    {
        image_Y_out[i] = new unsigned char[image_Y_Mat.cols];
        image_Y_out[i] = image_Y_Mat.ptr<unsigned char>(i);
    }
    //cout << "Y processing finished" << endl;
    for (int i = 0; i < 422; i++)
    {
        for (int j = 0; j < 750; j++)
        {
            int Y_adjusted = image_Y_out[i][j];
            int R = (int)floor(1.164 * (Y_adjusted - 16) + 1.596 * (image_V[i][j] - 128));
            int G = (int)floor(1.164 * (Y_adjusted - 16) - 0.813 * (image_V[i][j] - 128) - 0.391 * (image_U[i][j] - 128));
            int B = (int)floor(1.164 * (Y_adjusted - 16) - 0.000 * (image_V[i][j] - 128) + 2.018 * (image_U[i][j] - 128));

            if (R > 255)
            {
                R = 255;
            }
            else if (R < 0)
            {
                R = 0;
            }
            if (G > 255)
            {
                G = 255;
            }
            else if (G < 0)
            {
                G = 0;
            }
            if (B > 255)
            {
                B = 255;
            }
            else if (B < 0)
            {
                B = 0;
            }

            image_out[i][j][0] = (unsigned char)R;
            image_out[i][j][1] = (unsigned char)G;
            image_out[i][j][2] = (unsigned char)B;
        }
    }
    std::fclose(file);

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(argv[2], "wb")))
    {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(image_out, sizeof(unsigned char), 750 * 422 * BytesPerPixel, file);
    // fwrite(image_padding, sizeof(unsigned char), 750_padding*422_padding, file);
    std::fclose(file);
    cv::Mat image(cv::Size(750, 422), CV_8UC3, image_out);
    cv::cvtColor(image, image, COLOR_BGR2RGB);
    cv::imshow("test", image);
    cv::waitKey();

    return 0;
}
