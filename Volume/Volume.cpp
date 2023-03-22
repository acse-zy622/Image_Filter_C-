#include "Volume.h"
#include <string>


// Constructor for the volume
Volume::Volume() {}

// Add an image to the volume.
void Volume::addImage(const char* filename) {
        int w, h, c;
        unsigned char* data = stbi_load(filename, &w, &h, &c, 0);
        if (!data) {
            std::cerr << "Failed to load image: " << filename << std::endl;
        }
        Image img = { w, h, c, data };
        images.push_back(img);
    }

// Add stack of images to the volume.
void Volume::addImageFolder(const char* folderPath) {
        std::vector<std::filesystem::path> file_paths;

        for (const auto& file : std::filesystem::directory_iterator(folderPath)) {
            if (file.path().extension() == ".png") {
                file_paths.push_back(file.path());
            }
        }
        file_sort(file_paths);

        for (const auto& file_path : file_paths) {
            int w, h, c;
            std::cout << file_path << std::endl;

            unsigned char* data = stbi_load(file_path.string().c_str(), &w, &h, &c, 0);
            if (!data) {
                std::cerr << "Failed to load image: " << file_path << std::endl;
                continue;
            }
            Image img = { w, h, c, data };
            images.push_back(img);
        }
    }

// Get a specific image from the volume
const Volume::Image& Volume::getImage(int i) {   
        if (i >= images.size()) {
            throw std::out_of_range("Image index out of range");
        }
        else {
            return images[i];
        }
    }

// Get a list of images for further use.
const std::vector<Volume::Image>& Volume::getImageList() const {
        return images;
    }

// Adjust get index for 3d filters.
int Volume:: get_size() { 
        return images.size(); }
   
// destructor for the volume.
Volume::~Volume() {
        for (auto& img : images) {
            stbi_image_free(img.data);
        }
    }

bool Volume:: sort_file(const std::filesystem::path& a, const std::filesystem::path& b) {
        int num_a = std::stoi(a.stem().string().substr(a.stem().string().length() - 4));
        int num_b = std::stoi(b.stem().string().substr(b.stem().string().length() - 4));

        return num_a < num_b;
    }

void Volume:: file_sort(std::vector<std::filesystem::path>& file_paths) {
        for (size_t i = 0; i < file_paths.size(); ++i) {
            for (size_t j = 0; j < file_paths.size() - i - 1; ++j) {
                if (!sort_file(file_paths[j], file_paths[j + 1])) {
                    std::swap(file_paths[j], file_paths[j + 1]);
                }
            }
        }
    }




//int main() {
//    
//    Volume volume;
//    volume.addImage("images/dimorphos.png"); // add images one by one
//    
//    Volume volume2;
//    volume2.addImageFolder("scans/fracture"); // add all images in folders
//    
//    //for (int i = 0; i < 6; i++) {
//    //    image im = volume2.getimage(i); // get by index
//
//    //     
//    //    std::cout << "image loaded with size " << im.width << " x " << im.height << " with " << im.channels << " channel(s)." << std::endl;
//    //}
//
//
//    //// print one image size to screen
//    //std::cout << "image loaded with size " << im.width << " x " << im.height << " with " << im.channels << " channel(s)." << std::endl;
//
//
//
//    return 0;
//  }





