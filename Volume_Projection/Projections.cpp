#include "Projections.h"
#include "stb_image.h"
#include "stb_image_write.h"


// Constructor for the `Projection` class, initializing the `volume` member variable with the provided `Volume` pointer.
Projection::Projection(const Volume* volume) : volume(volume) {}

// Destructor for the `Projection` class, which does not have any specific resource deallocation.
Projection::~Projection() {}

// Defines the `IP` method for the `Projection` class, taking the compare function, output name, and min/max z values as parameters.
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

            if (flag == "test") {
                for (int i = 0; i < MaxIP_data.size(); i++) {
                    std::cout << static_cast<int>(MaxIP_data[i]) << std::endl;
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

            
            if (flag == "test") {
                for (int i = 0; i < MinIP_data.size(); i++) {
                    std::cout << static_cast<int>(MinIP_data[i]) << std::endl;
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

        if (flag == "test") {

            for (int i = 0; i < MeanIP_data.size(); i++) {
                std::cout << static_cast<double>(MeanIP_data[i]) << std::endl;
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

        // Check if the images vector is empty, and print an error message if it is
        if (images.empty()) {
            std::cerr << "No images!" << std::endl;
            return;
        }

        // Initialize the MedianIP_data vector with the same dimensions and channels as the input images
        std::vector<unsigned char> MedianIP_data(width * height * channels);

        // Iterate through all pixels and channels, and compute the median value for each pixel
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                for (int c = 0; c < channels; c++) {
                    int index = (x + y * width) * channels + c;
                    std::cout << "Processing x: " << x << ", y: " << y << ", c: " << c << ", index: " << index << std::endl;
                    // Create a temporary vector to store the pixel values for each image
                    std::vector<unsigned char> val;
                    val.reserve(images.size());

                    // Populate the temporary vector with the pixel values from all input images
                    for (const auto& im4 : images) {
                        val.emplace_back(im4.data[index]);
                    }

                    // Sort the temporary vector to find the median value
                    quickSort(val, 0, val.size() - 1);

                    // odd and even conditions for median number index
                    if (val.size() % 2 == 0) {
                        MedianIP_data[index] = (val[val.size()/ 2 - 1] + val[val.size() / 2]) / 2;
                    }
                    else {
                        MedianIP_data[index] = val[val.size() / 2];
                    }
                }
            }
        }

        if (flag == "test") {
            for (int i = 0; i < MedianIP_data.size(); i++) {
                std::cout << static_cast<double>(MedianIP_data[i]) << std::endl;
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

// Define the my_max function template to return the maximum of two input values
template<typename T>
T Projection::my_max(const T& a, const T& b) {
    return (a > b) ? a : b;
}

// Define the my_min function template to return the minimum of two input values
template<typename T>
T Projection::my_min(const T& a, const T& b) {
    return (a < b) ? a : b;
}

// Define the separation function to partition the input vector around a pivot for the quick sort algorithm
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

// Define the quickSort function to sort the input vector with unsigned char using the quick sort algorithm
void Projection::quickSort(std::vector<unsigned char>& val, int l, int h) {
    if (l < h) {
        int piv = separation(val, l, h);
        quickSort(val, l, piv - 1);
        quickSort(val, piv + 1, h);
    }
}

