# EE569 Homework Assignment #1
# Date: Jan 29, 2023
# Name: Baosheng Chang
# ID: 9660914048
# email: baosheng@usc.edu
#
# Operating Environment: MacOS Monterey, M1 chip
========================================================================
Requirement: latest Opencv and latest pkg-config need to installed for compiling the code
Steps:


#Usage

##Problem 1

### problem 1 a
1. run `make Q1_A`. This will generate Q1_A
2. run `./Q1_A input_file output_file`
Q1_A will read the input_file, then process the image, and write the image to output_file

### problem 1 b
Q1_B_Method_a.cpp implement the transfer-function-based histogram equalization. To run it, follow the following command
1. run `make Q1_B_Method_a`. This will generate Q1_B_Method_a
2. run `./Q1_B_Method_a input_file output_file`
Q1_B_Method_a will read the input_file, then process the image, and write the image to output_file

Q1_B_Method_b.cpp implement the bucket filling histogram equalization. To run it, follow the following command
1. run `make Q1_B_Method_b`. This will generate Q1_B_Method_b
2. run `./Q1_B_Method_b input_file output_file`
Q1_B_Method_b will read the input_file, then process the image, and write the image to output_file

### problem 1 c
Q1_C_CLAHE.cpp implement the CLAHE histogram equailzation. To run it, follow the following command
1. run `make Q1_C_CLAHE`. This will generate Q1_C_CLAHE
2. run `./Q1_C_CLAHE input_file output_file ClipLimit TilesGridSize`
Q1_C_CLAHE will read the input_file and process the image with input parameters (ClipLimit TilesGridSize).
Last, write the image to output_file.

Q1_C_Method_a.cpp implement the transfer-function-based histogram equalization. To run it, follow the following command
1. run `make Q1_C_Method_a`. This will generate Q1_C_Method_a
2. run `./Q1_C_Method_a input_file output_file`
Q1_C_Method_a will read the input_file, then process the image, and write the image to output_file

Q1_C_Method_b.cpp implement the bucket filling histogram equalization. To run it, follow the following command
1. run `make Q1_C_Method_b`. This will generate Q1_C_Method_b
2. run `./Q1_C_Method_b input_file output_file`
Q1_C_Method_b will read the input_file, then process the image, and write the image to output_file

##Problem 2
### problem 2 a
Q2_A_mean.cpp implement the mean filter Denosising. To run it, follow the following command
1. run `make Q2_A_mean`. This will generate Q2_A_mean
2. run `./Q2_A_mean input_file output_file`
Q2_A_mean will read the input_file, then process the image, and write the image to output_file

Q2_A_Gaussian.cpp implement the Gaussian filter Denosising. To run it, follow the following command
1. run `make Q2_A_Gaussian`. This will generate Q2_A_Gaussian
2. run `./Q2_A_Gaussian input_file output_file`
Q2_A_Gaussian will read the input_file, then process the image, and write the image to output_file

### problem 2 b
Q2_B.cpp implement the Bilateral filter Denosising. To run it, follow the following command
1. run `make Q2_B`. This will generate Q2_B
2. run `./Q2_B input_file output_file sigma_c sigma_s`
Q2_B will read the input_file, then process the image and process the image with input parameters (sigma_c sigma_s).
Last, write the image to output_file.

### problem 2 c
Q2_C.cpp implement the NLM filter Denosising. To run it, follow the following command
1. run `make Q2_C`. This will generate Q2_C
2. run `./Q2_C input_file output_file search_window_size template_window_size h`
Q2_C will read the input_file, then process the image and process the image with 
input parameters (search_window_size template_window_size h). Last, write the image to output_file.

### problem 2 d (4)
Q2_D_4.cpp implement the denoising designed by problem 2 d (3). To run it, follow the following command
1. run `make Q2_D_4`. This will generate Q2_D_4
2. run `./Q2_D_4 input_file output_file`
Q2_D_4 will read the input_file, then process the image, and write the image to output_file

### problem 2 d (5)
Q2_D_5.cpp implement the mean filter denoising on R,G,B channel. To run it, follow the following command
1. run `make Q2_D_5`. This will generate Q2_D_5
2. run `./Q2_D_5 input_file output_file`
Q2_D_5 will read the input_file, then process the image, and write the image to output_file

### problem 2 d (6)
Q2_D_6.cpp implement the mean filter denoising on H channel with numerical averaging. To run it, follow the following command
1. run `make Q2_D_6`. This will generate Q2_D_6
2. run `./Q2_D_6 input_file output_file`
Q2_D_6 will read the input_file, then process the image, and write the image to output_file

### problem 2 d (7)
Q2_D_7.cpp implement the mean filter denoising on H channel with angular averaging. To run it, follow the following command
1. run `make Q2_D_7`. This will generate Q2_D_7
2. run `./Q2_D_7 input_file output_file`
Q2_D_7 will read the input_file, then process the image, and write the image to output_file

/////////////////////////////////////////////////////////////////////////////
Other standard files:

PSNR_color.cpp PSNR_grey.cpp
    These files are used for calculate the PSNR value of the image

Q2_D_image_process.cpp
    This file is used for exporting the statistic of the noisy image. the data is then processed using python.

Q1_C_Method_a_array.cpp
    do the same function as Q1_C_Method_a.cpp, but implemented using array instead of vector

Q1_C_OpenCV.cpp
    do the same function as Q1_C_CLAHE.cpp, but implemented entirelyusing OpenCV. Used for debugging 

/////////////////////////////////////////////////////////////////////////////
