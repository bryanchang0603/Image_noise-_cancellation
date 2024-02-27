// # EE569 Homework Assignment #1
// # Date: Jan 29, 2023
// # Name: Baosheng Chang
// # ID: 9660914048
// # email: baosheng@usc.edu
// #
// # Operating Environment: MacOS Monterey, M1 chip
// ========================================================================

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    std::string image_path = argv[1];
    std::ifstream file_in;
    file_in.open(image_path, std::ios::binary);
    FILE *file;

    file_in.seekg(0, file_in.end); // move the pointer to end
    int length = file_in.tellg();  // show the entire length og the image
    file_in.seekg(0, file_in.beg); // move pointer to begining

    char *buffer = new char[length];
    file_in.read(buffer, length);

    cv::Mat image_in(cv::Size(750, 422), CV_8UC3, buffer);
    cv::Mat image_YUV(cv::Size(750, 422), CV_8UC3);
    cv::Mat image_out(cv::Size(750, 422), CV_8UC3);
    std::vector<cv::Mat> YUV_channel(3);
    cv::Mat image_Y_adjusted;
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();

    // convert image to YUV
    cv::cvtColor(image_in, image_YUV, COLOR_BGR2Luv);
    split(image_YUV, YUV_channel);

    // set clahe parameter
    clahe->setClipLimit(atoi(argv[3])); //2
    clahe->setTilesGridSize(cv::Size(atoi(argv[4]),atoi(argv[4]))); //20
    clahe->apply(YUV_channel[0], image_Y_adjusted);
    image_Y_adjusted.copyTo(YUV_channel[0]);
    merge(YUV_channel, image_YUV);
    cv::cvtColor(image_YUV, image_out, COLOR_Luv2RGB);
    cv::imshow("image in", image_out);
    cv::waitKey();

    return 0;
}
