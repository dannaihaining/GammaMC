#ifndef RAND_H
#define RAND_H

#include <stdlib.h>     /* srand, rand */
#include <math.h>       /* log , M_PI */
#include <cmath>		/* sin */
#include "../GGeometry/GPoint.h"


/*
 * Gamma-related random number generators
 */

//I should think about better ways of rand number generation
//Should use line: srand(time(0));  // Initialize random number generator.



class GRand{
	public:
  	GRand(){}
  	static int RandInt(int n){
  		return rand()%n;
  	}
  	static double RandDouble(double fMin, double fMax){
  		double f = (double)rand()/RAND_MAX;
    	return fMin + f*(fMax-fMin);
  	}
  	//CDF of time interval between decays: 1-exp(-A*t).
  	//A: activity (uCi)
  	//t: time (us)
  	static bool RandTime2Decay(double A, double& t){
  		if(A<=0) return false;
  		A *= 3.7E-2; //Convert to average deays per us
  		t = -log(1-RandDouble(0,1.0))/A;
  		return true;
  	}
  	//Uniformly sample the direction on a unit sphere
  	static bool RandSphereDir(double &x, double &y, double &z){
  		double theta = 2*M_PI*RandDouble(0.0, 1.0);
  		double phi = acos(1-2*RandDouble(0.0, 1.0));
  		x = sin(phi) * cos(theta);
  		y = sin(phi) * sin(theta);
  		z = cos(phi);
  		return true;
  	}
  	//Uniformly sample the position within a cuboid
  	static bool RandCuboidUniform(GPoint* bl, GPoint* tr, double &fPosX, double &fPosY, double &fPosZ){
  		fPosX = RandDouble(bl->x, tr->x);
  		fPosY = RandDouble(bl->y, tr->y);
  		fPosZ = RandDouble(bl->z, tr->z);
  		return true;
  	}
  	static bool RandInteractionDepth(double fAttnCoeff, double& z, double fMaxZ=1E7){
  		//fAttnCoeff: unit 1/cm
  		//z: unit cm
		if(fAttnCoeff<=0) return false;
		z = -log(1-RandDouble(0,1.0))/fAttnCoeff;
		if(z>fMaxZ) return false;
  		return true;
  	}
  	static bool RandCircDir(double& fPhi){
  		fPhi = M_PI*RandDouble(-1.0, 1.0);
  		return true;
  	}
  	static bool RandComptonAngle(double fE, double& fTheta, double& fPhi, double &fEs, int nFlag){
  		//Compton angle scatter sampler.
  		//fE: incoming ray energy (MeV)
  		//fEs: secondary gamma ray energy (MeV)
  		//fTheta: polar angle (radian) 0~pi
  		//fPhi: azimuthal angle (radian) -pi~pi
  		//Flag 0: simple rectangular rejection
  		//Flag 1: envelope rejection by Ozmutlu, "Sampling of Angular Distribution in Compton Scattering", 1992
  		return true;
  	}
};

#endif
