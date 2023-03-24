/**

* @file Volume.h

* @brief Header file for the Volume class.

*

* This file contains the declaration of the Volume class used to apply 3d projections.

*

* Group Members:

* - Hang Zhao (edsml-hz822)

* - Luwen Liang (edsml-ll2822)

* - Elliott Mcquire (acse-ecm22)

* - Zhuoran Yang (acse-zy622)

* - Qingyang Lu (acse-ql1522)

*/

#pragma once
#include "stb_image.h"
#include "stb_image_write.h"
#include "Image.h"


/**

@brief The Volume class represents a collection of images.
*/
class Volume {
public:
    /**

    @brief Default constructor for the Volume class.
    */
    Volume();

    /**

    @brief Adds a self-made image to the Volume for testing purposes.
    @param im The image to add to the Volume.
    */
    void addTestImage(Image& im);

    /**

    @brief Adds an image to the Volume by loading it from a file.
    @param filename The path to the file containing the image.
    */
    void addImage(const char* filename);

    /**

    @brief Generates a 1D array of unsigned char values to represent the Volume for 3D filter computations.
    @param w The width of each image in the Volume.
    @param h The height of each image in the Volume.
    @param c The number of channels in each image in the Volume.
    @param d The number of images in the Volume.
    @return A pointer to the 1D array of unsigned char values.
    */
    unsigned char* trans_volume(int w, int h, int c, int d);

    /**

    @brief Adds all images from a folder to the Volume by loading them from files in numerical order.
    @param folderPath The path to the folder containing the images.
    */
    void addImageFolder(const char* folderPath);

    /**

    @brief Retrieves the image at the given index in the Volume.
    @param i The index of the image to retrieve.
    @return A constant reference to the requested image.
    @throw std::out_of_range if the index is out of range.
    */
    const Image& getImage(int i);

    /**

    @brief Returns a constant reference to the list of images in the Volume.
    @return A constant reference to the vector of images in the Volume.
    */
    const std::vector<Image>& getImageList() const;

    /**

    @brief Returns the number of images in the Volume.
    @return The number of images in the Volume.
    */
    int get_size();

    /**

    @brief Destructor for the Volume class. Frees image memory.
    */
    ~Volume();

private:
    // A vector holding the images in the Volume.
    std::vector<Image> images;

    // A vector used for internal operations.
    std::vector<Image> v;

    // 1D array for 3d filter computation
    /*unsigned char data_1;*/

    /**
    * @brief Compares two file paths based on their numeric values in the last four substrings.
    * @param a The first file path to compare.
    * @param b The second file path to compare.
    * @return true if the first file path should come before the second.
    * @throw std::invalid_argument if either file path is invalid.
    */
    bool sort_file(const std::filesystem::path& a, const std::filesystem::path& b);

    /**
    * @brief Sorts a vector of file paths using the sort_file comparison function.
    * @param file_paths The vector of file paths to sort.
    * @throw std::invalid_argument if any file path is invalid.
    */
    void file_sort(std::vector<std::filesystem::path>& file_paths);
};
