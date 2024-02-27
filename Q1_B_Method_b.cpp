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
#include <vector>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
using namespace cv;

using namespace std;
const int RGB_channel = 3;

struct pixel_info
{
    unsigned char grey_scale;
    int width_cord;
    int height_cord;
};

bool compare_greyscale(pixel_info &x, pixel_info &y)
{
    return x.grey_scale < y.grey_scale;
}

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    fstream file_out;
    int BytesPerPixel;
    int height = 340, width = 596;

    // Check for proper syntax
    if (argc < 3)
    {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw " << endl;
        return 0;
    }

    // Allocate image data array
    unsigned char image_in[width][height];
    unsigned char image_out[width][height];
    std::vector<pixel_info> pixel_vec;
    int pixel_counter = 0;
    int greyscale_counter = 0;
    int grayscale_count_after_c[256] = {};
    int grayscale_count_before_c[256] = {};
    int grayscale_count_after[256] = {};
    int grayscale_count_before[256] = {};

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb")))
    {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(image_in, sizeof(unsigned char), height * width * BytesPerPixel, file);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            pixel_vec.push_back({image_in[i][j], i, j});
        }
    }
    fclose(file);

    // sort the pixel_vec with acending order
    std::sort(pixel_vec.begin(), pixel_vec.end(), compare_greyscale);

    for (auto i : pixel_vec)
    {
        //cout << (int)i.grey_scale << endl;
        image_out[i.width_cord][i.height_cord] = greyscale_counter;
        grayscale_count_after[greyscale_counter]++;
        grayscale_count_before[(int)i.grey_scale]++;
        pixel_counter += 1;
        if ((pixel_counter % 793) == 0)
        {
            pixel_counter = 0;
            greyscale_counter += 1;
        }
    }
    grayscale_count_after_c[0] = grayscale_count_after[0];
    grayscale_count_before_c[0] = grayscale_count_before[0];
    for (int i = 1; i < 256; i++)
    {
        grayscale_count_after_c[i] = grayscale_count_after_c[i - 1] + grayscale_count_after[i];
        grayscale_count_before_c[i] = grayscale_count_before_c[i - 1] + grayscale_count_before[i];
    }

    // file_out.open(argv[3], ios_base::out);
    // file_out << "index"
    //          << ","
    //          << "grayscale_count_before"
    //          << ","
    //          << "grayscale_count_after"
    //          << ","
    //          << "grayscale_count_before_c"
    //          << ","
    //          << "grayscale_count_after_c"
    //          << endl;

    // for (int i = 0; i < 256; i++)
    // {
    //     file_out << i << ","
    //              << grayscale_count_before[i] << ","
    //              << grayscale_count_after[i] << ","
    //              << grayscale_count_before_c[i] << ","
    //              << grayscale_count_after_c[i] 
    //              << endl;
    // }
    // file_out.close();

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(argv[2], "wb")))
    {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(image_out, sizeof(unsigned char), height * width, file);
    // fwrite(image_padding, sizeof(unsigned char), height_padding*width_padding, file);
    fclose(file);

    cv::Mat image(cv::Size(width, height), CV_8UC1, image_out);
    cv::imshow("test", image);
    cv::waitKey();

    return 0;
}
