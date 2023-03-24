/**
 * @file 3d_ops.cpp
 * @author Group Members:
 * - Hang Zhao (edsml-hz822)
 * - Luwen Liang (edsml-ll2822)
 * - Elliott Mcquire (acse-ecm22)
 * - Zhuoran Yang (acse-zy622)
 * - Qingyang Lu (acse-ql1522)
 * @brief Implementation of the slice class(named ThreeDee in our project)
 * @version 0.1
 * @date 2023-03-24
 * @copyright Copyright (c) 2023
 *
 */
#include "3d_ops.h"
#include "Volume.h"
#include "Image.h"

 /**
  * @brief Construct a new Three Dee:: Three Dee object
  *
  */
ThreeDee::ThreeDee() {}

/**
 * @brief get x-z slice
 *
 * @param img | the volume that need to get slice
 * @param y | a constant y value to slice
 * @return unsigned char* | a pointer to the slice
 */
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

/**
 * @brief get y-z slice of a 3D volume
 *
 * @param img | the volume that need to get slice
 * @param x | a constant x value to slice
 * @return unsigned char* | a pointer to the slice
 */
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


/**
 * @brief Destroy the Three Dee:: Three Dee object
 *
 */
ThreeDee::~ThreeDee() {}