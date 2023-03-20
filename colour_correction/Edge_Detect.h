#pragma once
#include "filter.h"

template <class T>
class Edge {
public:

    /*Edge(unsigned char* corrected_img, int width, int height) : Filter<T>(corrected_img, width, height){
    }*/

    //Edge() : input(nullptr), output(nullptr), width(0), height(0), gray_channels(0) {}

    Edge(unsigned char* corrected_img, int w, int h, int channel) {
        input = corrected_img;
        width = w;
        height = h;
        channels = channel;
    }

    //Needs to Inherit (input width and height)
    void Sobel() {
        cout << "Hello";
        output = new unsigned char[width * height * channels];

        //new change (revert if fails)

        cout << "Image Height: " << height << endl;
        cout << "Image Width: " << width << endl;
        // mask (sobel x)
        vector<vector<int>> gx = { {-1,0,1},{-2,0,2},{-1,0,1} };
        // mask (sobel y)
        vector<vector<int>> gy = { {-1,-2,-1},{0,0,0},{1,2,1} };

        for (int i = 1; i < height - 1; i++) {
            for (int j = 1; j < width - 1; j++) {
                int valx = 0;
                int valy = 0;
                //calculating the X and Y convolutions
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        valx += input[(i + x) * width + (j + y)] * gx[1 + x][1 + y];
                        valy += input[(i + x) * width + (j + y)] * gy[1 + x][1 + y];
                    }
                }
                //cout << "I am at the end of the line" << endl;

                //Gradient magnitude
                //int magnitude = sqrt(pow(valx, 2) + pow(valy, 2));
                int magnitude = abs(valx) + abs(valy);
           
                //*( output + i * width + j) = magnitude > 225 ? 225 : magnitude;
                output[i * width + j] = magnitude > 225 ? 225 : magnitude;
                //output[i * image_width + j + 1] = output[i * image_width + j];

            }
        }
        
    }

    void SaveImg_remove() {
        cout << "We are at the save location";
        //int success = stbi_write_png(save_path, width, height, gray_channels, gray_img, 0);
        int success = stbi_write_png("GraceHopper_test_edge.png", width, height, channels, output, 0);
        std::cout << "Success, Image has been saved";

    }

private:
    unsigned char* input;
    unsigned char* output;
    int width, height;
    int channels;
    char const* save_path = "gracehopper_test_edge.png";
};