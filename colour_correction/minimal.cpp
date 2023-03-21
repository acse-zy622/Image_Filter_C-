// A minimal example file showing how to include the stb image headers,
// and how to read and write image files using these headers.
//
// Compilation with: g++-12 minimal.cpp -o minimal
//
// Written by T.M. Davison (2023)

#include "filter.h"
#include "Blur.h"
#include "Edge_Detect.h"
#include "UserInput.h"
#include <iostream>
#include <string>
#include <functional>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
using namespace std;

int main() {

    int bright;
    int filter_key;
    int kernel_size = 0;
    float sigma = 0;

    // UserInterface Options
    char quick;
    UserInput user_funcs;
    
    cout << "Are you familiar with this programme? if so select 'y' for QuickMenu: ";
    cin >> quick;
    if (quick == 'y') {
       filter_key = user_funcs.QuickMenu();
    }
    else {
       filter_key = user_funcs.FilterMenu();
    }

    //setting user variables for blur
    if (filter_key > 20 && filter_key < 30) {
        cout << "\nPlease specify the kernel size: ";
        cin >> kernel_size;
        cout << "\nPlease specify the sigma: ";
        cin >> sigma;
    }


    user_funcs.UserPathRequest();
    user_funcs.UserSavePath();

    // Initialise the Object
    Filter<int> black_white(user_funcs.img_path.c_str(), user_funcs.save_path.c_str());
    Blur<int> blur_img(user_funcs.img_path.c_str(), user_funcs.save_path.c_str(), kernel_size, sigma);
    //Edge<int> edge_detect(black_white.corrected_img, black_white.width, black_white.height, black_white.channels, black_white.save_path);


    // map for Edge
    unordered_map<int, std::function<void()>> overview = {
    {11, [&]() { black_white.ApplyGrayScale(); }},
    {12, [&]() { black_white.AutoColourBalance(); }},
    {21, [&]() { blur_img.box_blur(); }},
    {22, [&]() { blur_img.gaussian_blur(); }},
    {23, [&]() { blur_img.median_blur(); }} };

    // Calling the Filter key for colour and Blur class
    if (overview.find(filter_key) != overview.end()) {
        
        overview[filter_key]();  // Call the method

        if (filter_key < 20) {
            black_white.SaveImg();
        }
        else if (filter_key > 20 && filter_key < 30) {
            blur_img.SaveImg();
        }

    }
    // setting user brightness
    else if (filter_key == 13) {
        bright = user_funcs.BrightnessRequest();
        black_white.Brightness(bright);
        black_white.SaveImg();
    }
    else {
        black_white.ApplyGrayScale();
        Edge<int> edge_detect(black_white.corrected_img, black_white.width, black_white.height, black_white.channels, black_white.save_path);

        unordered_map<int, std::function<void()>> edge_overview = {{31, [&]() { edge_detect.Sobel(); }},
                                                                   {32, [&]() { edge_detect.prewitt_edge_detect(); }} };

        edge_overview[filter_key]();
        edge_detect.SaveImg();
    }
    

    return 0;
}
