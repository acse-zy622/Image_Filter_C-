#include "3d_ops-1.h"
#include "Volume.h"
#include "Image.h"


ThreeDee::ThreeDee() {}

unsigned char* ThreeDee::Get_XZ_slice(Volume* img, int y) {
    // this gives Z
    int z = img->get_size();
    //Now I need to get w and height
    Image image = img->getImage(0);
    int w = image.get_width();
    int h = image.get_height();
    unsigned char* xz_slice;

    xz_slice = new unsigned char[w * z];
    for (int i = 0; i < z; i++) {
        for (int j = 0; j < w; j++) {
            xz_slice[i * w + j] = img->getImage(i).data[y * w + j];
        }
    }
    return xz_slice;

}

unsigned char* ThreeDee::Get_YZ_slice(Volume* img, int x) {
    int z = img->get_size();
    
    // Now I need to get w and height
    Image image = img->getImage(0);
    int w = image.get_width();
    int h = image.get_height();
    unsigned char* yz_slice;

    yz_slice = new unsigned char[h * z];
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < z; ++j) {
            yz_slice[i * z + j] = img->getImage(j).data[i * w + x];
        }
    }
    return yz_slice;
}


// destructor for the volume.
ThreeDee::~ThreeDee() {}
