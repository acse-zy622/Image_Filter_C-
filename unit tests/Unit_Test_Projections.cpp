#include "Projections.h"

int main(){


	//Unit test for all projection types.
	Volume* v1 = new Volume();
	int w = 3;
	int h = 3;
	int c = 1;
	unsigned char test1[] = {1,7,0,2,5,4,3,23,97};
	unsigned char* t1 = test1;
	Image im(t1, w, h, c);
	v1->addTestImage(im);

	unsigned char test2[] = {2,6,4,3,7,2,9,98,43};
	unsigned char* t2 = test2;
	Image im2(t2, w, h, c);
	v1->addTestImage(im2);

	unsigned char test3[] = { 4,7,3,2,1,93,23,45,12};
	unsigned char* t3 = test3;
	Image im3(t3, w, h, c);
	v1->addTestImage(im3);
    
	Projection proj(v1);
	proj.IP("max", "unit_test.png", 0, 3, "test");

	proj.IP("min", "unit_test.png", 0, 3, "test");

	proj.IP("mean", "unit_test.png", 0, 3, "test");

	proj.IP("median", "unit_test.png", 0, 3, "test");

}