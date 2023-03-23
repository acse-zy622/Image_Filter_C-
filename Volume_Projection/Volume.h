#pragma once
#include "stb_image.h"
#include "stb_image_write.h"
#include "Image.h"


// The Volume class represents a collection of images.
class Volume {
public:
    // Default constructor
    Volume();

    // Selfmade images for testing.
    void addTestImage(Image& im);

    // Adds an image to the Volume by providing the filename.
    void addImage(const char* filename);

    // 1D array for 3d filter computation
    unsigned char* trans_volume(int w, int h, int c, int d);

    // Adds all images from a folder to the Volume by providing the folder path.
    void addImageFolder(const char* folderPath);

    // Retrieves the image at the given index in the Volume.
    const Image& getImage(int i);

    // Returns a constant reference to the list of images in the Volume.
    const std::vector<Image>& getImageList() const;

    // Returns the number of images in the Volume.
    int get_size();

    // Destructor
    ~Volume();

private:
    // A vector holding the images in the Volume.
    std::vector<Image> images;

    // A vector used for internal operations.
    std::vector<Image> v;

    // 1D array for 3d filter computation
    unsigned char data_1;

    // Compares two file paths and returns true if the first should come before the second.
    bool sort_file(const std::filesystem::path& a, const std::filesystem::path& b);

    // Sorts a vector of file paths.
    void file_sort(std::vector<std::filesystem::path>& file_paths);
};
