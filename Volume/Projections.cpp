#include "Projections.h"
#include "stb_image.h"
#include "stb_image_write.h"


Projection::Projection(const Volume* volume) : volume(volume){}

Projection::~Projection() {}

void Projection :: IP(const char* compare_function, const char* output_name, int min_z, int max_z) {

        const auto& vv = volume->getImageList();
        if (min_z < 0 || max_z > vv.size() || min_z > max_z) {
            std::cerr << "Invalid thin slabs!" << std::endl;
        }
        auto images = std::vector<Image>(vv.begin() + min_z, vv.begin() + max_z );


        int width = images[0].get_width();
        int height = images[0].get_height();
        int channels = images[0].get_channels();

        // use mymax function for MaxIP
        if (compare_function == "max") {

            if (images.empty()) {
                std::cerr << "No images!" << std::endl;
            }
            else {
                // Initialize MIP image with the same dimensions and channels since ct-scans are all in the same dims.

                std::vector<unsigned char> MaxIP_data(width * height * channels);

                // Iterate through all images and compute the maximum using mymax function.
                for (const auto& im : images) {
                    for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                            for (int c = 0; c < channels; c++) {
                                int index = (x + y * width) * channels + c;
                                MaxIP_data[index] = my_max(MaxIP_data[index], im.data[index]);
                            }
                        }
                    }
                }
                if (!stbi_write_png(output_name, width, height, channels, MaxIP_data.data(), width * channels)) {
                    std::cerr << "Failed to save! " << std::endl;
                }
            }
        }

        if (compare_function == "min") {

            if (images.empty()) {
                std::cerr << "No images found!" << std::endl;
            }
            else {

                std::vector<unsigned char> MinIP_data(width * height * channels);


                for (const auto& im2 : images) {
                    for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                            for (int c = 0; c < channels; c++) {
                                int index = (x + y * width) * channels + c;
                                MinIP_data[index] = my_min(MinIP_data[index], im2.data[index]);
                            }
                        }
                    }
                }
                if (!stbi_write_png(output_name, width, height, channels, MinIP_data.data(), width * channels)) {
                    std::cerr << "Failed to save! " << std::endl;
                }
            }
        }

        if (compare_function == "mean") {

            if (images.empty()) {
                std::cerr << "No images!" << std::endl;
                return;
            }
            int num = static_cast<int>(images.size());


            std::vector<unsigned char> MeanIP_data(width * height * channels);
            std::vector <double> sum(width * height * channels);

            for (const auto& im3 : images) {
                for (int y = 0; y < height; y++) {
                    for (int x = 0; x < width; x++) {
                        for (int c = 0; c < channels; c++) {
                            int index = (x + y * width) * channels + c;
                            sum[index] += static_cast<double>(im3.data[index]);
                        }
                    }
                }
            }

            for (int i = 0; i < width * height * channels; i++) {
                MeanIP_data[i] = static_cast<unsigned char>(sum[i] / num);
            }

            if (!stbi_write_png(output_name, width, height, channels, MeanIP_data.data(), width * channels)) {
                std::cerr << "Failed to save! " << std::endl;
            }
        }

        if (compare_function == "median") {

            
            if (images.empty()) {
                std::cerr << "No images!" << std::endl;
                return;
            }

            std::vector<unsigned char> MedianIP_data(width * height * channels);

            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    for (int c = 0; c < channels; c++) {
                        int index = (x + y * width) * channels + c;
                        std::cout << "Processing x: " << x << ", y: " << y << ", c: " << c << ", index: " << index << std::endl;
                        std::vector<unsigned char> val;
                        val.reserve(images.size());

                        for (const auto& im4 : images) {
                            val.emplace_back(im4.data[index]);
                        }
                        quickSort(val, 0, val.size() - 1);
                        MedianIP_data[index] = val[val.size() / 2];
                    }
                }
            }
            if (!stbi_write_png(output_name, width, height, channels, MedianIP_data.data(), width * channels)) {
                std::cerr << "Failed to save! " << std::endl;
            }

        }

        if (compare_function != "max" && compare_function != "min" && compare_function != "mean" && compare_function != "median") {
            std::cout << "Unrecognized compare function!" << std::endl;
        }
    }

template<typename T>
T Projection::my_max(const T& a, const T& b) {
        return (a > b) ? a : b;
    }

template<typename T>
T Projection::my_min(const T& a, const T& b) {
        return (a < b) ? a : b;
    }

int Projection::separation(std::vector<unsigned char>& val, int l, int h) {
        unsigned char piv = val[h];
        int i = l - 1;
        for (int j = l; j <= h - 1; j++) {
            if (val[j] <= piv) {
                i++;
                std::swap(val[i], val[j]);
            }
        }
        std::swap(val[i + 1], val[h]);
        return (i + 1);
    }

void Projection::quickSort(std::vector<unsigned char>& val, int l, int h) {
        if (l < h) {
            int piv = separation(val, l, h);
            quickSort(val, l, piv - 1);
            quickSort(val, piv + 1, h);
        }
    }

