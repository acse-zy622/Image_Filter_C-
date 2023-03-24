/**
 * @file 3d_ops-1.h
 * @author Group Members:
 * - Hang Zhao (edsml-hz822)
 * - Luwen Liang (edsml-ll2822)
 * - Elliott Mcquire (acse-ecm22)
 * - Zhuoran Yang (acse-zy622)
 * - Qingyang Lu (acse-ql1522)
 * @brief Header file for the slice class(named ThreeDee in our project).
 * @version 0.1
 * @date 2023-03-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include "Volume.h"

#include "Image.h"

class ThreeDee {
public:

	ThreeDee();

	~ThreeDee();

	unsigned char* Get_XZ_slice(Volume* img, int y);

	unsigned char* Get_YZ_slice(Volume* img, int x);


	

};