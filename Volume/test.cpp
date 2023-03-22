#include "Projections.h"

int main(){

	// All images, volumes and projections can be defined here.

	Volume* v1 = new Volume();
	v1->addImageFolder("Scans/fracture");
	Projection proj(v1);
	proj.IP("max", "test_output.png",0, v1->get_size());
	delete v1;

}