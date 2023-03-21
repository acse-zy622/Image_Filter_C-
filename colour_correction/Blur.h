#pragma once
#include <vector>
#include <algorithm>
#include <cmath>
#include "stb_image.h"
#include "stb_image_write.h"

template<class T>
class Blur 
{
public:	

    // Constructor
    Blur(char const* i_path, char const* s_path, int k_size, float sig) {
        img_path = i_path;
        save_path = s_path;
        kernel_size = k_size;
        sigma = sig;
    }

    // box blur method
    void box_blur() {
        data = stbi_load(img_path, &w, &h, &c, 0);
        const int kernel_radius = kernel_size / 2;

        std::vector<unsigned char> kernel_values(kernel_size * kernel_size);

        for (int channel = 0; channel < c; ++channel) {
            // Create a temporary copy of the image data for the current channel
            std::vector<unsigned char> temp_data(data, data + w * h * c);

            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    // Extract the pixel values within the kernel for the current channel
                    int index = 0;
                    int sum = 0;
                    for (int ky = -kernel_radius; ky <= kernel_radius; ++ky) {
                        for (int kx = -kernel_radius; kx <= kernel_radius; ++kx) {
                            int nx = x + kx;
                            int ny = y + ky;
                            if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
                                unsigned char pixel_value = temp_data[(ny * w + nx) * c + channel];
                                kernel_values[index++] = pixel_value;
                                sum += pixel_value;
                            }
                        }
                    }

                    // Set the pixel value at the center of the kernel to the average value for the current channel
                    data[(y * w + x) * c + channel] = sum / index;
                }
            }
        }
    }

    void gaussian_blur() {
        data = stbi_load(img_path, &w, &h, &c, 0);
        const int kernel_radius = kernel_size / 2;
        std::vector<float> kernel_values(kernel_size * kernel_size);

        // Calculate the values of the kernel
        float sum = 0.0f;
        for (int ky = -kernel_radius; ky <= kernel_radius; ++ky) {
            for (int kx = -kernel_radius; kx <= kernel_radius; ++kx) {
                float value = exp(-(kx * kx + ky * ky) / (2.0f * sigma * sigma));
                kernel_values[(ky + kernel_radius) * kernel_size + (kx + kernel_radius)] = value;
                sum += value;
            }
        }

        // Normalize the kernel
        for (int i = 0; i < kernel_size * kernel_size; ++i) {
            kernel_values[i] /= sum;
        }

        for (int channel = 0; channel < c; ++channel) {
            // Create a temporary copy of the image data for the current channel
            std::vector<unsigned char> temp_data(data, data + w * h * c);

            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    // Apply the kernel to the pixel values within the kernel for the current channel
                    float sum = 0.0f;
                    for (int ky = -kernel_radius; ky <= kernel_radius; ++ky) {
                        for (int kx = -kernel_radius; kx <= kernel_radius; ++kx) {
                            int nx = x + kx;
                            int ny = y + ky;
                            if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
                                unsigned char pixel_value = temp_data[(ny * w + nx) * c + channel];
                                float kernel_value = kernel_values[(ky + kernel_radius) * kernel_size + (kx + kernel_radius)];
                                sum += pixel_value * kernel_value;
                            }
                        }
                    }

                    // Set the pixel value at the center of the kernel to the convolved value for the current channel
                    data[(y * w + x) * c + channel] = static_cast<unsigned char>(sum + 0.5f);
                }
            }
        }
    }

    void median_blur() {
        const int kernel_radius = (kernel_size - 1) / 2;

        std::vector<unsigned char> kernel_values(kernel_size * kernel_size);

        for (int channel = 0; channel < c; ++channel) {
            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    // Extract the pixel values within the kernel for the current channel
                    int index = 0;
                    for (int ky = -kernel_radius; ky <= kernel_radius; ++ky) {
                        for (int kx = -kernel_radius; kx <= kernel_radius; ++kx) {
                            int nx = x + kx;
                            int ny = y + ky;
                            if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
                                kernel_values[index++] = data[(ny * w + nx) * c + channel];
                            }
                        }
                    }

                    // Sort the pixel values for the current channel
                    std::sort(kernel_values.begin(), kernel_values.end());

                    // Set the pixel value at the center of the kernel to the median value for the current channel
                    data[(y * w + x) * c + channel] = kernel_values[(kernel_size * kernel_size) / 2];
                }
            }
        }
    }

    void SaveImg() {

        //int success = stbi_write_png(save_path, width, height, gray_channels, gray_img, 0);
        int success = stbi_write_png(save_path, w, h, c, data, 0);
        std::cout << "Success, your blurry Image has been saved";

    }



private:
    char const* img_path = nullptr;
    char const* save_path = nullptr;
    unsigned char* data;
    int w;
    int h;
    int c;
    int kernel_size;
    float sigma;
};
