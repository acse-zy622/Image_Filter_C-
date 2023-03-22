#include <vector>
#include <cmath>

void gaussian_blur_3d(unsigned char* data, int w, int h, int d, int c, int kernel_size, float sigma) {

  
  const int kernel_radius = kernel_size / 2;
  const int kernel_size_sq = kernel_size * kernel_size;
  std::vector<float> kernel_values(kernel_size_sq * kernel_size);

  // Calculate the values of the kernel
  float sum = 0.0f;
  for (int kz = -kernel_radius; kz <= kernel_radius; ++kz) {
    for (int ky = -kernel_radius; ky <= kernel_radius; ++ky) {
      for (int kx = -kernel_radius; kx <= kernel_radius; ++kx) {
        float value = exp(-(kx * kx + ky * ky + kz * kz) / (2.0f * sigma * sigma));
        kernel_values[((kz + kernel_radius) * kernel_size + (ky + kernel_radius)) * kernel_size + (kx + kernel_radius)] = value;
        sum += value;
      }
    }
  }

  // Normalize the kernel
  for (int i = 0; i < kernel_size_sq * kernel_size; ++i) {
    kernel_values[i] /= sum;
  }

  for (int channel = 0; channel < c; ++channel) {
    // Create a temporary copy of the image data for the current channel
    std::vector<unsigned char> temp_data(data, data + w * h * d * c);

    for (int z = 0; z < d; ++z) {
      for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
          // Apply the kernel to the pixel values within the kernel for the current channel
          float sum = 0.0f;
          for (int kz = -kernel_radius; kz <= kernel_radius; ++kz) {
            for (int ky = -kernel_radius; ky <= kernel_radius; ++ky) {
              for (int kx = -kernel_radius; kx <= kernel_radius; ++kx) {
                int nx = x + kx;
                int ny = y + ky;
                int nz = z + kz;
                if (nx >= 0 && nx < w && ny >= 0 && ny < h && nz >= 0 && nz < d) {
                  unsigned char pixel_value = temp_data[((nz * h + ny) * w + nx) * c + channel];
                  float kernel_value = kernel_values[((kz + kernel_radius) * kernel_size + (ky + kernel_radius)) * kernel_size + (kx + kernel_radius)];
                  sum += pixel_value * kernel_value;
                }
              }
            }
          }

          // Set the pixel value at the center of the kernel to the convolved value for the current channel
          data[((z * h + y) * w + x) * c + channel] = static_cast<unsigned char>(sum + 0.5f);
        }
      }
    }
  }
}