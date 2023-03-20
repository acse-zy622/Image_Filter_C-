#include <vector>

void box_blur(unsigned char* data, int w, int h, int c, int kernel_size) {
  const int kernel_radius = kernel_size / 2;

  std::vector<unsigned char> kernel_values(kernel_size * kernel_size);

  for (int channel = 0; channel < c; ++channel) {
    // Create a temporary copy of the image data for the current channel
    std::vector<unsigned char> temp_data(data, data + w * h * c);

    for (int y = 0; y < h; ++y) {
      for (int x = 0; x < w; ++x) {
        // Extract the pixel values within the kernel for the current channel
        int index = 0;
        int sum = 0;
        for (int ky = -kernel_radius; ky <= kernel_radius; ++ky) {
          for (int kx = -kernel_radius; kx <= kernel_radius; ++kx) {
            int nx = x + kx;
            int ny = y + ky;
            if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
              unsigned char pixel_value = temp_data[(ny * w + nx) * c + channel];
              kernel_values[index++] = pixel_value;
              sum += pixel_value;
            }
          }
        }

        // Set the pixel value at the center of the kernel to the average value for the current channel
        data[(y * w + x) * c + channel] = sum / index;
      }
    }
  }
}
