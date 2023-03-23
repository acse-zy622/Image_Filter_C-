#include "Volume.h"


// Default constructor for the Volume class
Volume::Volume() {}

// Adds images for unit testing.
void Volume::addTestImage(Image& im) {
    images.push_back(im);
};

// Adds an image to the Volume by loading it from a file
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

// 1D array for 3d filter computation
unsigned char* Volume::trans_volume(int w, int h, int c, int d) {
    unsigned char* data_1 = new unsigned char[w * h * c * d];
    for (int i = 0; i < d; i++) {
        int img_size = w * h * c;
        std::memcpy(&data_1[i * img_size], images[i].data, img_size);
    }
    return data_1;
}

// Adds a stack of images to the Volume by loading them from a folder with order
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

// Returns a specific image from the Volume by index
const Image& Volume::getImage(int i) {
    if (i >= images.size()) {
        throw std::out_of_range("Image index out of range");
    }
    else {
        return images[i];
    }
}

// Returns a constant reference to the list of images in the Volume
const std::vector<Image>& Volume::getImageList() const {
    return images;
}

// Returns the number of images in the Volume
int Volume::get_size() {
    return images.size();
}

// Destructor for the Volume class, frees image memory
Volume::~Volume() {
    for (auto& img : images) {
        stbi_image_free(img.data);
    }
}

// Compares two file paths based on their numeric values in the last four substrings
// Throw an exception if requirements are not met
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

// Sorts a vector of file paths using the sort_file comparison function
// Catch an exception from sort_file to exit
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



