
#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"
#include <vector>
#include "sobel_edge_detection.h"
#include "filter.h"

void sobel_edge_detection(unsigned char* input, unsigned char* output, int width, int height);

int main() {
    int width, height, channels;
    
    // allocate memory for output image
    unsigned char* output = new unsigned char[width * height];

    Filter<int> black_white("/Users/hz822/advanced-programming-group-kruskal-main/Images/gracehopper.png", "/Users/hz822/advanced-programming-group-kruskal-main/src/output.png");
    
    black_white.ApplyGrayScaleOneChannel();
    black_white.SaveImg();

    // read image
    unsigned char* data = stbi_load("/Users/hz822/advanced-programming-group-kruskal-main/src/output.png", &width, &height, &channels, 0);
    
    // apply Sobel filter
    sobel_edge_detection(data, output, width, height);

    // save image
    //SaveImg(output, width, height, channels, "/Users/hz822/advanced-programming-group-kruskal-main/src/output222.png");
    stbi_write_png("/Users/hz822/advanced-programming-group-kruskal-main/src/output22.png", width, height, channels, output, 0);
    
    // free memory
    stbi_image_free(data);
    delete[] output;

    return 0;
}

  






