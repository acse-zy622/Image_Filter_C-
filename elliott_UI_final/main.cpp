/**
 * @file main.cpp
 * @author Group Members:
 * - Hang Zhao (edsml-hz822)
 * - Luwen Liang (edsml-ll2822)
 * - Elliott Mcquire (acse-ecm22)
 * - Zhuoran Yang (acse-zy622)
 * - Qingyang Lu (acse-ql1522)
 * @brief A minimal example file showing how to use classes in this project
 * @date 2023-03-24
 * @copyright Copyright (c) 2023
 *
 */
#include "filter.h"
#include "UserInput.h"
#include "3d_ops-1.h"
#include "Projections.h"
#include <iostream>
#include <string>
#include <functional>

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
    
    // Prompt for choice of menu - The user can choose between a quick (returning user) menu
    // Or a "step by step" Menu
    cout << "Are you familiar with this programme? if so select 'y' for QuickMenu: ";
    cin >> quick;
    if (quick == 'y') {
       filter_key = user_funcs.QuickMenu();
    }
    else {
       filter_key = user_funcs.FilterMenu();
    }

    // Based on filter key the user will need to specify k_size and Sigma
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
    if (filter_key < 40) {

        // Methods for taking in user_paths and save_paths
        user_funcs.UserPathRequest();
        user_funcs.UserSavePath();

        // initalise the an Image object using the specified single image
        Image image(user_funcs.img_path.c_str());
        // Initialise the Filter object
        Filter black_white(image, kernel_size, sigma);
        // Map store for the 2d functions
        unordered_map<int, std::function<void()>> overview = {
                        {11, [&]() { black_white.ApplyGrayScale(); }},
                        {12, [&]() { black_white.AutoColourBalance(); }},
                        {21, [&]() { black_white.box_blur(); }},
                        {22, [&]() { black_white.gaussian_blur(); }},
                        {23, [&]() { black_white.median_blur(); }},};

        // Checking if key exists within the map
        if (overview.find(filter_key) != overview.end() && filter_key < 30) {

            // Execute the chosen method
            overview[filter_key]();  // Call the method

            // Save the resulting image in the user specified save path
            black_white.SaveImg(user_funcs.save_path.c_str());
        }

        // setting user brightness
        else if (filter_key == 13) {
            bright = user_funcs.BrightnessRequest();
            black_white.Brightness(bright);
            black_white.SaveImg(user_funcs.save_path.c_str());
        }
        else {

            overview[11]();
            black_white.SaveImg(user_funcs.save_path.c_str());

            Image image_1(user_funcs.save_path.c_str());

            Filter edge(image_1, kernel_size, sigma);

            unordered_map<int, std::function<void()>> overview_edge = {
                        {31, [&]() { edge.Sobel(); }},
                        {32, [&]() { edge.Prewitt(); }}, };

            std::cout << " I have applied grayscale";
            if (overview_edge.find(filter_key) != overview_edge.end()) {
                std::cout << filter_key << std::endl;
                // Execute the chosen method
                overview_edge[filter_key]();  // Call the method

                // Save the resulting image in the user specified save path
                edge.SaveImg(user_funcs.save_path.c_str());
            }
        }
    }
    // 3D blurs and Slicing - check if filter key is between the categorical range
    else if (filter_key > 40 && filter_key < 60) {

        // Initialise slice class (only methods)
        ThreeDee slice;
        // Initialise the volume class
        Volume* volume2 = new Volume();

        // Take in the users path to folder and path to save folder
        user_funcs.FolderPathRequest();
        user_funcs.SaveFolderPath();

        // Add this folder to the volume
        volume2->addImageFolder(user_funcs.folder_path.c_str());
        // Access the first image of the volume to determine img dims (and amount of images in the folder)
        Image image = volume2->getImage(0);
        int depth = volume2->get_size();
        int w = image.get_width();
        int h = image.get_height();

        // This block allows for the conversion of volume type to the Image type
        unsigned char* data = volume2->trans_volume(w, h, 1, depth);
        depth = volume2->get_size();
        Image trans_img(data, w, h, 1);

        // Initialise the filter class using the 3D constructor
        Filter black_white(trans_img, kernel_size, sigma, depth);

        // Storing the methods in a map
        unordered_map<int, std::function<void()>> overview_3d = {
                        {41, [&]() { black_white.median_blur_3d(); }},
                        {42, [&]() { black_white.gaussian_blur_3d(); }}, };

        if (overview_3d.find(filter_key) != overview_3d.end()) {
            overview_3d[filter_key]();  // Call the method
            black_white.SaveImgFolder(user_funcs.save_folder_path.c_str()); // Save to user specified folder
        }
        else {
            // Entering the slicing block
            user_funcs.xyChoice(); // Requesting a slice choice from the user
            if (user_funcs.choice == 'x') {
                // peform slicing
                int y = user_funcs.XSlice_dim(w);
                std::cout << y << endl;
                unsigned char* xz_slice;
                xz_slice = slice.Get_XZ_slice(volume2, y);
                std::cout << "Please specify the path to the XZ Slice" << std::endl;
                //ask user for the new save path
                user_funcs.UserSavePathForSlice();
                std::string full_save_path = user_funcs.save_folder_path + user_funcs.slice_filename;
                std::cout << "The full save path is: " << full_save_path << std::endl;
                // save to path
                stbi_write_png(full_save_path.c_str(), w, depth, 1, xz_slice, 0);
            }
            else if (user_funcs.choice == 'y') {
                int x = user_funcs.YSlice_dim(h);
                unsigned char* yz_slice;
                yz_slice = slice.Get_YZ_slice(volume2, x);
                std::cout << "Please specify the path to the YZ Slice" << std::endl;
                user_funcs.UserSavePathForSlice();
                std::string full_save_path = user_funcs.save_folder_path + user_funcs.slice_filename;
                std::cout << "The full save path is: " << full_save_path << std::endl;
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
                

                std::cout << "Please specify the path to the YZ Slice" << std::endl;
                user_funcs.UserSavePathForSlice();
                std::string full_save_path_yz = user_funcs.save_folder_path + user_funcs.slice_filename;
                stbi_write_png(full_save_path_yz.c_str(), depth, h, 1, yz_slice, 0);
                stbi_write_png(full_save_path_xz.c_str(), w, depth, 1, xz_slice, 0);
            }  
            
        }

    }
    else if (filter_key > 60) {
        //Entering the projection filters
        Volume* volume2 = new Volume();
        user_funcs.FolderPathRequest();
        volume2->addImageFolder(user_funcs.folder_path.c_str());
        int depth = volume2->get_size();
        user_funcs.UserSavePathForSlice();

        Projection proj(volume2);

        // Creating the map for the methods
        unordered_map<int, const char*> overview_proj = { {61, "max"}, {62, "min"}, {63, "mean"}, {64, "median"} };
        
        if (overview_proj.find(filter_key) != overview_proj.end()) {
            proj.IP(overview_proj[filter_key], user_funcs.slice_filename.c_str(), 0, depth, "run");
            std::cout << "Finished" << std::endl;
        }

    }

    return 0;
};
