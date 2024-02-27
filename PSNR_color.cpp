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
    unsigned char origional_image[height][width][3];
    unsigned char denoised_image[height][width][3];
    double SSE_R, SSE_G, SSE_B;
    double MSE_R, MSE_G, MSE_B;

    // Check for proper syntax
    if (argc < 2)
    {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw " << endl;
        return 0;
    }

    // Allocate image data array

    // Read image (filename specified by first argument) into image data matrix
    file = fopen("images/Pepper.raw", "rb");
    fread(origional_image, sizeof(unsigned char), height * width * 3, file);
    fclose(file);

    if (!(file = fopen(argv[1], "rb")))
    {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(denoised_image, sizeof(unsigned char), height * width * 3, file);
    SSE_R = 0;
    SSE_G = 0;
    SSE_B = 0;
    MSE_R = 0;
    MSE_G = 0;
    MSE_B = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            SSE_R += pow(abs((int)origional_image[i][j][0] - (int)denoised_image[i][j][0]), 2);
            SSE_G += pow(abs((int)origional_image[i][j][1] - (int)denoised_image[i][j][1]), 2);
            SSE_B += pow(abs((int)origional_image[i][j][2] - (int)denoised_image[i][j][2]), 2);
            // cout << (int)origional_image[i][j][1] << " " << (int)denoised_image[i][j][1] << " " << abs((int)origional_image[i][j][1] - (int)denoised_image[i][j][1])<<endl;
        }
    }

    MSE_R = SSE_R / (double)(width * height);
    MSE_G = SSE_G / (double)(width * height);
    MSE_B = SSE_B / (double)(width * height);
    double psnr_r = 10 * log10(255 * 255 / MSE_R);
    double psnr_g = 10 * log10(255 * 255 / MSE_G);
    double psnr_b = 10 * log10(255 * 255 / MSE_B);

    // cv::Mat mat_org(cv::Size(400, 240), CV_8UC3, origional_image);
    // cv::Mat mat_dsn(cv::Size(400, 240), CV_8UC3, denoised_image);
    // cv::Mat mat_dif;
    // absdiff(mat_org, mat_dsn, mat_dif);
    // mat_dif.convertTo(mat_dif, CV_32FC1);
    // mat_dif = mat_dif.mul(mat_dif);
    // Scalar dif_sum = sum(mat_dif);
    // MSE = (dif_sum.val[0] + dif_sum.val[1] + dif_sum.val[2]) / double(mat_org.total());
    // psnr = 10 * log10(255 * 255 / MSE);
    cout << "PSNR_r:" << psnr_r << endl;
    cout << "PSNR_g:" << psnr_g << endl;
    cout << "PSNR_b:" << psnr_b << endl;

    return 0;
}
