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

    int getImageNumber() {
        return images.size();
    }

    // adjust get index for 3d filters.
    const std::vector<Image>& getImageBatch(int batch_number, int kernal_length, int total_length) {
        std::vector<Image> v;
        if (total_length >= images.size()) {
            throw std::out_of_range("Image index out of range");
        }
        else {
            for (int i = batch_number * kernal_length; i < batch_number * kernal_length + kernal_length - 1; i++) {
                v.push_back(images[i]);
            }
            return v;
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


unsigned char* Get_XZ_slice(Volume& img, int y) {
    int z = img.getImageNumber();
    int w = img.getImage(0).width;
    unsigned char* xz_slice;
    xz_slice = new unsigned char[w * z];
    for (int i = 0; i < z; i++) {
        for (int j = 0; j < w; j++) {
            xz_slice[i * w + j] = img.getImage(i).data[y * w + j];
        }
    }
    return xz_slice;

}
unsigned char* Get_YZ_slice(Volume& img, int x) {
    int z = img.getImageNumber();
    int w = img.getImage(0).width;
    int h = img.getImage(0).height;
    unsigned char* yz_slice;
    yz_slice = new unsigned char[h * z];
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < z; ++j) {
            yz_slice[i * z + j] = img.getImage(j).data[i * w + x];
        }
    }
    return yz_slice;
}


int main() {

    Volume volume2;
    volume2.addImageFolder("C:/Users/ecm22/source/repos/Colour_corection/Colour_corection/Scans/confuciusornis/"); // add all images in folders

    for (int i = 0; i < 6; i++) {
        Image im = volume2.getImage(i); // get by index
        // check if implemented rightly.
        std::cout << "Image loaded with size " << im.width << " x " << im.height << " with " << im.channels << " channel(s)." << std::endl;
    }

    std::cout << "\n" << volume2.getImageNumber() << "\n";
    unsigned char* xz_slice;
    unsigned char* yz_slice;
    int y = 700;
    int x = 500;
    int w = volume2.getImage(0).width;
    int h = volume2.getImage(0).height;
    int z = volume2.getImageNumber();
    xz_slice = Get_XZ_slice(volume2, y);
    yz_slice = Get_YZ_slice(volume2, x);
    int success_xz = stbi_write_png("C:/Users/ecm22/source/repos/Colour_corection/Colour_corection/Scans/confruc_out/conf_xz_slice.png", w, z, 1, xz_slice, 0);
    int success_yz = stbi_write_png("C:/Users/ecm22/source/repos/Colour_corection/Colour_corection/Scans/confruc_out/conf_yz_slice.png", z, h, 1, yz_slice, 0);
    return 0;
}





