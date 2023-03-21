#pragma once
#include "filter.h"
#include "assert.h"

template <class T>
class Edge {
public:

    Edge(unsigned char* corrected_img, int width, int height, int channel, const char* sv_pth){
        input = corrected_img;
        w = width;
        h = height;
        c = channel;
        save_path = sv_pth;
    }

    //Needs to Inherit (input width and height)
    void Sobel() {

        output = new unsigned char[w * h * c];

        //new change (revert if fails)

        // mask (sobel x)
        vector<vector<int>> gx = { {-1,0,1},{-2,0,2},{-1,0,1} };
        // mask (sobel y)
        vector<vector<int>> gy = { {-1,-2,-1},{0,0,0},{1,2,1} };

        for (int i = 1; i < h - 1; i++) {
            for (int j = 1; j < w - 1; j++) {
                int valx = 0;
                int valy = 0;
                //calculating the X and Y convolutions
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        valx += input[(i + x) * w + (j + y)] * gx[1 + x][1 + y];
                        valy += input[(i + x) * w + (j + y)] * gy[1 + x][1 + y];
                    }
                }
                //cout << "I am at the end of the line" << endl;

                //Gradient magnitude
                //int magnitude = sqrt(pow(valx, 2) + pow(valy, 2));
                int magnitude = abs(valx) + abs(valy);
           
                //*( output + i * width + j) = magnitude > 225 ? 225 : magnitude;

                output[i * w + j] = magnitude > 225 ? 225 : magnitude;
                //output[i * image_width + j + 1] = output[i * image_width + j];

            }
        }
        
    }

    void X_gradient() {
        for (int i = 1; i < h - 1; i++) {
            for (int j = 1; j < w - 1; j++) {
                int val = input[w * (i + 1) + j] + input[w * (i + 1) + j - 1] + input[w * (i + 1) + j + 1] -
                    (input[w * (i - 1) + j] + input[w * (i - 1) + j - 1] + input[w * (i - 1) + j + 1]);
                output[w * i + j] = min(max(val, 0), 255);
            }
        }
    }

    void Y_gradient() {
        for (int i = 1; i < h - 1; i++) {
            for (int j = 1; j < w - 1; j++) {
                int val = input[w * (i + 1) + j] + input[w * (i + 1) + j - 1] + input[w * (i + 1) + j + 1] -
                    (input[w * (i - 1) + j] + input[w * (i - 1) + j - 1] + input[w * (i - 1) + j + 1]);
                output[w * i + j] = min(max(val, 0), 255);
            }
        }
    }

    // edge detection
    void prewitt_edge_detect() {
        output = new unsigned char[w * h * c];
        assert(w > 0);
        assert(h > 0);
        assert(c == 1);
        // get X gradient and Y gradient 
        int* gx = new int[w * h];
        int* gy = new int[w * h];
        X_gradient();
        Y_gradient();
        // compute the value of image using X gradient and Y gradient 
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                input[w * i + j] = sqrt(gx[w * i + j] * gx[w * i + j] + gy[w * i + j] * gy[w * i + j]);
            }
        }
        delete[] gx;
        delete[] gy;
    }

    void SaveImg() {
        cout << "We are at the save location";
        //int success = stbi_write_png(save_path, width, height, gray_channels, gray_img, 0);
        int success = stbi_write_png(save_path, w, h, c, output, 0);
        std::cout << "Success, Image has been saved";

    }

private:
    unsigned char* input;
    unsigned char* output;
    int w, h;
    int c;
    char const* save_path;
};