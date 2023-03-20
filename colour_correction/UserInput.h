#pragma once
#include <iostream>
#include <string>
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
            }
            else if (decider == 'n') {
                cout << " Saving as: " << img_path << endl;
            }
            else {
                cout << "Invalid choice" << endl;
                decider = '\0';
            }
        }

    }
};