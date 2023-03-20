#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class UserInput {
public:


    string img_path;
    string save_path;


    void UserPathRequest() {
        cout << "Please enter the path to the image you would like to filter: ";
        cin >> img_path;
    }

    void UserSavePath() {

        char decider = '\0';

        while (decider != 'y' && decider != 'n') {

            cout << "Would you like to rename the path? [y/n]: ";
            cin >> decider;

            if (decider == 'y') {
                cout << "Please specify your path: ";
                cin >> save_path;
                cout << "Saving as: " << save_path << endl;
                cout << endl;
            }
            else if (decider == 'n') {
                cout << " Saving as: " << img_path << endl;
                cout << endl;
            }
            else {
                cout << "Invalid choice" << endl;
                decider = '\0';
            }
        }
    }

    int QuickMenu() {

        int user_choice;
        bool selected = false;

        unordered_map<int, string> overview = { {11, "GrayScale"}, {12, "ColourCorrection"}, {13, "AutoBrightness"},
                                              {21, "BoxBlur"}, {22, "MedianBlur"}, {23, "GaussBlur"}, {30, "Sobel"},
                                              {31, "Prewitt"} };

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

    int FilterMenu() {

        /*unordered_map<string, int> filter_list = { {"GrayScale", 1}, {"ColourCorrection", 2}, {"AutoBrightness", 3}, {"MedianBlur", 4},
            {"Bo}}*/

        int user_choice_store;
        int user_refined_choice;
        bool selected = false;

        unordered_map<int, string> overview = { {1, "Colour Correction"}, {2, "Image Blur"}, {3, "Edge Detection"} };
        unordered_map<int, string> ColourCorrect = { {1, "GrayScale"}, {2, "ColourCorrection"}, {3, "AutoBrightness"} };
        unordered_map<int, string> Blur = { {1, "BoxBlur"}, {2, "MedianBlur"}, {3, "GaussBlur"} };
        unordered_map<int, string> EdgeDetection = { {1, "Sobel"}, {2, "Prewitt"} };
        vector<unordered_map<int, string>> all_filters = { ColourCorrect, Blur, EdgeDetection };


        //unordered_map<string, vector<unordered_map<int, string>>> select_filters = { {""}}


        cout << "Please select a filter from the following list using the assigned number: \n" << endl;

        while (selected != true) {
            for (int i = 1; i < overview.size()+1; i++) {
                cout << overview[i] << ": " << i << endl;
            }
            cout << "\nPlease Select: ";
            cin >> user_choice_store;
            if (overview.find(user_choice_store) != overview.end()) {
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
            if (user_filter.find(user_refined_choice) != user_filter.end()) {
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
};