#include <string>
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"

/**
 * @brief Constructs an Image object for testing purposes.
 *
 * This constructor initializes an Image object with the provided data, width, height, and channels.
 *
 * @param data Pointer to the image data.
 * @param width Width of the image.
 * @param height Height of the image.
 * @param channels Number of channels in the image.
 */
Image::Image(unsigned char* data, int width, int height, int channels)
    : data(data), width(width), height(height), channels(channels) {
}

/**
 * @brief Constructs an Image object by loading an image from a file.
 *
 * This constructor initializes an Image object by loading an image from the specified file path.
 *
 * @param img_path Path to the image file.
 */
Image::Image(const std::string& img_path) : img_path(img_path) {
    data = stbi_load(img_path.c_str(), &width, &height, &channels, 0);
}

/**
 * @brief Returns the width of the image.
 *
 * @return Width of the image.
 */
int Image::get_width() const {
    return width;
}

/**
 * @brief Returns the height of the image.
 *
 * @return Height of the image.
 */
int Image::get_height() const {
    return height;
}

/**
 * @brief Returns the number of channels in the image.
 *
 * @return Number of channels in the image.
 */
int Image::get_channels() const {
    return channels;
}
