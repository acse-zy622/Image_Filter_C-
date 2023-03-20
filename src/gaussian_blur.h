#include <vector>
#include <cmath>

void gaussian_blur(unsigned char* data, int w, int h, int c, int kernel_size, float sigma) {
  const int kernel_radius = kernel_size / 2;
  std::vector<float> kernel_values(kernel_size * kernel_size);

  // Calculate the values of the kernel
  float sum = 0.0f;
  for (int ky = -kernel_radius; ky <= kernel_radius; ++ky) {
    for (int kx = -kernel_radius; kx <= kernel_radius; ++kx) {
      float value = exp(-(kx * kx + ky * ky) / (2.0f * sigma * sigma));
      kernel_values[(ky + kernel_radius) * kernel_size + (kx + kernel_radius)] = value;
      sum += value;
    }
  }

  // Normalize the kernel
  for (int i = 0; i < kernel_size * kernel_size; ++i) {
    kernel_values[i] /= sum;
  }

  for (int channel = 0; channel < c; ++channel) {
    // Create a temporary copy of the image data for the current channel
    std::vector<unsigned char> temp_data(data, data + w * h * c);

    for (int y = 0; y < h; ++y) {
      for (int x = 0; x < w; ++x) {
        // Apply the kernel to the pixel values within the kernel for the current channel
        float sum = 0.0f;
        for (int ky = -kernel_radius; ky <= kernel_radius; ++ky) {
          for (int kx = -kernel_radius; kx <= kernel_radius; ++kx) {
            int nx = x + kx;
            int ny = y + ky;
            if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
              unsigned char pixel_value = temp_data[(ny * w + nx) * c + channel];
              float kernel_value = kernel_values[(ky + kernel_radius) * kernel_size + (kx + kernel_radius)];
              sum += pixel_value * kernel_value;
            }
          }
        }

        // Set the pixel value at the center of the kernel to the convolved value for the current channel
        data[(y * w + x) * c + channel] = static_cast<unsigned char>(sum + 0.5f);
      }
    }
  }
}

