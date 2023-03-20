

#include <vector>
#include <algorithm>

void median_blur(unsigned char* data, int w, int h, int c, int kernel_size) {
  const int kernel_radius = (kernel_size-1) / 2;

  std::vector<unsigned char> kernel_values(kernel_size * kernel_size);

  for (int channel = 0; channel < c; ++channel) {
    for (int y = 0; y < h; ++y) {
      for (int x = 0; x < w; ++x) {
        // Extract the pixel values within the kernel for the current channel
        int index = 0;
        for (int ky = -kernel_radius; ky <= kernel_radius; ++ky) {
          for (int kx = -kernel_radius; kx <= kernel_radius; ++kx) {
            int nx = x + kx;
            int ny = y + ky;
            if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
              kernel_values[index++] = data[(ny * w + nx) * c + channel];
            }
          }
        }

        // Sort the pixel values for the current channel
        std::sort(kernel_values.begin(), kernel_values.end());

        // Set the pixel value at the center of the kernel to the median value for the current channel
        data[(y * w + x) * c + channel] = kernel_values[(kernel_size* kernel_size)/ 2];
      }
    }
  }
}

// #include <vector>
// #include <algorithm>

// void median_blur(unsigned char* data, int w, int h, int c, int kernel_size) {
//   const int kernel_radius = kernel_size / 2;

//   std::vector<unsigned char> kernel_values(kernel_size * kernel_size);

//   for (int channel = 0; channel < c; ++channel) {
//     for (int y = 0; y < h; ++y) {
//       for (int x = 0; x < w; ++x) {
//         // Extract the pixel values within the kernel for the current channel
//         int index = 0;
//         for (int ky = -kernel_radius; ky <= kernel_radius; ++ky) {
//           for (int kx = -kernel_radius; kx <= kernel_radius; ++kx) {
//             int nx = x + kx;
//             int ny = y + ky;
//             if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
//               kernel_values[index++] = data[(ny * w + nx) * c + channel];
//             }
//           }
//         }

//         // Sort the pixel values for the current channel
//         std::sort(kernel_values.begin(), kernel_values.end());

//         // Set the pixel value at the center of the kernel to the median value for the current channel
//         data[(y * w + x) * c + channel] = kernel_values[kernel_size / 2];
//       }
//     }
//   }
// }





// #include <vector>
// #include <algorithm>

// void median_blur(unsigned char* data, int w, int h, int c, int kernel_size) {
//   const int kernel_radius = kernel_size / 2;

//   std::vector<unsigned char> kernel_values(kernel_size * kernel_size);

//   for (int channel = 0; channel < c; ++channel) {
//     for (int y = 0; y < h; ++y) {
//       for (int x = 0; x < w; ++x) {
//         // Extract the pixel values within the kernel for the current channel
//         int index = 0;
//         for (int ky = -kernel_radius; ky <= kernel_radius; ++ky) {
//           for (int kx = -kernel_radius; kx <= kernel_radius; ++kx) {
//             int nx = x + kx;
//             int ny = y + ky;
//             if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
//               kernel_values[index++] = data[(ny * w + nx) * c + channel];
//             }
//           }
//         }

//         // Sort the pixel values for the current channel
//         std::sort(kernel_values.begin(), kernel_values.end());

//         // Set the pixel value at the center of the kernel to the median value for the current channel
//         data[(y * w + x) * c + channel] = kernel_values[kernel_size / 2];
//       }
//     }
//   }
// }
