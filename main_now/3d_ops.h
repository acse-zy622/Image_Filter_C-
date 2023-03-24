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