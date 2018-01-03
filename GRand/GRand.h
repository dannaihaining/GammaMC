#ifndef RAND_H
#define RAND_H

#include <stdlib.h>     /* srand, rand */

//I should think about better ways of rand number generation
//Should use line: srand(time(0));  // Initialize random number generator.
class GRand{
	public:
  	GRand(){}
  	static int randInt(int n){
  		return rand()%n + 1;
  	}
  	static double randDouble(double fMin, double fMax){
  		double f = (double)rand() / RAND_MAX;
    	return fMin + f * (fMax - fMin);
  	}
};

#endif
