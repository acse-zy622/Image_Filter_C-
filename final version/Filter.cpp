/**
 * @file Filter.cpp
 * @brief Implementation of the Filter class.
 *
 * This file contains the implementation of the Filter class used to apply 2d and 3d filters to images.
 *
 * Group Members:
 * - Hang Zhao (edsml-hz822)
 * - Luwen Liang (edsml-ll2822)
 * - Elliott Mcquire (acse-ecm22)
 * - Zhuoran Yang (acse-zy622)
 * - Qingyang Lu (acse-ql1522)
 */

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <cassert>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Filter.h"
#include "Image.h"

using namespace std;

/**
 * @brief Constructs a Filter object for image processing.
 *
 * This constructor initializes a Filter object with the provided image,
 * kernel size, sigma value, and depth values. It also sets the width, height,
 * channels, and image size based on the input image.
 *
 * @param image Reference to the input image to be processed.
 * @param kernel_size The size of the kernel to be used in the filter.
 * @param sigma The standard deviation of the Gaussian distribution used in the Gaussian blur filter.
 * @param depth depth Integer representing the depth of the image (number of layers or slices) for 3D image processing.
 */
Filter::Filter(Image &image, int kernel_size, float sigma, int depth) : image(image), kernel_size(kernel_size), sigma(sigma), depth(depth)
{
    this->width = image.get_width();
    this->height = image.get_height();
    this->channels = image.get_channels();
    this->img_size = width * height * channels;
    this->corrected_img = new unsigned char[width * height * channels];
}

/**
 * @brief Destructor for the Filter object.
 *
 * This destructor releases the memory allocated for the corrected_img buffer.
 */
Filter::~Filter()
{
    delete[] corrected_img;
}

/**
 * @brief Applies grayscale to an image.
 *
 * Calculates the average of each RGB value within the pixel and stores it as
 * an unsigned 8-bit integer in the output pixel. If the image has an alpha channel,
 * it stores the alpha channel in the second channel of the grayscale image.
 */
void Filter::ApplyGrayScale()
{
    unsigned char *img_data = image.data;
    // Set the number of channels in the grayscale image.
    int gray_channels = 1;
    corrected_img = new unsigned char[width * height * gray_channels];

    for (unsigned char *input_pixel = img_data, *output_pixel = corrected_img; input_pixel != img_data + img_size; input_pixel += channels, output_pixel += gray_channels)
    {
        // Calculate the average of each RGB value within the pixel and cast value to an unsigned 8-bit integer
        // to ensure the pixel value is represented by exactly one byte.
        *output_pixel = static_cast<uint8_t>((*input_pixel + *(input_pixel + 1) + *(input_pixel + 2)) / 3.0);
    }
    channels = gray_channels;
}

/**
 * @brief Balances the color of the image by scaling each color channel by
 * the ratio of the maximum intensity to the average intensity of that channel.
 */
void Filter::AutoColourBalance()
{
    unsigned char *img_data = image.data;
    size_t pixel_total = width * height;
    corrected_img = new unsigned char[width * height * channels];

    int red_total = 0;
    int green_total = 0;
    int blue_total = 0;

    // Calculate the total intensity of each channel
    for (unsigned char *input_pixel = img_data; input_pixel != img_data + img_size; input_pixel += channels)
    {
        red_total += *input_pixel;
        green_total += *(input_pixel + 1);
        blue_total += *(input_pixel + 2);
    }

    // Calculate the average intensity of each channel
    vector<double> inten_avg = {static_cast<double>(red_total) / pixel_total,
                                static_cast<double>(green_total) / pixel_total,
                                static_cast<double>(blue_total) / pixel_total};

    // Find the maximum intensity among all channels
    auto max_intensity = *max_element(begin(inten_avg), end(inten_avg));

    // Calculate the scale factor for each channel
    double red_scale = max_intensity / inten_avg[0];
    double green_scale = max_intensity / inten_avg[1];
    double blue_scale = max_intensity / inten_avg[2];

    // Scale each pixel in the image and store the result in corrected_img
    for (unsigned char *input_pixel = img_data, *output_pixel = corrected_img; input_pixel != img_data + img_size; input_pixel += channels, output_pixel += channels)
    {
        *output_pixel = std::min((*input_pixel * red_scale), 255.0);
        *(output_pixel + 1) = std::min((*(input_pixel + 1) * green_scale), 255.0);
        *(output_pixel + 2) = std::min((*(input_pixel + 2) * blue_scale), 255.0);
    }
}

/**
 * @brief Adjusts brightness of the image by scaling the intensity of each color
 * channel by the ratio of the desired brightness to the average intensity of that channel.
 *
 * @param brightness The desired brightness level, as an integer between 0 and 255.
 * @return None
 */
void Filter::Brightness(int brightness)
{
    unsigned char *img_data = image.data;
    size_t pixel_total = width * height;
    corrected_img = new unsigned char[width * height * channels];

    int red_total = 0;
    int green_total = 0;
    int blue_total = 0;

    // Calculate the total intensity for each color channel
    for (unsigned char *input_pixel = img_data; input_pixel != img_data + img_size; input_pixel += channels)
    {
        red_total += *input_pixel;
        green_total += *(input_pixel + 1);
        blue_total += *(input_pixel + 2);
    }

    // Calculate the average intensity for each color channel
    double red_avg = red_total / (double)pixel_total;
    double green_avg = green_total / (double)pixel_total;
    double blue_avg = blue_total / (double)pixel_total;

    // Calculate the scaling factor for each color channel based on the desired brightness level
    double red_scale = brightness / red_avg;
    double green_scale = brightness / green_avg;
    double blue_scale = brightness / blue_avg;

    // Scale the intensity of each color channel for each pixel in the image
    for (unsigned char *input_pixel = img_data, *output_pixel = corrected_img; input_pixel != img_data + img_size; input_pixel += channels, output_pixel += channels)
    {
        *output_pixel = std::max(0.0, std::min(static_cast<int>(*input_pixel) * red_scale, 255.0));
        *(output_pixel + 1) = std::max(0.0, std::min(static_cast<int>(*(input_pixel + 1)) * green_scale, 255.0));
        *(output_pixel + 2) = std::max(0.0, std::min(static_cast<int>(*(input_pixel + 2)) * blue_scale, 255.0));
    }
}

/**
 * @brief Applies the Sobel edge detection filter to the image.
 *
 * This function utilizes the Sobel operator to determine the gradient magnitude
 * for each pixel and applies the Sobel edge detection filter.
 * The operator is a pair of 3x3 convolution kernels, each for the X
 * and Y direction. The resulting image emphasizes the edges within the input image.
 */
void Filter::Sobel()
{
    // Allocate memory for the corrected image
    corrected_img = new unsigned char[width * height];
    unsigned char *img_data = image.data;
    int gx, gy;

    // Iterate through the image pixels
    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 1; x < width - 1; x++)
        {
            // Calculate the convolutions with the Sobel filter in X direction
            gx = -img_data[(y - 1) * width + (x - 1)] - 2 * img_data[y * width + (x - 1)] - img_data[(y + 1) * width + (x - 1)] +
                 img_data[(y - 1) * width + (x + 1)] + 2 * img_data[y * width + (x + 1)] + img_data[(y + 1) * width + (x + 1)];

            // Calculate the convolutions with the Sobel filter in Y direction
            gy = -img_data[(y - 1) * width + (x - 1)] - 2 * img_data[(y - 1) * width + x] - img_data[(y - 1) * width + (x + 1)] +
                 img_data[(y + 1) * width + (x - 1)] + 2 * img_data[(y + 1) * width + x] + img_data[(y + 1) * width + (x + 1)];

            // Calculate the gradient magnitude
            int mag = abs(gx) + abs(gy);

            // Set the output pixel value with a cap of 255, the max value represented by an 8-bit integer
            corrected_img[y * width + x] = (mag > 255) ? 255 : mag;
        }
    }
}

/**
 * @brief Applies the Prewitt edge detection filter to the image.
 *
 * This function utilizes the Prewitt operator to determine the gradient magnitude
 * for each pixel and applies the Prewitt edge detection filter.
 * The operator is a pair of 3x3 convolution kernels, for the X
 * and Y direction each. The resulting image emphasizes the edges within the input image.
 */
void Filter::Prewitt()
{
    // Allocate memory for the corrected image
    corrected_img = new unsigned char[width * height * channels];
    unsigned char *img_data = image.data;

    // Ensure the image dimensions and channels are valid
    assert(width > 0);
    assert(height > 0);
    assert(channels == 1);

    // Allocate memory for X and Y gradients
    int *gx = new int[width * height];
    int *gy = new int[width * height];

    // Calculate X gradient
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            int val = img_data[width * (i + 1) + j] + img_data[width * (i + 1) + j - 1] + img_data[width * (i + 1) + j + 1] -
                      (img_data[width * (i - 1) + j] + img_data[width * (i - 1) + j - 1] + img_data[width * (i - 1) + j + 1]);
            gx[width * i + j] = min(max(val, 0), 255);
        }
    }
    // Calculate Y gradient
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            int val = img_data[width * (i + 1) + j] + img_data[width * (i + 1) + j - 1] + img_data[width * (i + 1) + j + 1] -
                      (img_data[width * (i - 1) + j] + img_data[width * (i - 1) + j - 1] + img_data[width * (i - 1) + j + 1]);
            gy[width * i + j] = min(max(val, 0), 255);
        }
    }
    // Compute the value of image using X gradient and Y gradient
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            corrected_img[width * i + j] = sqrt(gx[width * i + j] * gx[width * i + j] + gy[width * i + j] * gy[width * i + j]);
        }
    }
    delete[] gx;
    delete[] gy;
}

/**
 * @brief Applies a box blur filter to the image.
 *
 * This function averages the pixel values within a square kernel
 * of the specified size to apply a box blur filter to the image.
 * The filter smooths the image and reduces noise.
 */
void Filter::box_blur()
{
    // Access the input image data
    unsigned char *img_data = image.data;
    corrected_img = new unsigned char[width * height * channels];
    const int kernel_radius = kernel_size / 2;

    // Create a vector to store the kernel values
    std::vector<unsigned char> kernel_values(kernel_size * kernel_size);

    // Iterate through each color channel
    for (int channel = 0; channel < channels; ++channel)
    {
        // Create a temporary copy of the image data for the current channel
        std::vector<unsigned char> temp_data(img_data, img_data + width * height * channels);

        // Iterate through the image pixels
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                // Extract the pixel values within the kernel for the current channel
                int index = 0;
                int sum = 0;
                for (int ky = -kernel_radius; ky <= kernel_radius; ++ky)
                {
                    for (int kx = -kernel_radius; kx <= kernel_radius; ++kx)
                    {
                        int nx = x + kx;
                        int ny = y + ky;
                        // Check if the neighbor pixel is within the image boundaries
                        if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                        {
                            unsigned char pixel_value = temp_data[(ny * width + nx) * channels + channel];
                            kernel_values[index++] = pixel_value;
                            sum += pixel_value;
                        }
                    }
                }

                // Set the pixel value at the center of the kernel to the average value for the current channel
                corrected_img[(y * width + x) * channels + channel] = sum / index;
            }
        }
    }
}

/**
 * @brief Applies Gaussian blur to the input image.
 *
 * This function uses a Gaussian kernel to apply a Gaussian blur to the input image.
 * The Filter class instantiation includes the kernel size and standard deviation/sigma.
 * The appearance of the final image will be smoother, with less noise and detail.
 */
void Filter::gaussian_blur()
{
    // Allocate memory for the corrected image
    corrected_img = new unsigned char[width * height * channels];
    // Access the input image data
    unsigned char *img_data = image.data;

    // Calculate the kernel radius based on the kernel size
    const int kernel_radius = kernel_size / 2;

    // Create a vector to store the kernel values
    std::vector<float> kernel_values(kernel_size * kernel_size);

    // Calculate the values of the Gaussian kernel
    float sum = 0.0f;
    for (int ky = -kernel_radius; ky <= kernel_radius; ++ky)
    {
        for (int kx = -kernel_radius; kx <= kernel_radius; ++kx)
        {
            float value = exp(-(kx * kx + ky * ky) / (2.0f * sigma * sigma));
            kernel_values[(ky + kernel_radius) * kernel_size + (kx + kernel_radius)] = value;
            sum += value;
        }
    }

    // Normalize the kernel
    for (int i = 0; i < kernel_size * kernel_size; ++i)
    {
        kernel_values[i] /= sum;
    }

    // Iterate through the image channels
    for (int channel = 0; channel < channels; ++channel)
    {
        // Create a temporary copy of the image data for the current channel
        std::vector<unsigned char> temp_data(img_data, img_data + width * height * channels);

        // Iterate through the image pixels
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                // Apply the Gaussian kernel to the pixel values within the kernel for the current channel
                float sum = 0.0f;
                for (int ky = -kernel_radius; ky <= kernel_radius; ++ky)
                {
                    for (int kx = -kernel_radius; kx <= kernel_radius; ++kx)
                    {
                        int nx = x + kx;
                        int ny = y + ky;
                        if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                        {
                            unsigned char pixel_value = temp_data[(ny * width + nx) * channels + channel];
                            float kernel_value = kernel_values[(ky + kernel_radius) * kernel_size + (kx + kernel_radius)];
                            sum += pixel_value * kernel_value;
                        }
                    }
                }

                // Set the pixel value at the center of the kernel to the convolved value for the current channel
                corrected_img[(y * width + x) * channels + channel] = static_cast<unsigned char>(sum + 0.5f);
            }
        }
    }
}

/**
 * @brief Applies a median blur to the input image.
 *
 * This function uses a square kernel to apply a meidan blur to the input image.
 * The Filter class instantiation includes the kernel size.
 * The appearance of the final image will be smoother, with reduced noise and preserved edges.
 */
void Filter::median_blur()
{
    // Allocate memory for the corrected image
    corrected_img = new unsigned char[width * height * channels];
    // Access the input image data
    unsigned char *img_data = image.data;

    // Calculate the kernel radius based on the kernel size
    const int kernel_radius = (kernel_size - 1) / 2;

    // Create a vector to store the kernel values
    std::vector<unsigned char> kernel_values(kernel_size * kernel_size);

    // Iterate through the image channels
    for (int channel = 0; channel < channels; ++channel)
    {
        // Iterate through the image pixels
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                // Extract the pixel values within the kernel for the current channel
                int index = 0;
                for (int ky = -kernel_radius; ky <= kernel_radius; ++ky)
                {
                    for (int kx = -kernel_radius; kx <= kernel_radius; ++kx)
                    {
                        int nx = x + kx;
                        int ny = y + ky;
                        if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                        {
                            kernel_values[index++] = img_data[(ny * width + nx) * channels + channel];
                        }
                    }
                }
                // Sort the values for the current channel
                for (int i = 0; i < kernel_size * kernel_size - 1; ++i)
                {
                    for (int j = 0; j < kernel_size * kernel_size - i - 1; ++j)
                    {
                        if (kernel_values[j] > kernel_values[j + 1])
                        {
                            float temp = kernel_values[j];
                            kernel_values[j] = kernel_values[j + 1];
                            kernel_values[j + 1] = temp;
                        }
                    }
                }

                // Set the pixel value at the center of the kernel to the median value for the current channel
                corrected_img[(y * width + x) * channels + channel] = kernel_values[(kernel_size * kernel_size) / 2];
            }
        }
    }
}

/**
 * Apply median blur filter on 3D image data for each channel
 *
 * @param data Pointer to the image data array
 * @param w Width of the image
 * @param h Height of the image
 * @param d Depth of the image
 * @param c Number of channels in the image
 * @param kernel_size Size of the kernel used for the median filter. Must be odd.
 */
void Filter::median_blur_3d()
{
    // Allocate memory for the corrected image
    corrected_img = new unsigned char[width * height * depth * channels];
    // Access the input image data
    unsigned char *img_data = image.data;

    const int kernel_radius = (kernel_size - 1) / 2;
    std::vector<unsigned char> kernel_values(kernel_size * kernel_size * kernel_size);

    for (int channel = 0; channel < channels; ++channel)
    {
        for (int z = 0; z < depth; ++z)
        {
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    // Get the median pixel value within the kernel for the current channel
                    std::vector<unsigned char> pixel_values;
                    int index = 0;
                    for (int kz = -kernel_radius; kz <= kernel_radius; ++kz)
                    {
                        for (int ky = -kernel_radius; ky <= kernel_radius; ++ky)
                        {
                            for (int kx = -kernel_radius; kx <= kernel_radius; ++kx)
                            {
                                int nx = x + kx;
                                int ny = y + ky;
                                int nz = z + kz;
                                if (nx >= 0 && nx < width && ny >= 0 && ny < height && nz >= 0 && nz < depth)
                                {
                                    kernel_values[index++] = img_data[((nz * height + ny) * width + nx) * channels + channel];
                                }
                            }
                        }
                    }
                    quickSort1(kernel_values, 0, kernel_values.size()-1);
                    // Set the pixel value at the center of the kernel to the median value for the current channel
                    corrected_img[((z * height + y) * width + x) * channels + channel] = kernel_values[kernel_values.size() / 2];
                }
            }
        }
    }
}

/**
 * Applies a 3D Gaussian blur filter to the input image data for each channel.
 * The blur is computed using a Gaussian kernel with the specified size and standard deviation.
 * The input data is assumed to be stored in row-major order with interleaved channels.
 *
 * @param data Pointer to the input image data. The size of the data buffer must be at least w * h * d * c bytes.
 * @param w Width of the input image in pixels.
 * @param h Height of the input image in pixels.
 * @param d Depth of the input image in pixels.
 * @param c Number of channels in the input image.
 * @param kernel_size Size of the Gaussian kernel in each dimension (e.g., 3 for a 3x3x3 kernel).
 * @param sigma Standard deviation of the Gaussian kernel in each dimension.
 */
void Filter::gaussian_blur_3d()
{
    // Allocate memory for the corrected image
    corrected_img = new unsigned char[width * height * depth * channels];
    // Access the input image data
    unsigned char *img_data = image.data;
    const int kernel_radius = (kernel_size - 1) / 2;
    const int kernel_size_tr = kernel_size * kernel_size * kernel_size;
    std::vector<float> kernel_values(kernel_size_tr);

    // Calculate the values of the kernel
    float sum = 0.0f;
    for (int kz = -kernel_radius; kz <= kernel_radius; ++kz)
    {
        for (int ky = -kernel_radius; ky <= kernel_radius; ++ky)
        {
            for (int kx = -kernel_radius; kx <= kernel_radius; ++kx)
            {
                float value = exp(-(kx * kx + ky * ky + kz * kz) / (2.0f * sigma * sigma));
                kernel_values[((kz + kernel_radius) * kernel_size + (ky + kernel_radius)) * kernel_size + (kx + kernel_radius)] = value;
                sum += value;
            }
        }
    }

    // Normalize the kernel
    for (int i = 0; i < kernel_size_tr; ++i)
    {
        kernel_values[i] /= sum;
    }

    for (int channel = 0; channel < channels; ++channel)
    {
        // Create a temporary copy of the image data for the current channel
        std::vector<unsigned char> temp_data(img_data, img_data + width * height * depth * channels);

        for (int z = 0; z < depth; ++z)
        {
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    // Apply the kernel to the pixel values within the kernel for the current channel
                    float sum = 0.0f;
                    for (int kz = -kernel_radius; kz <= kernel_radius; ++kz)
                    {
                        for (int ky = -kernel_radius; ky <= kernel_radius; ++ky)
                        {
                            for (int kx = -kernel_radius; kx <= kernel_radius; ++kx)
                            {
                                int nx = x + kx;
                                int ny = y + ky;
                                int nz = z + kz;
                                if (nx >= 0 && nx < width && ny >= 0 && ny < height && nz >= 0 && nz < depth)
                                {
                                    unsigned char pixel_value = temp_data[((nz * height + ny) * width + nx) * channels + channel];
                                    float kernel_value = kernel_values[((kz + kernel_radius) * kernel_size + (ky + kernel_radius)) * kernel_size + (kx + kernel_radius)];
                                    sum += pixel_value * kernel_value;
                                }
                            }
                        }
                    }

                    // Set the pixel value at the center of the kernel to the convolved value for the current channel
                    corrected_img[((z * height + y) * width + x) * channels + channel] = static_cast<unsigned char>(sum + 0.5f);
                }
            }
        }
    }
}

/**
 * @brief Saves the filtered image to a file.
 *
 * This function saves the filtered image to a file in PNG format.
 * The file is saved at the specified path.
 *
 * @param s_path The path where the filtered image should be saved.
 */
void Filter::SaveImg(const std::string &s_path)
{
    stbi_write_png(s_path.c_str(), width, height, channels, corrected_img, width * channels);
    std::cout << "Success, your filtered image has been saved";
}

/**
 * @brief Saves the corrected image to a folder.
 *
 * This function saves the corrected image to a folder in PNG format.
 * The folder is saved at the specified path.
 * 
 * @param s_path The path to the folder where the images will be saved.
 */
void Filter::SaveImgFolder(const std::string &s_path)
{
    for (int i = 0; i < depth; i++)
    {
        std::string filename = s_path + std::string(4 - std::to_string(i).length(), '0') + std::to_string(i) + ".png";
        std::cout << filename << std::endl;
        stbi_write_png(filename.c_str(), width, height, channels, &corrected_img[i * width * height * channels], 0);
    }
    std::cout << "Success, your Images have been saved into the folder";
}

/**
 * @brief Returns a pointer to the filtered image data.
 *
 * This function returns a pointer to the filtered image data.
 * The data is stored as an array of unsigned char values.
 *
 * @return A pointer to the filtered image data.
 */
unsigned char *Filter::get_corrected_img() const
{
    return corrected_img;
}

/**
 * Partitions a vector of unsigned char values for quicksort.
 *
 * @param val The vector to be partitioned.
 * @param l The lower index of the range to be partitioned.
 * @param h The upper index of the range to be partitioned.
 * @return The index of the pivot element.
 */
int Filter::separation1(std::vector<unsigned char>& val, int l, int h) {
    unsigned char piv = val[h];
    int temp;
    int i = l - 1;
    for (int j = l; j <= h - 1; j++) {
        if (val[j] <= piv) {
            i++;
            temp = val[j];
            val[j]=val[i];
            val[i]=temp;          
        }
    }
    temp=val[h];
    val[h]=val[i+1];
    val[i+1]=temp;
    return (i + 1);
}

/**
 * Sorts a vector of unsigned char values using the quicksort algorithm.
 *
 * @param val The vector to be sorted.
 * @param l The lower index of the range to be sorted.
 * @param h The upper index of the range to be sorted.
 * @return None.
 */
void Filter::quickSort1(std::vector<unsigned char>& val, int l, int h) {
    if (l < h) {
        int piv = separation1(val, l, h);
        quickSort1(val, l, piv - 1);
        quickSort1(val, piv + 1, h);
    }
}