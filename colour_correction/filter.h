#pragma once
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

template <class T> 
class Filter
{
public:


	// constructor
	Filter(char const* i_path, char const* s_path) {
        img_path = i_path;
        save_path = s_path;
        }


    void ApplyGrayScale() {

        //// Read in image file
        img_data = stbi_load(img_path, &width, &height, &channels, 0);

        size_t img_size = width * height * channels;
        //cout << img_size << endl;

        // edit
        //gray_channels = (channels == 4) ? 2 : 1;
        gray_channels = 1;
        corrected_img = new unsigned char[width * height * gray_channels];

        // set initial loop conditions:
        // set a pointer of the same type to the first element of data (input pixel - coloured image)
        // set a pointer of the same type to the first element of gray image output

        // set conditions:
        // input_pixel != data + img_size -  data is a pointer to the first element the data array (so adding img_size gives us the final byte of memory - last value)

        // Incrementers:
        // Each pixel contains (R, G, B) so we have to make a step of 3 (if jpg) or 4 (if png)
        // We also step for the output so C can be 1 or 2.

        for (unsigned char* input_pixel = img_data, *output_pixel = corrected_img; input_pixel != img_data + img_size; input_pixel += channels, output_pixel += gray_channels)
        {
            // calculate the average of each RGB value within the pixel) - thats why input_pixel(+0) + (inputpixel + 1) etc...
            // cast this to unsigned 8 bit integer
            // this ensures pixel value is represeneted by exactly one byte (standard)
            *output_pixel = static_cast<uint8_t>((*input_pixel + *(input_pixel + 1) + *(input_pixel + 2)) / 3.0);
        }
        channels = gray_channels;
    }


    void AutoColourBalance() {
        //// Read in image file
        img_data = stbi_load(img_path, &width, &height, &channels, 0);
        // This part is being repeated (DRY!!!)
        size_t img_size = width * height * channels;
        size_t pixel_total = width * height;

        corrected_img = new unsigned char[width * height * channels];

        int red_total = 0;
        int green_total = 0;
        int blue_total = 0;

        for (unsigned char* input_pixel = img_data; input_pixel != img_data + img_size; input_pixel += channels) {

            red_total += *input_pixel; // not sure if its ordered like this for every image type
            green_total += *(input_pixel + 1);
            blue_total += *(input_pixel + 2);

            //*output_pixel = (*input_pixel + *(input_pixel + 1) + *(input_pixel + 2)) / 3.0;
        }

        map<char, double> inten_avg = { {'r', red_total / pixel_total}, {'g', green_total / pixel_total}, {'b', blue_total / pixel_total} };

        
        auto max_intensity = inten_avg.rbegin();
        double red_scale = max_intensity->second / inten_avg['r'];
        double green_scale = max_intensity->second / inten_avg['g'];
        double blue_scale = max_intensity->second / inten_avg['b'];

        //sanity check for instensity averages
        cout << red_scale<< endl;
        cout << green_scale << endl;
        cout << blue_scale << endl;

        for (unsigned char* input_pixel = img_data, *output_pixel = corrected_img; input_pixel != img_data + img_size; input_pixel += channels, output_pixel += channels) {

            *output_pixel = std::min((*input_pixel * red_scale), 255.0);
            *(output_pixel + 1) = std::min((*(input_pixel + 1) * green_scale), 255.0);
            *(output_pixel + 2) = std::min((*(input_pixel + 2) * blue_scale), 255.0);

        }
        cout << "I have completed" << endl;

    }


    void Brightness(int& brightness) {
        //// Read in image file
        img_data = stbi_load(img_path, &width, &height, &channels, 0);
        // This part is being repeated (DRY!!!)
        size_t img_size = width * height * channels;
        size_t pixel_total = width * height;

        corrected_img = new unsigned char[width * height * channels];

        int red_total = 0;
        int green_total = 0;
        int blue_total = 0;

        //total intensity for each channel
        for (unsigned char* input_pixel = img_data; input_pixel != img_data + img_size; input_pixel += channels) {

            red_total += *input_pixel; // not sure if its ordered like this for every image type
            green_total += *(input_pixel + 1);
            blue_total += *(input_pixel + 2);
        }

        double red_avg = red_total / (double)pixel_total;
        double green_avg = green_total / (double)pixel_total;
        double blue_avg = blue_total / (double)pixel_total;

        double red_scale = brightness / red_avg;
        double green_scale = brightness / green_avg;
        double blue_scale = brightness / blue_avg;

        for (unsigned char* input_pixel = img_data, *output_pixel = corrected_img; input_pixel != img_data + img_size; input_pixel += channels, output_pixel += channels) {
            *output_pixel = std::max(0.0, std::min((*input_pixel) * red_scale, 255.0));
            *(output_pixel + 1) = std::max(0.0, std::min((*(input_pixel + 1)) * green_scale, 255.0));
            *(output_pixel + 2) = std::max(0.0, std::min((*(input_pixel + 2)) * blue_scale, 255.0));
        }

    }



    void SaveImg() {

        //int success = stbi_write_png(save_path, width, height, gray_channels, gray_img, 0);
        int success = stbi_write_png(save_path, width, height, channels, corrected_img, 0);
        std::cout << "Success, Image has been saved";
        // Deallocate memory
        //stbi_image_free(data);
        //delete[] gray_img;
    }

   /* int width, height, channels;
    unsigned char* corrected_img;
    int gray_channels;*/

    unsigned char* corrected_img;

    int width, height, channels;

    int gray_channels;
    unsigned char* img_data;
    //unsigned char* gray_img;
    char const* img_path = nullptr;
    char const* save_path = nullptr;

protected:

    //edge_detect constructor - accessible to derived classes
    //Filter(unsigned char* corrected_img, int width, int height, int channels) :
    //    corrected_img(corrected_img), width(width), height(height), channels(channels) {}

private:
		
};