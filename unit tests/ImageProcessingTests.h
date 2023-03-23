#pragma once

#include "Filter.h"
#include "Image.h"
#include <cstring>
#include <cmath>
#include <cassert>

// The ImageProcessingTests class is used to test various image processing functions.
class ImageProcessingTests {
public:
    // Constructor: Initializes an ImageProcessingTests object.
    ImageProcessingTests(); 

    // Destructor: Cleans up resources used by the ImageProcessingTests object.
    ~ImageProcessingTests(); 

    // Test function for applying grayscale to an image.
    void test_apply_gray_scale();

    // Test function for applying auto color balance to an image.
    void test_auto_colour_balance();

    // Test function for adjusting the brightness of an image.
    void test_brightness();

    // Test function for applying median blur to an image.
    void test_median_blur();

    // Test function for applying box blur to an image.
    void test_box_blur();

    // Test function for applying Gaussian blur to an image.
    void test_gaussian_blur();

    // Test function for applying Sobel edge detection to an image.
    void test_sobel_edge_detection();

    // Test function for applying Prewitt edge detection to an image.
    void test_prewitt_edge_detection();

    // Test function for applying median blur to a 3D image.
    void test_median_blur_3d();

    // Test function for applying Gaussian blur to a 3D image.
    void test_gaussian_blur_3d();

private:
    unsigned char* img_data;       // Pointer to the image data
    unsigned char* gray_data;      // Pointer to the grayscale image data
    unsigned char* corrected_img;  // Pointer to the corrected image data
    int w;                         // Image width
    int h;                         // Image height
    int c;                         // Number of image channels
    int kernel_size;               // Kernel size for blur operations
    float sigma;                   // Sigma value for Gaussian blur
    int d;                         // Depth for 3D image operations
};










   
