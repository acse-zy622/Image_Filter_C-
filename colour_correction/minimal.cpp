// A minimal example file showing how to include the stb image headers,
// and how to read and write image files using these headers.
//
// Compilation with: g++-12 minimal.cpp -o minimal
//
// Written by T.M. Davison (2023)

#include "filter.h"
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

    int bright = 128;
    int filter_key;

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

    user_funcs.UserPathRequest();
    user_funcs.UserSavePath();

    // Initialise the Object
    Filter<int> black_white(user_funcs.img_path.c_str(), user_funcs.save_path.c_str());
    Edge<int> edge_detect(black_white.corrected_img, black_white.width, black_white.height, black_white.channels, black_white.save_path);


    unordered_map<int, std::function<void()>> overview = {
    {11, [&]() { black_white.ApplyGrayScale(); }},
    {12, [&]() { black_white.AutoColourBalance(); }},
    {30, [&]() { edge_detect.Sobel(); }},
    };

    if (overview.find(filter_key) != overview.end()) {
        overview[filter_key]();  // Call the method
    }
    else {
        cout << "Oh No - Thats not a proper key";
    }

    // need a way to handle these (ideally needs to be a shared member)
    //black_white.SaveImg();
    edge_detect.SaveImg();
    ////black_white.AutoColourBalance();
    //black_white.ApplyGrayScale();


    //cout << "this is my gray channels: " << black_white.gray_channels << endl;
    //cout << "this is my normal channels: " << black_white.channels << endl;
    //Edge<int> edge_detect(black_white.corrected_img, black_white.width, black_white.height, black_white.channels, black_white.save_path);
    //edge_detect.Sobel();
    //

    ////black_white.Brightness(bright, false, true);
    ////black_white.SaveImg();
    //edge_detect.SaveImg();

    return 0;
}
