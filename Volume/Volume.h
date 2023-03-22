#pragma once
#include <vector>
#include <filesystem>
#include <string>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

class Volume {
public:
    Volume();

    struct Image {
        int width;
        int height;
        int channels;
        unsigned char* data;
    };

    void addImage(const char* filename);
    void addImageFolder(const char* folderPath);
    const Image& getImage(int i);
    const std::vector<Image>& getImageList() const;
    int get_size();
    ~Volume();

private:
    std::vector<Image> images;
    std::vector<Image> v;

    bool sort_file(const std::filesystem::path& a, const std::filesystem::path& b);
    void file_sort(std::vector<std::filesystem::path>& file_paths);
};
