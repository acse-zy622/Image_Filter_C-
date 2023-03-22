#pragma once

// The Image class represents an image with its data, width, height, and channels.
class Image {
public:
    unsigned char* data;
    
    // Constructor for testing: Initializes an Image object with the given data, width, height, and channels.
    Image(unsigned char* data, int width, int height, int channels);
    
    // Constructor for image: Initializes an Image object by loading an image from the specified file path.
    Image(const std::string& i_path);

    // Returns the width of the image.
    int get_width() const;

    // Returns the height of the image.
    int get_height() const;

    // Returns the number of channels in the image.
    int get_channels() const;

private: 
    std::string img_path;
    int width, height, channels;
};
