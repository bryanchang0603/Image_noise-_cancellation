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
    fstream file_out;
    int BytesPerPixel = 3;
    int height = 400, width = 240;
    int padding_side = 1;
    int padding_area = (2 * padding_side + 1) * (2 * padding_side + 1);
    int height_padding = 402, width_padding = 242;
    float filter_sum_H = 0;

    // Check for proper syntax
    if (argc < 3)
    {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw " << endl;
        return 0;
    }

    // Allocate image data array
    unsigned char image_in[width][height][BytesPerPixel];
    unsigned char image_R[width][height], image_G[width][height], image_B[width][height];
    int R_scale_noisy[256] = {}, G_scale_noisy[256] = {}, B_scale_noisy[256] = {};
    int R_scale_regular[256] = {}, G_scale_regular[256] = {}, B_scale_regular[256] = {};
    string single_line;

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
            R_scale_noisy[(int)image_in[i][j][0]]++;
            G_scale_noisy[(int)image_in[i][j][1]]++;
            B_scale_noisy[(int)image_in[i][j][2]]++;
        }
    }
    fclose(file);

    if (!(file = fopen(argv[3], "rb")))
    {
        cout << "Cannot open file: " << argv[3] << endl;
        exit(1);
    }

    fread(image_in, sizeof(unsigned char), height * width * BytesPerPixel, file);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            R_scale_regular[(int)image_in[i][j][0]]++;
            G_scale_regular[(int)image_in[i][j][1]]++;
            B_scale_regular[(int)image_in[i][j][2]]++;
        }
    }

    // Write image data (filename specified by second argument) from image data matrix

    file_out.open(argv[2], ios_base::out);

    file_out << "index"
             << ","
             << "R_scale_noisy"
             << ","
             << "G_scale_noisy"
             << ","
             << "B_scale_noisy"
             << ","
             << "R_scale_regular"
             << ","
             << "G_scale_regular"
             << ","
             << "B_scale_regular"
             << "," << endl;
    for (int i = 0; i < 256; i++)
    {
        // single_line.assign("");
        // single_line.append(to_string(i));
        // single_line.append(",");
        // single_line.append(to_string(R_scale_noisy[i]));
        // single_line.append(",");
        // single_line.append(to_string(G_scale_noisy[i]));
        // single_line.append(",");
        // single_line.append(to_string(B_scale_noisy[i]));
        // single_line.append("\n");
        file_out << i << ","
                 << (int)R_scale_noisy[i] << "," 
                 << (int)G_scale_noisy[i] << "," 
                 << (int)B_scale_noisy[i] << ","
                 << (int)R_scale_regular[i] << "," 
                 << (int)G_scale_regular[i] << "," 
                 << (int)B_scale_regular[i] << ","
                  << endl;
    }
    file_out.close();

    cv::Mat image(cv::Size(height, width), CV_8UC1, image_B);
    cv::imshow("test", image);
    cv::waitKey();

    return 0;
}
