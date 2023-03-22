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
#include "gaussian_blur_3d.h"



void gaussian_blur_3d(unsigned char* data, int w, int h, int d, int c, int kernel_size, float sigma);


// Shortens the amount I need to type below.

// the element type in vectors.
struct Image {
    int width;
    int height;
    int channels;
    unsigned char* data;
};

bool sort_confu(const std::filesystem::path& a, const std::filesystem::path& b) {
    int num_a = std::stoi(a.stem().string().substr(a.stem().string().length() - 4));
    int num_b = std::stoi(b.stem().string().substr(b.stem().string().length() - 4));
    return num_a < num_b;}

void file_sort_confu(std::vector<std::filesystem::path>& file_paths) {
    for (size_t i = 0; i < file_paths.size(); ++i) {
    for (size_t j = 0; j < file_paths.size() - i - 1; ++j) {
        if (!sort_confu(file_paths[j], file_paths[j + 1])) {
            std::swap(file_paths[j], file_paths[j + 1]);
            }
        }
    }
}

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


    void addImageFolder_confu(const char* folderPath) {
        std::vector<std::filesystem::path> file_paths;
        for (const auto& file : std::filesystem::directory_iterator(folderPath)) {
            if (file.path().extension() == ".png") {
                file_paths.push_back(file.path());
            }
        }
        file_sort_confu(file_paths); 
        for (const auto& file_path : file_paths) {
            int w, h, c;
            std::cout << file_path << std::endl; unsigned char* data = stbi_load(file_path.string().c_str(), &w, &h, &c, 0);
            if (!data) {
                std::cerr << "Failed to load image: " << file_path << std::endl;
                continue;
            }
            Image img = { w, h, c, data };
            images.push_back(img);
        }
    }

    int get_size(){
        return images.size();
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







int main(){
    // Define the input and output directories
    std::string input_folder = "/Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Scans/fracture";
    std::string output_folder = "/Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Output/fracture_gaussian_blur/";
    // std::string input_folder = "/Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Scans/confuciusornis";
    // std::string output_folder = "//Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Output/confuciusornis_gaussian_blur/";

    // Create a volume object and add all PNG images in the input directory
    Volume volume;
    // int d=volume.addImageFolder(input_folder.c_str());
    volume.addImageFolder_confu(input_folder.c_str());
    std::cout << "Make volume successfully" << std::endl;

    // Get the dimensions of the volume
    int w = volume.getImage(0).width;
    int h = volume.getImage(0).height;
    int c = volume.getImage(0).channels;
    // int d = volume.getImageBatch(0, 3, 6).size();
    int d = volume.get_size();
    // int d =50;
    // int c = 1;

    // Allocate memory for the volume data
    unsigned char* data = new unsigned char[w * h * d * c];

    // Copy the image data into the volume data
    for (int i = 0; i < d; i++) {
        const Image& img = volume.getImage(i);
        int img_size = img.width * img.height * img.channels;
        std::memcpy(&data[i * img_size], img.data, img_size);
    }
    std::cout << "create data successfully" << std::endl;

    // Apply a 3D Gaussian blur filter to the volume data
    int kernal_size = 9;
    float sigma = 1;
    gaussian_blur_3d(data, w, h, d, c, kernal_size , sigma);

    std::cout << "gaussian_blur successfully" << std::endl;

    // Write the blurred volume as a series of PNG images to the output directory
    for (int i = 0; i < d; i++) {
        std::string filename = output_folder + "output_" + std::to_string(i+1) + ".png";
        stbi_write_png(filename.c_str(), w, h, c, &data[i * w * h * c], 0);
    }

    std::cout << "write images successfully" << std::endl;

    // Free the memory used by the volume data
    delete[] data;

    return 0;
}
