
#include "Volume.h"
#include "3d_ops-1.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"



//int main() {
//    
//    // calls the constructor for volume
//    Volume volume2;
//    volume2.addImageFolder("C:/Users/ecm22/source/repos/oriana_test/Scans/confuciusornis/");
//    //v2->getImageList();
//    ThreeDee slice;
//    // const auto& vv = v2->getImageList();
//    // if (min_z < 0 || max_z > vv.size() || min_z > max_z) {
//    //     std::cerr << "Invalid thin slabs!" << std::endl;
//    // }
//    // auto images = std::vector<Image>(vv.begin() + min_z, vv.begin() + max_z );
//
//    Image image = volume2.getImage(0);
//    int z = volume2.get_size();
//    int w = image.get_width();
//    int h = image.get_height();
//    
//    std::cout << z << std::endl;
//
//    // Define the empty slice
//    unsigned char* xz_slice;
//    unsigned char* yz_slice;
//    int y=420;
//    int x=100;
//    xz_slice= slice.Get_XZ_slice(volume2, y);
//    yz_slice= slice.Get_YZ_slice(volume2, x);
//    int success_xz = stbi_write_png("C:/Users/ecm22/source/repos/oriana_test/Scans/confruc_out/try.png", w, z, 1, xz_slice, 0);
//    //int success_yz = stbi_write_png("/Users/ll2822/eclipse-workspace/GroupProject0320/Output/yz_slice.png", z, h, 1, yz_slice, 0);
//    return 0;
//  }

//int main() {
//
//    // calls the constructor for volume
//    Volume* volume2 = new Volume();
//    volume2->addImageFolder("C:/Users/ecm22/source/repos/oriana_test/Scans/confuciusornis/");
//
//    ThreeDee slice;
//
//
//    Image image = volume2->getImage(0);
//    int z = volume2->get_size();
//    int w = image.get_width();
//    int h = image.get_height();
//
//    std::cout << z << std::endl;
//
//    // Define the empty slice
//    unsigned char* xz_slice;
//    unsigned char* yz_slice;
//    int y = 420;
//    int x = 100;
//    xz_slice = slice.Get_XZ_slice(volume2, y);
//    yz_slice = slice.Get_YZ_slice(volume2, x);
//    int success_xz = stbi_write_png("C:/Users/ecm22/source/repos/oriana_test/Scans/confruc_out/try.png", w, z, 1, xz_slice, 0);
//    int success_yz = stbi_write_png("/Users/ll2822/eclipse-workspace/GroupProject0320/Output/yz_slice.png", z, h, 1, yz_slice, 0);
//    return 0;
//}









