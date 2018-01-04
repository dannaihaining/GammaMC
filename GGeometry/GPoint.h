#ifndef POINT_HEADER  
#define POINT_HEADER

#include <math.h>

struct GPoint{
	double x;
	double y;
	double z;
	GPoint(){
		x=0; y=0; z=0;
	}
	GPoint(double fInX, double fInY, double fInZ){
		x=fInX; y=fInY; z=fInZ;
	}
	void SetPos(double fInX, double fInY, double fInZ){
		x=fInX; y=fInY; z=fInZ;
	}
};


#endif
