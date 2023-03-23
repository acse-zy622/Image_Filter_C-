#pragma once
#include "Volume.h"


// The Projection class represents the process of creating projections from a Volume of images.
class Projection {
public:
    // Constructor that takes a pointer to a Volume object.
    Projection(const Volume* volume);

    // Destructor for the Projection class.
    ~Projection();

    // Creates an intensity projection of the Volume using the specified compare function, output filename,
    // and the range of images to be considered in the projection (min_z and max_z).
    void IP(const char* compare_function, const char* output_name, int min_z, int max_z, const std::string& flag);

private:
    // A pointer to the Volume object containing the images for the projection.
    const Volume* volume;

    // A template function that returns the maximum of two values.
    template<typename T>
    T my_max(const T& a, const T& b);

    // A template function that returns the minimum of two values.
    template<typename T>
    T my_min(const T& a, const T& b);

    // A helper function that finds the separation point for the quicksort algorithm.
    int separation(std::vector<unsigned char>& val, int l, int h);

    // A helper function that performs quicksort on a vector of unsigned char values.
    void quickSort(std::vector<unsigned char>& val, int l, int h);
};
