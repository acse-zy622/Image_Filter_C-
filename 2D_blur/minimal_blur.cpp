

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <vector>
#include <algorithm>
#include "median_blur.h"
#include "box_blur.h"
#include "gaussian_blur.h"

void median_blur(unsigned char* data, int w, int h, int c, int kernel_size);
void box_blur(unsigned char* data, int w, int h, int c, int kernel_size);
void gaussian_blur(unsigned char* data, int w, int h, int c, int kernel_size, float sigma);




int main() {
  int w, h, c;
  unsigned char* data = stbi_load("/Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Images/gracehopper.png", &w, &h, &c, 0);

  const int kernel_size = 3;

  median_blur(data, w, h, c, kernel_size);

  stbi_write_png("/Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Output/gracehopper_medianblur_.png", w, h, c, data, 0);

  stbi_image_free(data);

  unsigned char* data1 = stbi_load("/Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Images/gracehopper.png", &w, &h, &c, 0);


  box_blur(data1, w, h, c, kernel_size);

  stbi_write_png("/Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Output/gracehopper_boxblur_.png", w, h, c, data1, 0);

  stbi_image_free(data1);
  
  
  unsigned char* data2 = stbi_load("/Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Images/gracehopper.png", &w, &h, &c, 0);

  const float sigma = 0.5;

  gaussian_blur(data2, w, h, c, kernel_size,sigma);

  stbi_write_png("/Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Output/gracehopper_gaussianblur_.png", w, h, c, data, 0);

  stbi_image_free(data2);

  return 0;
}






// void box_blur(unsigned char* data, int w, int h, int c, int kernel_size);

// int main() {
//   int w, h, c;
//   unsigned char* data1 = stbi_load("/Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Images/gracehopper.png", &w, &h, &c, 0);

//   const int kernel_size = 3;

//   box_blur(data1, w, h, c, kernel_size);

//   stbi_write_png("/Users/ql1522/Desktop/acse/advanced-programming-group-kruskal/Output/gracehopper_boxblur_.png", w, h, c, data1, 0);

//   stbi_image_free(data1);

//   return 0;
// }

