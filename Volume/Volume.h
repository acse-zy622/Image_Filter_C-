#pragma once
#include <vector>
#include <filesystem>
#include <string>
#include <iostream>
#include "stb_image.h"
#include "stb_image_write.h"
#include "Image.h"


class Volume {
public:
    Volume();

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
