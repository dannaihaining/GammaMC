#include "GPoint.h"

void GPoint::UpdatePoint(double fInX, double fInY, double fInZ){
	fPos[0]=fInX; fPos[1]=fInY; fPos[2]=fInZ;
}
double* GPoint::GetPos(){
	return fPos;
}
