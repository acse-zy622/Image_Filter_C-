// A minimal example file showing how to include the stb image headers,
// and how to read and write image files using these headers.
//
// Compilation with: g++-12 minimal.cpp -o minimal
//
// Written by T.M. Davison (2023)

#include "filter.h"
#include "UserInput.h"
#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
using namespace std;

int main() {

    int bright = 160;
    //int w, h, c;
    //unsigned char* data;

    //// Read in image file
    //data = stbi_load("gracehopper.png", &w, &h, &c, 0);
    // I have left this part as the input because The user should be able to change the image size if they want
    
    UserInput user_funcs;
    
    user_funcs.UserPathRequest();
    user_funcs.UserSavePath();
    Filter<int> black_white(user_funcs.img_path.c_str(), user_funcs.save_path.c_str());
    //black_white.AutoColourBalance();
    //black_white.ApplyGrayScale();
   
    black_white.Brightness(bright, false, true);
    black_white.SaveImg();

    return 0;
}


//int main() {
//
//    int w, h, c;
//    unsigned char* data;
//
//    // Read in image file
//    data = stbi_load("gracehopper.png", &w, &h, &c, 0);
//
//    // I think at this point would be a good idea to implement the class
//
//    // Print image size to screen
//    std::cout << "Image loaded with size " << w << " x " << h << " with " << c << " channel(s)." << std::endl;
//    std::cout << "Channels(s). " << c << std::endl;
//
//    size_t img_size = w * h * c;
//    cout << img_size << endl;
//
//    // This will handle the alpha transp
//    int gray_channels;
//    if (c == 4) {
//        gray_channels = 2;
//    }
//    else {
//        gray_channels = 1;
//    }
//
//    size_t gray_img_size = w * h * gray_channels;
//    unsigned char* gray_img = new unsigned char[gray_img_size];
//
//    // set initial loop conditions:
//    // set a pointer of the same type to the first element of data (input pixel - coloured image)
//    // set a pointer of the same type to the first element of gray image output
//
//    // set conditions:
//    // input_pixel != data + img_size -  data is a pointer to the first element the data array (so adding img_size gives us the final byte of memory - last value)
//
//    // Incrementers:
//    // Each pixel contains (R, G, B) so we have to make a step of 3 (if jpg) or 4 (if png)
//    // We also step for the output so C can be 1 or 2.
//
//    for (unsigned char* input_pixel = data, *output_pixel = gray_img; input_pixel != data + img_size; input_pixel += c, output_pixel += gray_channels)
//    {
//        // calculate the average of each RGB value within the pixel) - thats why input_pixel(+0) + (inputpixel + 1) etc...
//        // cast this to unsigned 8 bit integer
//        // this ensures pixel value is represeneted by exactly one byte (standard)
//        *output_pixel = static_cast<uint8_t>((*input_pixel + *(input_pixel + 1) + *(input_pixel + 2)) / 3.0);
//        // This will store the alpha channel in the second channel of the grayscale image
//        if (c == 4) {
//            *(output_pixel + 1) = *(input_pixel + 3);
//        }
//    }
//
//    // Save image to new filename
//    int success = stbi_write_png("gracehopper_test.png", w, h, gray_channels, gray_img, 0);
//
//    // Deallocate memory
//    stbi_image_free(data);
//
//    return 0;
//}