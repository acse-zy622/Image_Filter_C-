/**

* @file Projections.h

* @brief declaration of the Projection class.

*

* This file contains the declaration of all the 3D projections.

*

* Group Members:

* - Hang Zhao (edsml-hz822)

* - Luwen Liang (edsml-ll2822)

* - Elliott Mcquire (acse-ecm22)

* - Zhuoran Yang (acse-zy622)

* - Qingyang Lu (acse-ql1522)

*/
#pragma once
#include "Volume.h"


/**

@class Projection

@brief The Projection class represents the process of creating projections from a Volume of images.
*/
class Projection {
public:
    /**

    @brief Constructor that takes a pointer to a Volume object.
    @param volume A pointer to the Volume object containing the images for the projection.
    */
    Projection(const Volume* volume);

    /**

    @brief Destructor for the Projection class.
    */
    ~Projection();

    /**

    @brief Creates an intensity projection of the Volume using the specified compare function, output filename,
    and the range of images to be considered in the projection (min_z and max_z).
    @param compare_function The name of the function to use for intensity comparison (either "max" or "min").
    @param output_name The filename to use for the output projection image.
    @param min_z The index of the first image to be considered in the projection.
    @param max_z The index of the last image to be considered in the projection.
    @param flag A string flag indicating the direction of the projection (either "xy" or "xz").
    */
    void IP(const char* compare_function, const char* output_name, int min_z, int max_z, const std::string& flag);

private:
    /**
    * @brief A pointer to the Volume object containing the images for the projection.
    */
    const Volume* volume;

    /**
    * @brief A template function that returns the maximum of two values.
    * @tparam T The type of values to compare.
    * @param a The first value to compare.
    * @param b The second value to compare.
    * @return The maximum value of a and b.
    */
    template<typename T>
    T my_max(const T& a, const T& b);

    /**
    * @brief A template function that returns the minimum of two values.
    * @tparam T The type of values to compare.
    * @param a The first value to compare.
    * @param b The second value to compare.
    * @return The minimum value of a and b.
    */
    template<typename T>
    T my_min(const T& a, const T& b);

    /**
    * @brief A helper function that finds the separation point for the quicksort algorithm.
    * @param val A vector of unsigned char values to sort.
    * @param l The index of the first element in the vector to consider.
    * @param h The index of the last element in the vector to consider.
    * @return The index of the separation point.
    */
    int separation(std::vector<unsigned char>& val, int l, int h);

    /**
    * @brief A helper function that performs quicksort on a vector of unsigned char values.
    * @param val A vector of unsigned char values to sort.
    * @param l The index of the first element in the vector to consider.
    * @param h The index of the last element in the vector to consider.
    */
    void quickSort(std::vector<unsigned char>& val, int l, int h);
};
