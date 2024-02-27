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

struct YUV_pixel
{
    int Y;
    float U;
    float V;
    int x_cord;
    int y_cord;
};

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel = 3;
    int height = 422, width = 750;

    // Check for proper syntax
    if (argc < 3)
    {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw " << endl;
        return 0;
    }

    // Allocate image data array
    unsigned char image_in[width][height][BytesPerPixel]; // 0 is R | 1 is G | 2 is B;
    std::vector<YUV_pixel> image_YUV;
    unsigned char image_out[width][height][BytesPerPixel]; // 0 is R | 1 is G | 2 is B;
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
    fread(image_in, sizeof(unsigned char), width * height * BytesPerPixel, file);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int r_val = image_in[i][j][0], g_val = image_in[i][j][1], b_val = image_in[i][j][2];
            int Y_val = floor((0.257 * r_val) + (0.504 * g_val) + (0.098 * b_val) + 16);
            float U_val = -(0.148 * r_val) - (0.291 * g_val) + (0.439 * b_val) + 128;
            float V_val = (0.439 * r_val) - (0.368 * g_val) - (0.071 * b_val) + 128;
            image_YUV.push_back({Y_val, U_val, V_val, i, j});
            Y_count[Y_val] += 1;
        }
    }

    for (int i = 0; i < 256; i++)
    {
        // cout <<greyscale_count[i] << endl;
        total_pixel += Y_count[i];
        Y_prob[i] = ((float)Y_count[i]) / (float)(height * width);
        Y_prob_total += Y_prob[i];
        Y_prob_CDF[i] = Y_prob_total;
        // cout << Y_prob_CDF[i] << endl;
    }
    //cout << Y_prob_CDF[157-1] << endl;

    for (auto i : image_YUV)
    {
        float Y_adjusted = (255 * Y_prob_CDF[i.Y ]);
        int R = (int)floor(1.164 * (Y_adjusted - 16) + 1.596 * (i.V - 128));                       // R
        int G = (int)floor(1.164 * (Y_adjusted - 16) - 0.813 * (i.V - 128) - 0.391 * (i.U - 128)); // G
        int B = (int)floor(1.164 * (Y_adjusted - 16) + 2.018 * (i.U - 128));                       // B
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

        image_out[i.x_cord][i.y_cord][0] = R; // R
        image_out[i.x_cord][i.y_cord][1] = G; // G
        image_out[i.x_cord][i.y_cord][2] = B; // B
    }

    fclose(file);


    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(argv[2], "wb")))
    {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(image_out, sizeof(unsigned char), height * width * BytesPerPixel, file);
    // fwrite(image_padding, sizeof(unsigned char), height_padding*width_padding, file);
    fclose(file);

    
    cv::Mat image(cv::Size(width, height), CV_8UC3, image_out);
    cvtColor(image, image, COLOR_BGR2RGB);
    cv::imshow("test", image);
    cv::waitKey();

    return 0;
}
