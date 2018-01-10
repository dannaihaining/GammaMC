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
  	static bool RandComptonAngle(double fE, double& fDirX, double& fDirY, double &fDirZ, double &fEs, double& fTheta, double &fPhi, int nFlag){
  		//double fTheta, fPhi;
  		//Compton angle scatter sampler.
  		//fE: incoming ray energy (MeV)
  		//fEs: secondary gamma ray energy (MeV)
  		//fTheta: polar angle (radian) 0~pi
  		//fPhi: azimuthal angle (radian) -pi~pi
  		if(!RandCircDir(fPhi)) return false;
  		bool bSuccess = false;
  		switch(nFlag){
  			//Sample cos(theta)
  			//Flag 0: simple rectangular rejection
  			case 0: {
  				while(!bSuccess){
  					fTheta = RandDouble(0.0, M_PI);
  					bSuccess = RandDouble(0.0, 2.0) <= RelDiffCrossSecCompton(fE, cos(fTheta));
  				}
  				fEs = fE/(1+fE/E_EC*(1-cos(fTheta)));
  				fDirX = sin(fPhi) * cos(fTheta);
  				fDirY = sin(fPhi) * sin(fTheta);
  				fDirZ = cos(fPhi);
  			}
  			//Flag 1: envelope rejection by Ozmutlu, "Sampling of Angular Distribution in Compton Scattering", 1992
  			case 1: {
  				double fNormE = fE/E_EC;
  				double c = 2*(2*fNormE*fNormE+2*fNormE+1)/(2*fNormE+1)/(2*fNormE+1)/(2*fNormE+1);
  				double b = (1+c/2)/(1-c/2);
  				double a = 2*(b-1);
  				//The envelope function is h = a/(b-x).
  				//Integration from -1 to 1: Integral(h) = -a*log(b-x).
  			}
  			default: return false;
  		}
  		return true;
  	}
  	private:
  	//In C++11, the following data members may be initialized in class declaration:
  	//non-static members
  	//static constexpre members
  	//static const memebers for integral or enumeration (float??) type ONLY.
  	static constexpr double E_EC = 0.511;//static mass energy of electron (MeV)
  	static double RelDiffCrossSecCompton(double fE, double fCosTheta){
  		//RELATIVE Klein Nishina differential cross section.
  		//The maximum number in this equation is 2.
  		double fNormE = fE/E_EC;
  		double fTemp1 = fNormE*(1-fCosTheta);
  		double fTemp2 = 1/(1+fTemp1);
  		double fDiffCS = (1 + fCosTheta*fCosTheta + fTemp1*fTemp1*fTemp2)
  			*fTemp2*fTemp2;
  		return fDiffCS;
  	}
};

#endif
