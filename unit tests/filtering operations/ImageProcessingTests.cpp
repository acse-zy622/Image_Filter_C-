/**
 * @file ImageProcessingTests.cpp
 * @brief Unit tests for the image processing functions (2d and 3d)
 *
 * This file contains the unit tests for the image processing fucntions. 
 *
 * Group Members:
 * - Hang Zhao (edsml-hz822)
 * - Luwen Liang (edsml-ll2822)
 * - Elliott Mcquire (acse-ecm22)
 * - Zhuoran Yang (acse-zy622)
 * - Qingyang Lu (acse-ql1522)
 */

#include "ImageProcessingTests.h"
#include "Filter.h"
#include "Image.h"
#include <cstring>
#include <cmath>
#include <cassert>
#include <iostream>

/**
 * @brief Construct a new Image Processing Tests:: Image Processing Tests object
 *
 */
ImageProcessingTests::ImageProcessingTests()
{
    img_data = nullptr;
    corrected_img = nullptr;
    w = 0;
    h = 0;
    c = 0;
    d = 0;
    sigma = 1.0f;
};

/**
 * @brief Destroy the Image Processing Tests:: Image Processing Tests object
 *
 */
ImageProcessingTests::~ImageProcessingTests()
{
    if (img_data)
    {
        delete[] img_data;
    }
    if (corrected_img)
    {
        delete[] corrected_img;
    }
};

/**
 * Applies an apply gray scale filter for testing.
 */
void ImageProcessingTests::test_apply_gray_scale()
{
    // Sample input data (2x2 RGB image)
    unsigned char data1[] = {
        1, 2, 3, 4, 5, 6,
        7, 8, 9, 10, 11, 12};

    // Sample input data (2x2 image with an alpha channel)
    unsigned char data2[] = {
        1, 2, 3, 255, 4, 5, 6, 255,
        7, 8, 9, 255, 10, 11, 12, 255};

    // Expected output data for applying gray scale
    unsigned char expected_output_data1[] = {
        2, 5,
        8, 11};

    unsigned char expected_output_data2[] = {
        2, 255, 5, 255,
        8, 255, 11, 255};

    Image im(data1, 2, 2, 3);
    Filter filter1(im);
    filter1.ApplyGrayScale();

    Image im2(data2, 2, 2, 4);
    Filter filter2(im2);
    filter2.ApplyGrayScale();

    unsigned char *corrected_img1 = filter1.get_corrected_img();
    unsigned char *corrected_img2 = filter2.get_corrected_img();

    for (int i = 0; i < 2 * 2 * 1; ++i)
    {
        assert(abs(corrected_img1[i] - expected_output_data1[i]) <= 1);
    }
    for (int i = 0; i < 2 * 2 * 2; ++i)
    {
        assert(abs(corrected_img2[i] - expected_output_data2[i]) <= 1);
    }
};

/**
 * Applies an auto colour balance filter for testing.
 */
void ImageProcessingTests::test_auto_colour_balance()
{
    // Sample input data (2x2 RGB image)
    unsigned char data[] = {
        1, 2, 3, 4, 5, 6,
        7, 8, 9, 10, 11, 12};

    // Expected output data for auto colour balance
    unsigned char expected_output_data[] = {
        1, 2, 3, 5, 5, 6,
        9, 9, 9, 13, 12, 12};

    w = 2;
    h = 2;
    c = 3;

    Image im(data, w, h, c);
    Filter filter(im);
    filter.AutoColourBalance();

    unsigned char *corrected_img = filter.get_corrected_img();

    for (int i = 0; i < w * h * c; ++i)
    {
        assert(abs(corrected_img[i] - expected_output_data[i]) <= 1);
    }
}

/**
 * Applies a brightness filter for testing.
 */
void ImageProcessingTests::test_brightness()
{
    // Sample input data (2X2 RGB image)
    unsigned char data[] = {
        1, 2, 3, 4, 5, 6,
        7, 8, 9, 10, 11, 12};

    // Expected output data for brightness (2x2 RGB image)
    unsigned char expected_output_data[] = {
        9, 15, 20, 36, 38, 40,
        63, 61, 60, 90, 84, 80};

    int brightness_value = 50;

    w = 2;
    h = 2;
    c = 3;

    Image im(data, w, h, c);
    Filter filter(im);
    filter.Brightness(brightness_value);

    unsigned char *corrected_img = filter.get_corrected_img();

    for (int i = 0; i < 3 * 3 * 1; ++i)
    {
        assert(abs(corrected_img[i] - expected_output_data[i]) <= 1);
    }
}

/**
 * Applies a median blur filter for testing.
 */
void ImageProcessingTests::test_median_blur()
{

    // Sample input data (4x4 grayscale image)
    unsigned char data[] = {
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10,
        11,
        12,
        13,
        14,
        15,
        16,
    };

    // Expected output data for the median blur filter
    unsigned char expected_output_data[] = {
        0,
        5,
        6,
        7,
        7,
        7,
        7,
        10,
        11,
        11,
        11,
        14,
        14,
        14,
        15,
        15,
    };

    w = 4;
    h = 4;
    c = 1;
    kernel_size = 3;

    Image im(data, w, h, c);
    Filter filter(im, kernel_size);
    filter.median_blur();

    unsigned char *corrected_img = filter.get_corrected_img();

    for (int i = 0; i < 4 * 4 * 1; ++i)
    {
        assert(abs(corrected_img[i] - expected_output_data[i]) <= 1);
    }
}

/**
 * Applies a box blur filter for testing.
 */
void ImageProcessingTests::test_box_blur()
{
    // Sample input data (4x4 grayscale image)
    unsigned char data1[] = {
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10,
        11,
        12,
        13,
        14,
        15,
        16,
    };

    // Sample input data (2x2 RGB image)
    unsigned char data2[] = {
        1, 2, 3, 4, 5, 6,
        7, 8, 9, 10, 11, 12};

    // Expected output data for the box blur filter
    unsigned char expected_data1[] = {
        3,
        4,
        5,
        5,
        5,
        6,
        7,
        7,
        9,
        10,
        11,
        11,
        11,
        12,
        13,
        13,
    };

    unsigned char expected_data2[] = {
        5, 6, 7, 5, 6, 7,
        5, 6, 7, 5, 6, 7};

    Image im1(data1, 4, 4, 1);
    Filter filter1(im1, 3);
    filter1.box_blur();
    unsigned char *corrected_img1 = filter1.get_corrected_img();

    Image im2(data2, 2, 2, 3);
    Filter filter2(im2, 3);
    filter2.box_blur();
    unsigned char *corrected_img2 = filter2.get_corrected_img();

    for (int i = 0; i < 4 * 4 * 1; ++i)
    {
        assert(abs(corrected_img1[i] - expected_data1[i]) <= 1);
    }
    for (int i = 0; i < 2 * 2 * 3; ++i)
    {
        assert(abs(corrected_img2[i] - expected_data2[i]) <= 1);
    }
}

/**
 * Applies a gaussian blur filter for testing.
 */
void ImageProcessingTests::test_gaussian_blur()
{
    // Sample input data (3x3 grayscale image)
    unsigned char data[] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9};

    // Expected output data for the gaussian blur filter
    unsigned char expected_data[] = {
        1, 2, 2,
        3, 5, 4,
        3, 5, 4};

    w = 3;
    h = 3;
    c = 1;

    Image im(data, w, h, c);
    Filter filter(im, 3, 1.0f);
    filter.gaussian_blur();

    unsigned char *corrected_img = filter.get_corrected_img();
    // unsigned char* corrected_img = filter.corrected_img();

    for (int i = 0; i < w * h * c; ++i)
    {
        assert(abs(corrected_img[i] - expected_data[i]) <= 1);
    }
}

/**
 * Applies a sobel edge detection filter for testing.
 */
void ImageProcessingTests::test_sobel_edge_detection()
{
    // Sample input data (3x3 grayscale image)
    unsigned char data1[] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9};

    // Sample input data (4x4 grayscale image)
    unsigned char data2[] = {
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10,
        11,
        12,
        13,
        14,
        15,
        16,
    };

    // Expected output data for the Sobel edge detection
    unsigned char expected_data1[] = {
        0, 0, 0,
        0, 32, 0,
        0, 0, 0};

    unsigned char expected_data2[] = {
        0, 0, 0, 0,
        0, 40, 40, 0,
        0, 40, 40, 0,
        0, 0, 0, 0};

    Image im1(data1, 3, 3, 1);
    Filter filter1(im1);
    filter1.Sobel();
    unsigned char *corrected_img1 = filter1.get_corrected_img();

    Image im2(data2, 4, 4, 1);
    Filter filter2(im2);
    filter2.Sobel();
    unsigned char *corrected_img2 = filter2.get_corrected_img();

    for (int i = 0; i < 3 * 3 * 1; ++i)
    {
        assert(abs(corrected_img1[i] - expected_data1[i]) <= 1);
    }

    for (int i = 0; i < 4 * 4 * 1; ++i)
    {
        assert(abs(corrected_img2[i] - expected_data2[i]) <= 1);
    }
}

/**
 * Applies a prewitt edge detection filter for testing.
 */
void ImageProcessingTests::test_prewitt_edge_detection()
{
    // Sample input data (3x3 grayscale image)
    unsigned char data1[] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9};

    // Sample input data (4x4 grayscale image)
    unsigned char data2[]{
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10,
        11,
        12,
        13,
        14,
        15,
        16,
    };

    // Expected output data for the Prewitt edge detection
    unsigned char expected_data1[] = {
        0, 0, 0,
        0, 25, 0,
        0, 0, 0};

    unsigned char expected_data2[] = {
        0, 0, 0, 0,
        0, 33, 33, 0,
        0, 33, 33, 0,
        0, 0, 0, 0};

    Image im1(data1, 3, 3, 1);
    Filter filter1(im1);
    filter1.Prewitt();
    unsigned char *corrected_img1 = filter1.get_corrected_img();

    Image im2(data2, 4, 4, 1);
    Filter filter2(im2);
    filter2.Prewitt();
    unsigned char *corrected_img2 = filter2.get_corrected_img();

    for (int i = 0; i < 3 * 3 * 1; ++i)
    {
        assert(abs(corrected_img1[i] - expected_data1[i]) <= 1);
    }

    for (int i = 0; i < 4 * 4 * 1; ++i)
    {
        assert(abs(corrected_img2[i] - expected_data2[i]) <= 1);
    }
}

/**
 * Applies a 3d median blur filter for testing.
 */
void ImageProcessingTests::test_median_blur_3d()
{
    // Sample input data (3x3x2 grayscale image)
    unsigned char data1[] = {
        1, 2, 3, // First layer (slice)
        4, 5, 6,
        7, 8, 9,

        10, 11, 12, // Second layer (slice)
        13, 14, 15,
        16, 17, 18};

    // Expected output data for the 3d median blur filter
    unsigned char expected_data1[] = {
        0,
        4,
        10, // First layer (slice)
        11,
        13,
        14,
        14,
        15,
        16,

        16,
        16,
        16, // Second layer (slice)
        16,
        14,
        16,
        17,
        17,
        17,
    };

    Image im1(data1, 3, 3, 1);
    Filter filter1(im1, 3, 1.0f, 2);
    filter1.median_blur_3d();
    unsigned char *corrected_img1 = filter1.get_corrected_img();

    for (int i = 0; i < 3 * 3 * 2 * 1; ++i)
    {
        assert(abs(corrected_img1[i] - expected_data1[i]) <= 1);
    }
}

/**
 * Applies a 3d gaussian blur filter for testing.
 */
void ImageProcessingTests::test_gaussian_blur_3d()
{
    // Sample input data (2x2x2 grayscale image)
    unsigned char data1[] = {
        10, 20, // First layer (slice)
        30, 40,

        50, 60, // Second layer (slice)
        70, 80};

    // Sample input data (3x3x3 grayscale image)
    unsigned char data2[] = {
        1, 2, 3, // First layer (slice)
        4, 5, 6,
        7, 8, 9,

        10, 11, 12, // Second layer (slice)
        13, 14, 15,
        16, 17, 18,

        19, 20, 21, // Third layer (slice)
        22, 23, 24,
        25, 26, 27};

    // Expected output data for the 3d gaussian blur filter
    unsigned char expected_data1[] = {
        14, 15,
        16, 17,

        18, 19,
        20, 20};

    unsigned char expected_data2[] = {
        2, 3, 3,
        4, 6, 5,
        4, 5, 4,

        6, 9, 7,
        10, 14, 11,
        8, 12, 9,

        7, 9, 7,
        10, 14, 11,
        8, 11, 8};

    Image im1(data1, 2, 2, 1);
    Filter filter1(im1, 3, 1.0f, 2);
    filter1.gaussian_blur_3d();
    unsigned char *filtered_data1 = filter1.get_corrected_img();

    Image im2(data2, 3, 3, 1);
    Filter filter2(im2, 3, 1.0f, 3);
    filter2.gaussian_blur_3d();
    unsigned char *filtered_data2 = filter2.get_corrected_img();

    for (size_t i = 0; i < 8; ++i)
    {
        assert(abs(filtered_data1[i] - expected_data1[i]) <= 1);
    }

    for (size_t i = 0; i < 27; ++i)
    {
        assert(abs(filtered_data2[i] - expected_data2[i]) <= 1);
    }
}
