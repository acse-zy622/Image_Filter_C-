
#include <filesystem>
#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <vector>
#include "median_blur_3d.h"
#include "time.h"
#include "Volume.h"



void median_blur_3d(unsigned char* data, int w, int h, int d, int c, int kernel_size);


int main(){
    clock_t start,end;
    start=clock();
    // Define the input and output directories
    // std::string input_folder = "/Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Scans/fracture";
    // std::string output_folder = "/Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Output/fracture_gaussian_blur/";
    std::string input_folder = "/Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Scans/confuciusornis";
    std::string output_folder = "//Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Output/confuciusornis_median_blur/";

    // Create a volume object and add all PNG images in the input directory
    Volume volume;
    // int d=volume.addImageFolder(input_folder.c_str());
    volume.addImageFolder(input_folder.c_str());
    std::cout << "Make volume successfully" << std::endl;

    // Get the dimensions of the volume
    int w = volume.getImage(0).get_width();
    int h = volume.getImage(0).get_height();
    int c = volume.getImage(0).get_channels();
    int d = volume.get_size();


    // Allocate memory for the volume data
    unsigned char* data = new unsigned char[w * h * d * c];

    // Copy the image data into the volume data
    for (int i = 0; i < d; i++) {
        const Image& img = volume.getImage(i);
        int img_size = img.get_width() * img.get_height() * img.get_channels();
        std::memcpy(&data[i * img_size], img.data, img_size);
    }
    std::cout << "create data successfully" << std::endl;

    // Apply a 3D Gaussian blur filter to the volume data
    int kernal_size = 3;
    median_blur_3d(data, w, h, d, c, kernal_size);

    std::cout << "median_blur successfully" << std::endl;

    // Write the blurred volume as a series of PNG images to the output directory
    for (int i = 0; i < d; i++) {
        std::string filename = output_folder + "output_" + std::to_string(i+1) + ".png";
        stbi_write_png(filename.c_str(), w, h, c, &data[i * w * h * c], 0);
    }

    std::cout << "write images successfully" << std::endl;

    // Free the memory used by the volume data
    delete[] data;
    end=clock();
    std::cout<<"running time"<<(double)(end-start)/CLOCKS_PER_SEC<<std::endl;

    return 0;
}
