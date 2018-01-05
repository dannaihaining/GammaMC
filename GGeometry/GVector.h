#ifndef VECTOR_HEADER  
#define VECTOR_HEADER

#include <math.h>

struct GVector{
	double fDirX;
	double fDirY;
	double fDirZ;
	double fDirFracX;
	double fDirFracY;
	double fDirFracZ;
	GPoint gs_Orig;
	GVector(){
		fDirX=1; fDirY=0; fDirZ=0;
		fDirFracX=1.0/fDirX;
		fDirFracY=1.0/fDirY;
		fDirFracZ=1.0/fDirZ;
	}
	GVector(double fInOrigX, double fInOrigY, double fInOrigZ, double fInDirX, double fInDirY, double fInDirZ){
		gs_Orig.SetPos(fInOrigX, fInOrigY, fInOrigZ);
		fDirX=1; fDirY=0; fDirZ=0;
		double fNorm = sqrt(fInDirX*fInDirX+fInDirY*fInDirY+fInDirZ*fInDirZ);
		if(fNorm!=0){
			fDirX=fInDirX/fNorm;
			fDirY=fInDirY/fNorm;
			fDirZ=fInDirZ/fNorm;
			fDirFracX=1.0/fDirX;
			fDirFracY=1.0/fDirY;
			fDirFracZ=1.0/fDirZ;
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
			fDirFracX=1.0/fDirX;
			fDirFracY=1.0/fDirY;
			fDirFracZ=1.0/fDirZ;
		}
	}
	GVector(double fInX, double fInY, double fInZ, bool fSetOrig){
		if(fSetOrig){
			fDirX=1; fDirY=0; fDirZ=0;
			fDirFracX=1.0/fDirX;
			fDirFracY=1.0/fDirY;
			fDirFracZ=1.0/fDirZ;
			gs_Orig.SetPos(fInX, fInY, fInZ);
		}
		else{
			fDirX=1; fDirY=0; fDirZ=0;
			double fNorm = sqrt(fInX*fInX+fInY*fInY+fInZ*fInZ);
			if(fNorm!=0){
				fDirX=fInX/fNorm;
				fDirY=fInY/fNorm;
				fDirZ=fInZ/fNorm;
				fDirFracX=1.0/fDirX;
				fDirFracY=1.0/fDirY;
				fDirFracZ=1.0/fDirZ;
			}
		}
	}
	void SetDir(double fInX, double fInY, double fInZ){
		double fNorm = sqrt(fInX*fInX+fInY*fInY+fInZ*fInZ);
		if(fNorm!=0){
			fDirX=fInX/fNorm;
			fDirY=fInY/fNorm;
			fDirZ=fInZ/fNorm;
			fDirFracX=1.0/fDirX;
			fDirFracY=1.0/fDirY;
			fDirFracZ=1.0/fDirZ;
		}
	}
	void SetOrig(double fInX, double fInY, double fInZ){
		gs_Orig.SetPos(fInX, fInY, fInZ);
	}
	void PointOnThis(double t, double& x, double& y, double& z){
		x = t*fDirX + gs_Orig.x;
		y = t*fDirY + gs_Orig.y;
		z = t*fDirZ + gs_Orig.z;
	}
};


#endif
