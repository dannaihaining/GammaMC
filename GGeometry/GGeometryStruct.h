#ifndef STRUCT_HEADER  
#define STRUCT_HEADER

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

struct GVector{
	double fDirX;
	double fDirY;
	double fDirZ;
	GPoint gs_Orig;
	GVector(){
		fDirX=1; fDirY=0; fDirZ=0;
	}
	GVector(double fInOrigX, double fInOrigY, double fInOrigZ, double fInDirX, double fInDirY, double fInDirZ){
		gs_Orig.SetPos(fInOrigX, fInOrigY, fInOrigZ);
		fDirX=1; fDirY=0; fDirZ=0;
		double fNorm = sqrt(fInDirX*fInDirX+fInDirY*fInDirY+fInDirZ*fInDirZ);
		if(fNorm!=0){
			fDirX=fInDirX/fNorm;
			fDirY=fInDirY/fNorm;
			fDirZ=fInDirZ/fNorm;
		}
	}
	GVector(GPoint gs_InPoint, double fInDirX, double fInDirY, double fInDirZ){
		gs_Orig.SetPos(gs_InPoint.x, gs_InPoint.y, gs_InPoint.z);
		fDirX=1; fDirY=0; fDirZ=0;
		double fNorm = sqrt(fInDirX*fInDirX+fInDirY*fInDirY+fInDirZ*fInDirZ);
		if(fNorm!=0){
			fDirX=fInDirX/fNorm;
			fDirY=fInDirY/fNorm;
			fDirZ=fInDirZ/fNorm;
		}
	}
	GVector(double fInX, double fInY, double fInZ, bool fSetOrig){
		if(fSetOrig){
			fDirX=1; fDirY=0; fDirZ=0;
			gs_Orig.SetPos(fInX, fInY, fInZ);
		}
		else{
			fDirX=1; fDirY=0; fDirZ=0;
			double fNorm = sqrt(fInX*fInX+fInY*fInY+fInZ*fInZ);
			if(fNorm!=0){
				fDirX=fInX/fNorm;
				fDirY=fInY/fNorm;
				fDirZ=fInZ/fNorm;
			}
		}
	}
	void SetDir(double fInX, double fInY, double fInZ){
		double fNorm = sqrt(fInX*fInX+fInY*fInY+fInZ*fInZ);
		if(fNorm!=0){
			fDirX=fInX/fNorm;
			fDirY=fInY/fNorm;
			fDirZ=fInZ/fNorm;
		}
	}
	void SetOrig(double fInX, double fInY, double fInZ){
		gs_Orig.SetPos(fInX, fInY, fInZ);
	}
};


#endif
