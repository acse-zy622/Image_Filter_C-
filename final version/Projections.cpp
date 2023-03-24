/**
* @file Projections.cpp
* @brief This file contains the implementation of the all 3D projections.
* @date 2023-03-24
* @copyright Copyright (c) 2023
* 
* Group Members:
* - Hang Zhao (edsml-hz822)
* - Luwen Liang (edsml-ll2822)
* - Elliott Mcquire (acse-ecm22)
* - Zhuoran Yang (acse-zy622)
* - Qingyang Lu (acse-ql1522)

*/
#include "Projections.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <thread>
#include <tuple>

/**

@brief Constructor for the Projection class, initializing the volume member variable with the provided Volume pointer.

@param volume A pointer to a Volume object.
*/
Projection::Projection(const Volume* volume) : volume(volume) {}

/**

@brief Destructor for the Projection class, which does not have any specific resource deallocation.
*/
Projection::~Projection() {}

/**


@brief Defines the IP method for the Projection class, taking the compare function, output name, and min/max z values as parameters.

@param compare_function A C-style string representing the type of projection operation to perform (max, min, mean, or median).

@param output_name A C-style string representing the name of the output file to save the projection to.

@param min_z An integer representing the minimum z-value of the thin slab to consider.

@param max_z An integer representing the maximum z-value of the thin slab to consider.

@param flag A std::string object that, when set to "test", tests the output against predetermined values rather than saving it to a file.
*/
void Projection::IP(const char* compare_function, const char* output_name, int min_z, int max_z, const std::string& flag) {

    // Retrieve the list of images from the volume
    const auto& vv = volume->getImageList();

    // Check if the input min_z and max_z are valid, and print an error message if they are not
    if (min_z < 0 || max_z > vv.size() || min_z > max_z) {
        std::cerr << "Invalid thin slabs!" << std::endl;
        return;
    }

    // Create a new vector of images within the specified min_z and max_z range
    auto images = std::vector<Image>(vv.begin() + min_z, vv.begin() + max_z);

    // Get the dimensions and channels of the first image in the list
    int width = images[0].get_width();
    int height = images[0].get_height();
    int channels = images[0].get_channels();

    // Check if the compare_function is "max" and perform the MaxIP operation if it is
    if (compare_function == "max") {

        // Check if the images vector is empty, and print an error message if it is
        if (images.empty()) {
            std::cerr << "No images!" << std::endl;
            return;
        }
        else {
            // Initialize the MaxIP_data vector with the same dimensions and channels as the input images
            std::vector<unsigned char> MaxIP_data(width * height * channels);

            // Iterate through all images and compute the maximum using my_max function.
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
            // Check that if MaxIP_data and test1 are equal
            if (flag == "test") {
                unsigned char test1[] = { 4,7,4,3,7,93,23,98,97 };
                bool equal = true;
                for (int i = 0; i < MaxIP_data.size(); i++) {
                    std::cout << static_cast<int>(MaxIP_data[i]) << std::endl;
                }
                for (int i = 0; i < MaxIP_data.size(); i++) {
                    if (static_cast<int>(MaxIP_data[i]) != test1[i]) {
                        equal = false;
                        break;
                    }
                }
                if (equal) {
                    std::cout << "two sets are equal! passed!" << std::endl;
                }
                else {
                    std::cout << "two sets not equal! failed!" << std::endl;
                }
            }
            else {
                // Write the MaxIP_data to the output file, and print an error message if the writing fails
                if (!stbi_write_png(output_name, width, height, channels, MaxIP_data.data(), width * channels)) {
                    std::cerr << "Failed to save! " << std::endl;
                }
            }
        }
    }

    // Check if the compare_function is "min" and perform the MinIP operation if it is
    if (compare_function == "min") {

        // Check if the images vector is empty, and print an error message if it is
        if (images.empty()) {
            std::cerr << "No images found!" << std::endl;
            return;
        }
        else {
            // Initialize the MinIP_data vector with the same dimensions and channels as the input images
            std::vector<unsigned char> MinIP_data(width * height * channels,255);

            // Iterate through all images and compute the minimum using my_min function.
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

            // Check that if MinIP_data and test2 are equal
            if (flag == "test") {
                unsigned char test2[] = { 1,6,0,2,1,2,3,23,12 };
                bool equal = true;
                for (int i = 0; i < MinIP_data.size(); i++) {
                    std::cout << static_cast<int>(MinIP_data[i]) << std::endl;
                }
                for (int i = 0; i < MinIP_data.size(); i++) {
                    if (static_cast<int>(MinIP_data[i]) != test2[i]) {
                        equal = false;
                        break;
                    }
                }
                if (equal) {
                    std::cout << "two sets are equal! passed!" << std::endl;
                }
                else {
                    std::cout << "two sets not equal! failed!" << std::endl;
                }
            }
            else {
                // Write the MaxIP_data to the output file, and print an error message if the writing fails
                if (!stbi_write_png(output_name, width, height, channels, MinIP_data.data(), width * channels)) {
                    std::cerr << "Failed to save! " << std::endl;
                }
            }
        }
    }

    // Check if the compare_function is "mean" and perform the MeanIP operation if it is
    if (compare_function == "mean") {

        // Check if the images vector is empty, and print an error message if it is
        if (images.empty()) {
            std::cerr << "No images!" << std::endl;
            return;
        }

        // Compute the number of images in the images vector
        int num = static_cast<int>(images.size());

        // Initialize the MeanIP_data and sum vectors with the same dimensions and channels as the input images
        std::vector<unsigned char> MeanIP_data(width * height * channels);
        std::vector <double> sum(width * height * channels);

        // Iterate through all images and compute the sum for each pixel using the input images
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

        // Calculate the mean for each pixel and store it in MeanIP_data
        for (int i = 0; i < width * height * channels; i++) {
            MeanIP_data[i] = static_cast<unsigned char>(sum[i] / num);
        }

        // Check that if MeanIP_data and test3 are equal
        if (flag == "test") {
            unsigned char test3[] = { 2,6,2,2,4,33,11,55,50 };
            bool equal = true;
            for (int i = 0; i < MeanIP_data.size(); i++) {
                std::cout << static_cast<int>(MeanIP_data[i]) << std::endl;
            }
            for (int i = 0; i < MeanIP_data.size(); i++) {
                if (static_cast<int>(MeanIP_data[i]) != test3[i]) {
                    equal = false;
                    break;
                }
            }
            if (equal) {
                std::cout << "two sets are equal! passed!" << std::endl;
            }
            else {
                std::cout << "two sets not equal! failed!" << std::endl;
            }
        }
        else {
            // Write the MaxIP_data to the output file, and print an error message if the writing fails
            if (!stbi_write_png(output_name, width, height, channels, MeanIP_data.data(), width * channels)) {
                std::cerr << "Failed to save! " << std::endl;
            }
        }
    }

    // Check if the compare_function is "median" and perform the MedianIP operation if it is
    if (compare_function == "median") {
        if (images.empty()) {
            std::cerr << "No images!" << std::endl;
            return;
        }

        std::vector<unsigned char> MedianIP_data(width * height * channels);

        std::vector<std::tuple<int, int, int>> pixel_locations;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                for (int c = 0; c < channels; c++) {
                    pixel_locations.emplace_back(x, y, c);
                }
            }
        }
        // Multi-thread optimazations for median loops.
        auto process_pixels = [&](size_t start, size_t end) {
            for (size_t i = start; i < end; i++) {
                int x, y, c;
                std::tie(x, y, c) = pixel_locations[i];
                int index = (x + y * width) * channels + c;
                std::vector<unsigned char> val;
                val.reserve(images.size());

                for (const auto& im : images) {
                    val.emplace_back(im.data[index]);
                }

                // Sort the temporary vector to find the median value
                quickSort(val, 0, val.size() - 1);

                // odd and even conditions for median number index
                if (val.size() % 2 == 0) {
                    MedianIP_data[index] = (val[val.size() / 2 - 1] + val[val.size() / 2]) / 2;
                }
                else {
                    MedianIP_data[index] = val[val.size() / 2];
                }
            }
        };

        // get your threads imformation
        size_t num_threads = std::thread::hardware_concurrency();
        size_t pixels_per_thread = pixel_locations.size() / num_threads;

        // Create and store the threads in a vector
        std::vector<std::thread> threads;
        for (size_t i = 0; i < num_threads; i++) {
            size_t start = i * pixels_per_thread;
            size_t end = (i == num_threads - 1) ? pixel_locations.size() : (i + 1) * pixels_per_thread;
            threads.emplace_back(process_pixels, start, end);
        }
        // Join the threads to wait for their completion
        for (auto& t : threads) {
            t.join();
        }

        // Check that if MedianIP_data and test4 are equal
        if (flag == "test") {
            unsigned char test4[] = { 2,7,3,2,5,4,9,45,43 };
            bool equal = true;
            for (int i = 0; i < MedianIP_data.size(); i++) {
                std::cout << static_cast<int>(MedianIP_data[i]) << std::endl;
            }
            for (int i = 0; i < MedianIP_data.size(); i++) {
                if (static_cast<int>(MedianIP_data[i]) != test4[i]) {
                    equal = false;
                    break;
                }
            }
            if (equal) {
                std::cout << "two sets are equal! passed!" << std::endl;
            }
            else {
                std::cout << "two sets not equal! failed!" << std::endl;
            }
        }
        else {
            // Write the MaxIP_data to the output file, and print an error message if the writing fails
            if (!stbi_write_png(output_name, width, height, channels, MedianIP_data.data(), width * channels)) {
                std::cerr << "Failed to save! " << std::endl;
            }
        }
    }

    // Print an error message if the compare_function is not recognized
    if (compare_function != "max" && compare_function != "min" && compare_function != "mean" && compare_function != "median") {
        std::cout << "Unrecognized compare function!" << std::endl;
        return;
    }
}

/**
    * @brief Returns the maximum of two input values.
    * @tparam T The type of input values.
    * @param a The first input value.
    * @param b The second input value.
    * @return The maximum of the two input values.
    */
template<typename T>
T Projection::my_max(const T& a, const T& b) {
    return (a > b) ? a : b;
}

/**
 * @brief Returns the minimum of two input values.
 * @tparam T The type of input values.
 * @param a The first input value.
 * @param b The second input value.
 * @return The minimum of the two input values.
 */
template<typename T>
T Projection::my_min(const T& a, const T& b) {
    return (a < b) ? a : b;
}

/**
 * @brief Partitions the input vector around a pivot for the quick sort algorithm.
 * @param val The input vector to partition.
 * @param l The index of the leftmost element of the vector to partition.
 * @param h The index of the rightmost element of the vector to partition.
 * @return The index of the pivot element.
 */
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

/**
   * @brief Sorts the input vector with unsigned char using the quick sort algorithm.
   * @param val The input vector to sort.
   * @param l The index of the leftmost element of the vector to sort.
   * @param h The index of the rightmost element of the vector to sort.
   */
void Projection::quickSort(std::vector<unsigned char>& val, int l, int h) {
    if (l < h) {
        int piv = separation(val, l, h);
        quickSort(val, l, piv - 1);
        quickSort(val, piv + 1, h);
    }
}

