#pragma once

#include <string>
#include "Image.h"

// The Filter class provides various image filters
class Filter
{
public:
    // Constructor: Initializes a Filter object with the given image, kernel size, sigma, and depth values.
    Filter(Image &image, int k_size = 0, float sig = 1.0f, int d = 1);

    // Destructor: Frees the memory allocated for the corrected_img buffer.
    ~Filter();

    // Applies a grayscale filter to the image.
    void ApplyGrayScale();

    // Applies an automatic color balance filter to the image.
    void AutoColourBalance();

    // Adjusts the brightness of the image by the specified amount.
    void Brightness(int brightness);

    // Applies the Sobel edge detection filter to the image.
    void Sobel();

    // Applies the Prewitt edge detection filter to the image.
    void Prewitt();

    // Applies a median blur filter to the image.
    void median_blur();

    // Applies a box blur filter to the image.
    void box_blur();

    // Applies a Gaussian blur filter to the image.
    void gaussian_blur();

    // Applies a median blur filter to a 3D image.
    void median_blur_3d();

    // Applies a Gaussian blur filter to a 3D image.
    void gaussian_blur_3d();

    // Saves the filtered image to a file at the specified path.
    void SaveImg(const std::string &s_path);

    // Saves the filtered image to a folder at the specified path.
    void SaveImgFolder(const std::string &s_path);

    // Returns a pointer to the filtered image data.
    unsigned char *get_corrected_img() const;

private:
    Image &image;                 // Reference to the input image
    int kernel_size;              // Size of the kernel used for blur operations
    float sigma;                  // Sigma value used for Gaussian blur
    int depth;                    // Depth of the input image (for 3D image operations)
    int width;                    // Width of the input image
    int height;                   // Height of the input image
    int channels;                 // Number of channels in the input image (3 for RGB and 1 for grayscale)
    size_t img_size;              // Total size of the image data (width * height * channels)
    unsigned char *corrected_img; // Pointer to the corrected image data after applying filters
};
