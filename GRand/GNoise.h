#ifndef NOISE_H
#define NOISE_H

#include <random>
#include <math.h>

class GNoise{
public:
  	//Noise in the unit of keV
	GNoise(double fF = 0.1, double fOffset = 0.0){
		fFano = fF;
		distribution = std::normal_distribution<double>(fOffset, sqrt(fFano) * GAUSS_DELTA);
	}
  	double fGaussianSampler(double fNoiseFWHM){
  		return (distribution(generator) * GAUSS_DELTA_DIV * fNoiseFWHM * fWidthDiv);
  	}
private:
	double fFano = 0.1;
	double fWidthDiv = 1/2.35;
	const double GAUSS_DELTA = 5.0;
  	const double GAUSS_DELTA_DIV = 1/GAUSS_DELTA;
  	std::default_random_engine generator;
  	std::normal_distribution<double> distribution;
  	
	
};


#endif
