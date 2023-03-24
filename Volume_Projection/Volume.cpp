/**

* @file Volume.cpp

* @brief Implementation of the Volume class.

*

* This file contains the implementation of Volume class.

*

* Group Members:

* - Hang Zhao (edsml-hz822)

* - Luwen Liang (edsml-ll2822)

* - Elliott Mcquire (acse-ecm22)

* - Zhuoran Yang (acse-zy622)

* - Qingyang Lu (acse-ql1522)

*/
#include "Volume.h"


/**

Default constructor for the Volume class.
*/
Volume::Volume() {}

/**

Adds an image for unit testing.
@param[in] im The Image object to add.
*/
void Volume::addTestImage(Image& im) {
    images.push_back(im);
};

/**

Adds an image to the Volume by loading it from a file.
@param[in] filename The file path of the image.
*/
void Volume::addImage(const char* filename) {
    int w, h, c;
    unsigned char* data = stbi_load(filename, &w, &h, &c, 0);
    if (!data) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return;
    }
    Image img(data, w, h, c);
    images.push_back(img); 
}

/**

Returns a 1D array of image data for 3D filter computation.
@param[in] w The width of the images in the Volume.
@param[in] h The height of the images in the Volume.
@param[in] c The number of channels in the images in the Volume.
@param[in] d The depth of the Volume.
@return A pointer to the 1D array of image data.
*/
unsigned char* Volume::trans_volume(int w, int h, int c, int d) {
    unsigned char* data_1 = new unsigned char[w * h * c * d];
    for (int i = 0; i < d; i++) {
        int img_size = w * h * c;
        std::memcpy(&data_1[i * img_size], images[i].data, img_size);
    }
    return data_1;
}

/**

Adds a stack of images to the Volume by loading them from a folder with order.

@param[in] folderPath The file path of the folder containing the images.
*/
void Volume::addImageFolder(const char* folderPath) {
    std::vector<std::filesystem::path> file_paths;

    // Iterate through the folder and collect file paths of .png files
    for (const auto& file : std::filesystem::directory_iterator(folderPath)) {
        if (file.path().extension() == ".png") {
            file_paths.push_back(file.path());
        }
    }
    // Sort the file paths in numerical orders
    file_sort(file_paths);

    // Load and add images to the Volume
    for (const auto& file_path : file_paths) {
        int w, h, c;
        std::cout << file_path << std::endl;

        unsigned char* data = stbi_load(file_path.string().c_str(), &w, &h, &c, 0);
        if (!data) {
            std::cerr << "Failed to load image: " << file_path << std::endl;
            continue;
        }
        Image img(data, w, h, c);
        images.push_back(img);
    }
}

/**

Returns a specific image from the Volume by index.
@param[in] i The index of the image to return.
@return A constant reference to the Image object.
@throws std::out_of_range If the index is out of range.
*/
const Image& Volume::getImage(int i) {
    if (i >= images.size()) {
        throw std::out_of_range("Image index out of range");
    }
    else {
        return images[i];
    }
}

/**

@brief Returns a constant reference to the list of images in the Volume.
@return A constant reference to the list of images in the Volume
*/
const std::vector<Image>& Volume::getImageList() const {
    return images;
}

/**

@brief Returns the number of images in the Volume.
@return The number of images in the Volume
*/
int Volume::get_size() {
    return images.size();
}

/**

@brief Destructor for the Volume class, frees image memory.
*/
Volume::~Volume() {
    for (auto& img : images) {
        stbi_image_free(img.data);
    }
}

/**
* @brief Compares two file paths based on their numeric values in the last four substrings.
* @param[in] a The first file path to compare
* @param[in] b The second file path to compare
* @return true if the numeric value of a is less than that of b, false otherwise
* @throw std::invalid_argument if the last four substrings of either file path do not contain digits
*/
bool Volume::sort_file(const std::filesystem::path& a, const std::filesystem::path& b) {
    std::string a_st = a.stem().string();
    std::string b_st = b.stem().string();

    if (a_st.length() < 4 || !std::isdigit(a_st[a_st.length() - 4]) ||
        b_st.length() < 4 || !std::isdigit(b_st[b_st.length() - 4])) {
        throw std::invalid_argument("Invalid path!");
    }

    int a_ = std::stoi(a_st.substr(a_st.length() - 4));
    int b_ = std::stoi(b_st.substr(b_st.length() - 4));

    return a_ < b_;
}


/**
 * @brief Sorts a vector of file paths using the sort_file comparison function.
 * @param[in,out] file_paths The vector of file paths to sort
 * @throw std::invalid_argument if the sort_file function throws an exception
 */
void Volume::file_sort(std::vector<std::filesystem::path>& file_paths) {
    try {
        for (size_t i = 0; i < file_paths.size(); ++i) {
            for (size_t j = 0; j < file_paths.size() - i - 1; ++j) {
                if (!sort_file(file_paths[j], file_paths[j + 1])) {
                    std::swap(file_paths[j], file_paths[j + 1]);
                }
            }
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        std::exit(1);
    }
}



