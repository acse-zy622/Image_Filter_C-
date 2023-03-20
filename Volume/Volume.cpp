// VolumeOfData.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <filesystem>
#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <vector>


// Shortens the amount I need to type below.

// the element type in vectors.
struct Image {
    int width;
    int height;
    int channels;
    unsigned char* data;
};

class Volume {
public:
    // Constructor for Volume
    Volume() {}
    // Add an image to the volume
    void addImage(const char* filename) {
        int w, h, c;
        unsigned char* data = stbi_load(filename, &w, &h, &c, 0);
        if (!data) {
            std::cerr << "Failed to load image: " << filename << std::endl;
            return;
        }
        Image img = { w, h, c, data };
        images.push_back(img);
    }

    void addImageFolder(const char* folderPath) {
        for (const auto& file : std::filesystem::directory_iterator(folderPath)) {
            if (file.path().extension() == ".png") {
                int w, h, c;
                std::cout << file.path() << std::endl;

                unsigned char* data = stbi_load(file.path().string().c_str(), &w, &h, &c, 0);
                if (!data) {
                    std::cerr << "Failed to load image: " << file.path() << std::endl;
                    continue;
                }
                Image img = { w, h, c, data };
                images.push_back(img);
            }
        }
    }

    // Get a specific image from the volume
    const Image& getImage(int i) {    // should it be a const?
        if (i >= images.size()) {
            throw std::out_of_range("Image index out of range");
        }
        else {
            return images[i];
        }
    }

    // destructor for the volume.
    ~Volume() {
        for (auto& img : images) {
            stbi_image_free(img.data);
        }
    }

private:
    // Store image objects in the vector.
    std::vector<Image> images;
};


int main() {
    
    Volume volume;
    volume.addImage("Images/dimorphos.png"); // add images one by one
    
    Volume volume2;
    volume2.addImageFolder("images/"); // add all images in folders
    
    for (int i = 0; i < 6; i++) {
        Image im = volume2.getImage(i); // get by index

        // check if implemented rightly.
        std::cout << "Image loaded with size " << im.width << " x " << im.height << " with " << im.channels << " channel(s)." << std::endl;
    }

   

    //// print one image size to screen
    //std::cout << "Image loaded with size " << im.width << " x " << im.height << " with " << im.channels << " channel(s)." << std::endl;



    return 0;
  }





