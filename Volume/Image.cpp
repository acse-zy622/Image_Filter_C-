#include <string>
#include "Image.h"


// constructor for testing
Image::Image(unsigned char* data, int width, int height, int channels)
    : data(data), width(width), height(height), channels(channels) {
}

// constructor for image
Image::Image(const std::string& img_path) : img_path(img_path) {
    data = stbi_load(img_path.c_str(), &width, &height, &channels, 0);
}

int Image::get_width() const {
    return width;
}

int Image::get_height() const {
    return height;
}

int Image::get_channels() const {
    return channels;
}


