// A minimal example file showing how to include the stb image headers,
// and how to read and write image files using these headers.
//
// Compilation with: g++-12 minimal.cpp -o minimal
//
// Written by T.M. Davison (2023)

#include "filter.h"
#include "UserInput.h"
#include "3d_ops-1.h"
#include "Projections.h"
#include <iostream>
#include <string>
#include <functional>
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"
using namespace std;

int main() {

    //user stored variables
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

    // Recieve the image path and save path from the user

    // set the object using this info
    // Do I still need these

    //Build the object (specifying the save path)
    


    if (filter_key > 20 && filter_key < 50) {
        cout << "\nPlease specify the kernel size: ";
        cin >> kernel_size;
        cout << "\nPlease specify the sigma: ";
        cin >> sigma;

    }
    else {
        kernel_size = 0;
        sigma = 0;
    }

    // Initialisation for 2D filters
    if (filter_key < 30) {

        user_funcs.UserPathRequest();
        user_funcs.UserSavePath();
        // If only one image user can specify path
        Image image(user_funcs.img_path.c_str());
        Filter black_white(image, kernel_size, sigma);
        unordered_map<int, std::function<void()>> overview = {
                        {11, [&]() { black_white.ApplyGrayScale(); }},
                        {12, [&]() { black_white.AutoColourBalance(); }},
                        {21, [&]() { black_white.box_blur(); }},
                        {22, [&]() { black_white.gaussian_blur(); }},
                        {23, [&]() { black_white.median_blur(); }},
                        {31, [&]() { black_white.gaussian_blur(); }},
                        {32, [&]() { black_white.gaussian_blur(); }}, };

        if (overview.find(filter_key) != overview.end()) {

            overview[filter_key]();  // Call the method

            black_white.SaveImg(user_funcs.save_path.c_str());
        }

        // setting user brightness
        else if (filter_key == 13) {
            bright = user_funcs.BrightnessRequest();
            black_white.Brightness(bright);
            black_white.SaveImg(user_funcs.save_path.c_str());
        }
    }
    // 3D blurs and Slicing
    else if (filter_key > 40 && filter_key < 60) {

        ThreeDee slice;
        Volume* volume2 = new Volume();

        user_funcs.FolderPathRequest();
        user_funcs.SaveFolderPath();

        volume2->addImageFolder(user_funcs.folder_path.c_str());
        Image image = volume2->getImage(0);
        int depth = volume2->get_size();
        std::cout << "this is depth:" << depth;
        int w = image.get_width();
        int h = image.get_height();

        unsigned char* data = volume2->trans_volume(w, h, 1, depth);
        //cout << "Depth after conversion: " << volume2->get_size() << endl;
        depth = volume2->get_size();
        Image trans_img(data, w, h, 1);

        // Our error is here
        cout << "Kernel Size: " << kernel_size << endl;
        cout << "Sigma Size: " << sigma << endl;
        Filter black_white(trans_img, kernel_size, sigma, depth);

        unordered_map<int, std::function<void()>> overview_3d = {
                        {41, [&]() { black_white.median_blur_3d(); }},
                        {42, [&]() { black_white.gaussian_blur_3d(); }}, };

        cout << "Here -4" << endl;

        if (overview_3d.find(filter_key) != overview_3d.end()) {
            cout << "Am I getting past this stupid if statement" << endl;
            overview_3d[filter_key]();  // Call the method
            cout << "Here -5" << endl;
           // unsigned char* corrected_img = black_white.get_corrected_img();
            black_white.SaveImgFolder(user_funcs.save_folder_path.c_str());
        }
        else {

            user_funcs.xyChoice();
            if (user_funcs.choice == 'x') {
                int y = user_funcs.XSlice_dim(w);
                std::cout << y << endl;
                unsigned char* xz_slice;
                xz_slice = slice.Get_XZ_slice(volume2, y);
                std::cout << "Please specify the path to the XZ Slice" << std::endl;
                user_funcs.UserSavePathForSlice();
                std::string full_save_path = user_funcs.save_folder_path + user_funcs.slice_filename;
                cout << full_save_path << endl;
                stbi_write_png(full_save_path.c_str(), w, depth, 1, xz_slice, 0);
            }
            else if (user_funcs.choice == 'y') {
                int x = user_funcs.YSlice_dim(h);
                unsigned char* yz_slice;
                yz_slice = slice.Get_YZ_slice(volume2, x);
                std::cout << "Please specify the path to the YZ Slice" << std::endl;
                user_funcs.UserSavePathForSlice();
                std::string full_save_path = user_funcs.save_folder_path + user_funcs.slice_filename;
                cout << full_save_path << endl;
                stbi_write_png(full_save_path.c_str(), depth, h, 1, yz_slice, 0);
            }
            else {
                int y = user_funcs.XSlice_dim(w);
                int x = user_funcs.YSlice_dim(h);
                unsigned char* xz_slice;
                unsigned char* yz_slice;
                xz_slice = slice.Get_XZ_slice(volume2, y);
                yz_slice = slice.Get_YZ_slice(volume2, x);

                std::cout << "Please specify the path to the XZ Slice" << std::endl;
                user_funcs.UserSavePathForSlice();
                std::string full_save_path_xz = user_funcs.save_folder_path + user_funcs.slice_filename;
                stbi_write_png(full_save_path_xz.c_str(), w, depth, 1, xz_slice, 0);

                std::cout << "Please specify the path to the YZ Slice" << std::endl;
                user_funcs.UserSavePathForSlice();
                std::string full_save_path_yz = user_funcs.save_folder_path + user_funcs.slice_filename;
                stbi_write_png(full_save_path_yz.c_str(), depth, h, 1, yz_slice, 0);

            }
            
           
            
        }

    }
    else if (filter_key > 60) {

        Volume* volume2 = new Volume();
        user_funcs.FolderPathRequest();
        

        volume2->addImageFolder(user_funcs.folder_path.c_str());
        int depth = volume2->get_size();
        /*Image image = volume2->getImage(0);
        int depth = volume2->get_size();
        std::cout << "this is depth:" << depth;
        int w = image.get_width();
        int h = image.get_height();*/

        user_funcs.UserSavePath();

        Projection proj(volume2);

        unordered_map<int, const char*> overview_proj = { {61, "max"}, {62, "min"}, {63, "mean"}, {64, "median"} };
        
        if (overview_proj.find(filter_key) != overview_proj.end()) {
            cout << overview_proj[filter_key] << endl;
            proj.IP("mean", user_funcs.save_path.c_str(), 0, depth, "test");
            //proj.IP(overview_proj[filter_key].c_str(), user_funcs.save_path.c_str(), 0, depth, "test");
            std::cout << "Finished" << std::endl;
        }

    }


    // map for 2D Filters
    


    

    return 0;
};
