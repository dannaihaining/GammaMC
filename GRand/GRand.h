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
  		t = -log(1-RandDouble(0,1))/A;
  		return true;
  	}
  	//Uniformly sample the direction on a unit sphere
  	static bool RandSphereDir(double &x, double &y, double &z){
  		double theta = 2*M_PI*RandDouble(0.0, 1.0);
  		double phi = M_PI*RandDouble(0.0, 1.0);
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
};

#endif
