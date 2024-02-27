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
    unsigned char origional_image[height][width];
    unsigned char denoised_image[height][width];
    double SSE;
    double MSE;

    // Check for proper syntax
    if (argc < 2)
    {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw " << endl;
        return 0;
    }

    // Allocate image data array

    // Read image (filename specified by first argument) into image data matrix
    file = fopen("images/Pepper_gray.raw", "rb");
    fread(origional_image, sizeof(unsigned char), height * width, file);
    fclose(file);

    if (!(file = fopen(argv[1], "rb")))
    {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(denoised_image, sizeof(unsigned char), height * width, file);
    for (int i = 0 ; i < height; i++){
        for (int j = 0; j < width; j ++){
            SSE += pow(abs((int)origional_image[i][j] - (int)denoised_image[i][j]), 2);
        }
    }

    MSE = SSE/(double)(width * height);
    double psnr = 10 * log10(255*255/MSE);

    // cv::Mat mat_org(cv::Size(400, 240), CV_8UC1, origional_image);
    // cv::Mat mat_dsn(cv::Size(400, 240), CV_8UC1, denoised_image);
    // cv::Mat mat_dif;
    // absdiff(mat_org, mat_dsn, mat_dif);
    // mat_dif.convertTo(mat_dif, CV_32FC1);
    // mat_dif = mat_dif.mul(mat_dif);
    // Scalar dif_sum = sum(mat_dif);
    // double mse = dif_sum.val[0]/double(mat_org.total());
    // double psnr = 10 * log10(255*255/mse);
    cout << "SSE:" << SSE <<endl;
    cout << "MSE:" << MSE <<endl;
    cout << "PSNR:" << psnr <<endl;
    

    return 0;
}
