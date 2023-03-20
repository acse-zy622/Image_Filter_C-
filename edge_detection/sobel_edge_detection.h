
#include <iostream>
#include <cmath>

using namespace std;

void sobel_edge_detection(unsigned char* input, unsigned char* output, int width, int height) {
    int gx, gy;
    // apply the filers to each pixel, except for the borders
    for(int y = 1; y < height - 1; y++) {
        for(int x = 1; x < width - 1; x++) {
            // calculate the convolutions with the Sobel filter in X direction
            gx = -input[(y - 1) * width + (x - 1)] - 2 * input[y * width + (x - 1)] - input[(y + 1) * width + (x - 1)] +
                 input[(y - 1) * width + (x + 1)] + 2 * input[y * width + (x + 1)] + input[(y + 1) * width + (x + 1)];
            // calculate the convolutions with the Sobel filter in X direction
            gy = -input[(y - 1) * width + (x - 1)] - 2 * input[(y - 1) * width + x] - input[(y - 1) * width + (x + 1)] +
                 input[(y + 1) * width + (x - 1)] + 2 * input[(y + 1) * width + x] + input[(y + 1) * width + (x + 1)];
            // calculate the gradient magnitude
             int mag = abs(gx) + abs(gy);
            //set the output pixel value with a cap of 225, the max value represented by an 8-bit integer
            output[y * width + x] = (mag > 255) ? 255 : mag;
        }
    }
}


