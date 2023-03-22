#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

class Image {
public:
    unsigned char* data;
    
    // constructor for testing
    Image(unsigned char* data, int width, int height, int channels);
    // constructor for image
    Image(const std::string& i_path);

    int get_width() const;
    int get_height() const;
    int get_channels() const;

private: 
    std::string img_path;
    int width, height, channels;
};
