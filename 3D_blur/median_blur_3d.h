
#pragma once
#include <vector>
#include <algorithm>

/**
 * Apply median blur filter on 3D image data for each channel
 *
 * @param data Pointer to the image data array
 * @param w Width of the image
 * @param h Height of the image
 * @param d Depth of the image
 * @param c Number of channels in the image
 * @param kernel_size Size of the kernel used for the median filter. Must be odd.
 */
void median_blur_3d(unsigned char* data, int w, int h, int d, int c, int kernel_size) {

  const int kernel_radius = (kernel_size-1) / 2;
  // const int kernel_size_sq = kernel_size * kernel_size * kernel_size;
  std::vector<unsigned char> kernel_values(kernel_size * kernel_size * kernel_size);
  
  for (int channel = 0; channel < c; ++channel) {
    // Create a temporary copy of the image data for the current channel
    std::vector<unsigned char> temp_data(data, data + w * h * d * c);

    for (int z = 0; z < d; ++z) {
      for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
          // Get the median pixel value within the kernel for the current channel
          std::vector<unsigned char> pixel_values;
          for (int kz = -kernel_radius; kz <= kernel_radius; ++kz) {
            for (int ky = -kernel_radius; ky <= kernel_radius; ++ky) {
              for (int kx = -kernel_radius; kx <= kernel_radius; ++kx) {
                int nx = x + kx;
                int ny = y + ky;
                int nz = z + kz;
                if (nx >= 0 && nx < w && ny >= 0 && ny < h && nz >= 0 && nz < d) {
                  unsigned char pixel_value = temp_data[((nz * h + ny) * w + nx) * c + channel];
                  pixel_values.push_back(pixel_value);
                }
              }
            }
          }
          std::sort(pixel_values.begin(), pixel_values.end());
          unsigned char median_value = pixel_values[pixel_values.size() / 2];

          // Set the pixel value at the center of the kernel to the median value for the current channel
          data[((z * h + y) * w + x) * c + channel] = median_value;
        }
      }
    }
  }
}



