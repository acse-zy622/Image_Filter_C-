/**
* @file UserInput.h
* @brief Header file and Implementation for the UserInput class.
*
* This file contains the declaration of the UserInput class used to construct UI.
*
* Group Members:
* - Hang Zhao (edsml-hz822)
* - Luwen Liang (edsml-ll2822)
* - Elliott Mcquire (acse-ecm22)
* - Zhuoran Yang (acse-zy622)
* - Qingyang Lu (acse-ql1522)
*/

#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <vector>
using namespace std;

class UserInput {
public:


    string img_path;
    string save_path;
    string folder_path;
    string save_folder_path;
    string slice_filename;
    char choice;

        /**
     * @brief Allows the user to specify a path to where a single image is located.
     */

    void UserPathRequest() {
        bool valid_path = false;
        while (!valid_path) {
            cout << "Please enter the path to the image you would like to filter: ";
            cin >> img_path;
            ifstream file(img_path);
            if (file.good()) {
                valid_path = true;
                cout << "Valid path entered." << endl;
            }
            else {
                cout << "Invalid path entered. Please try again." << endl;
            }
        }
    }

    /**
     * @brief Allows the user to specify a path to where a single image should be saved.
     */

    void UserSavePath() {
        char decider = '\0';

        while (decider != 'y' && decider != 'n') {
            cout << "Would you like to rename the path? [y/n]: ";
            cin >> decider;

            if (decider == 'y') {
                cout << "Please specify your path: ";
                cin >> save_path;

                // check file extension
                string extension = save_path.substr(save_path.find_last_of(".") + 1);
                if (extension != "bmp" && extension != "png" && extension != "jpg" && extension != "jpeg") {
                    cout << "Invalid file extension. Please save as .bmp, .png, .jpg, or .jpeg." << endl;
                    decider = '\0';
                }
                else {
                    cout << "Saving as: " << save_path << endl;
                    cout << endl;
                }
            }
            else if (decider == 'n') {
                cout << "Saving as: " << img_path << endl;
                save_path = img_path;
                cout << endl;
            }
            else {
                cout << "Invalid choice" << endl;
                decider = '\0';
            }
        }
    }

    /**
     * @brief Allows the user to specify a path to where a single image should be saved
     * This is a helper function for the 3D methods.
     */

    void UserSavePathForSlice() {
        bool decider = false;
        

        while (decider != true) {
            cout << "Please specify the new file name: ";
            getline(cin, slice_filename);

            // check file extension
            string extension = slice_filename.substr(slice_filename.find_last_of(".") + 1);
            if (extension != "bmp" && extension != "png" && extension != "jpg" && extension != "jpeg") {
                cout << "Invalid file extension. Please save as .bmp, .png, .jpg, or .jpeg." << endl;
                decider = false;
            }
            else {
                cout << "Valid choice" << endl;
                decider = true;
            }
        }
    }

    /**
     * @brief Allows the user to specify a folder/directory where a volume of images are stored
     */

    void FolderPathRequest() {
        bool valid_path = false;
        while (!valid_path) {
            cout << "Please enter the path to the folder containing images you would like to filter: ";
            cin >> folder_path;
            if (filesystem::is_directory(folder_path)) {
                valid_path = true;
                cout << "Valid path entered." << endl;
            }
            else {
                cout << "Invalid path entered. Please try again." << endl;
            }
        }
    }


    /**
     * @brief Allows the user to specify a folder/directory where a volume of images should be saved.
     */
    void SaveFolderPath() {
        bool valid_path = false;
        while (!valid_path) {
            cout << "Please enter the path to the folder that you would like to save the images: ";
            cin >> save_folder_path;
            if (filesystem::is_directory(save_folder_path)) {
                valid_path = true;
                cout << "Valid path entered." << endl;
            }
            else {
                cout << "Invalid path entered. Please try again." << endl;
            }
        }
    }

        /**
     * @brief Allows the user to navigate through a quick version of the menu.
     * returning a filter key to specify which filter should be chosen
     *
     * @return int user_choice
     */
    int QuickMenu() {

        int user_choice;
        bool selected = false;

        unordered_map<int, string> overview = { {11, "GrayScale"}, {12, "ColourCorrection"}, {13, "AutoBrightness"},
                                              {21, "BoxBlur"}, {22, "MedianBlur"}, {23, "GaussBlur"}, {31, "Sobel"},
                                              {32, "Prewitt"}, {41, "Median 3D Blur"}, {42, "Gaussian 3D Blur"},
                                              {51, "3D Slicing"}, {61, "Max Projection"}, {62, "Min Projection"},
                                              {63, "Mean Projection"}, {64, "Median Projection"} };

        while (selected != true){
            cout << "Hello! You have selected Quick Menu\n";
            cout << "Please see your options below: \n";
            for (auto const& pair : overview) {
                std::cout << "{" << pair.first << ": " << pair.second << "}\n";
            }
            cin >> user_choice;

            if (overview.find(user_choice) != overview.end()) {
                selected = true;
            }
            else {
                cout << "\nInvalid Key - Please retry \n" << endl;
            }
        }
        
        return user_choice;

        

    }

        /**
      * @brief Allows the user to navigate through a longer version of the menu.
      * returning a filter key to specify which filter should be chosen
      *
      * @return int user_choice
      */

    int FilterMenu() {

        int user_choice_store;
        int user_refined_choice;
        bool selected = false;

        unordered_map<int, string> overview = { {1, "Colour Correction"}, {2, "Image Blur"}, {3, "Edge Detection"}, {4, "3D Filters"}, {5, "3D Image Slicing"} };
        unordered_map<int, string> ColourCorrect = { {1, "GrayScale"}, {2, "ColourCorrection"}, {3, "AutoBrightness"} };
        unordered_map<int, string> Blur = { {1, "BoxBlur"}, {2, "MedianBlur"}, {3, "GaussBlur"} };
        unordered_map<int, string> EdgeDetection = { {1, "Sobel"}, {2, "Prewitt"} };
        unordered_map<int, string> Blur_3d = { {1, "Median 3D Blur"}, {2, "Gaussian 3D Blur"} };
        unordered_map<int, string> Slicing = { {1, "3D Slicing"} };
        unordered_map<int, string> Project = { {1, "Max Projection"}, {2, "Min Projection"}, {3, "Min Projection"}, {4, "Min Projection"} };
        vector<unordered_map<int, string>> all_filters = { ColourCorrect, Blur, EdgeDetection, Blur_3d, Slicing, Project};



        cout << "Please select a filter from the following list using the assigned number: \n" << endl;

        while (selected != true) {
            for (int i = 1; i < overview.size()+1; i++) {
                cout << overview[i] << ": " << i << endl;
            }
            cout << "\nPlease Select: ";
            cin >> user_choice_store;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid input. Please enter an integer.\n" << endl;
            }
            else if (overview.find(user_choice_store) != overview.end()) {
                selected = true;
            }
            else {
                cout << "\nInvalid Key - Please retry \n" << endl;
                
            }
        }

        cout << "\nYou have chosen "<< overview[user_choice_store] << " filters! Please select which filter you would like to use: \n" << endl;
        while (selected == true) {
            unordered_map<int, string> user_filter = all_filters[user_choice_store - 1];
            for (int i = 0; i < user_filter.size(); i++) {
                cout << user_filter[i+1] << ": " << i+1 << endl;
            }
            cout << "Please Select: ";
            cin >> user_refined_choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid input. Please enter an integer.\n" << endl;
            }
            else if (user_filter.find(user_refined_choice) != user_filter.end()) {
                selected = false;
            }
            else {
                cout << "\nInvalid Key - Please retry \n" << endl;
            }
        }

        string s1 = to_string(user_choice_store);
        string s2 = to_string(user_refined_choice);
        //concat choice
        string s = s1 + s2;
        int filter_key = stoi(s);

        return filter_key;

    }

        /**
      * @brief Allows the user to specify a brightness for the autobright filter
      *
      * @return int user_brightness
      */

    int BrightnessRequest() {
        bool valid = false;
        int user_brightness;

        while (!valid) {
            cout << "\nPlease enter a brightness within the range of 1 to 255: ";
            cin >> user_brightness;

            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                cout << "\nInvalid input. Please enter an integer.\n" << endl;
            }
            else if (user_brightness < 1 || user_brightness > 255) {
                cout << "\nInvalid input. Please enter a value within the range of 1 to 255.\n" << endl;
            }
            else {
                valid = true;
            }
        }

        return user_brightness;
    }

        /**
      * @brief Allows the user to choose the dimensions of which the slice is performed
      *
      * @return int y_dim
      */

    int XSlice_dim(int y_max) {

        bool valid = false;
        int y_dim;

        while (valid != true) {
            cout << "\nPlease enter a y position to slice (max: " << y_max << "): " << endl;
            cin >> y_dim;
            if (cin.fail()) {
                cin.clear();
                //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid input. Please enter an integer.\n" << endl;
            }
            else if (y_dim < y_max) {
                valid = true;
            }
        }

        return y_dim;
    }

    /**
    * @brief Allows the user to choose the dimensions of which the slice is performed
    *
    * @return int x_dim
    */

    int YSlice_dim(int x_max) {

        bool valid = false;
        int x_dim;

        while (valid != true) {
            cout << "\nPlease enter a x position to slice (max: " << x_max << "): " << endl;
            cin >> x_dim;
            if (cin.fail()) {
                cin.clear();
                //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid input. Please enter an integer.\n" << endl;
            }
            else if (x_dim < x_max) {
                valid = true;
            }
        }

        return x_dim;
    }

    /**
    * @brief Allows the user to specify if they want to save bot a XZ and YZ slice.
    *
    */

    void xyChoice() {
        bool valid = false;

        while (!valid) {
            cout << "\nPlease enter either 'x' or 'y' for XZ or YZ slice. For both enter 'b': ";
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid input. Please enter either 'x' for XZ slice, or 'y' for YZ slice.\n" << endl;
                continue;
            }
            choice = tolower(choice);
            if (choice != 'x' && choice != 'y' && choice != 'b') {
                cout << "\nInvalid input. Please enter either 'x' for XZ slice, 'y' for YZ slice, or 'b' for both.\n" << endl;
                continue;
            }
            valid = true;
        }
    }
};