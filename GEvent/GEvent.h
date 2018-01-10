#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include "../GRand/GRand.h"
#include "../GSpectra/GSpectra.h"

class GEvent{
	public:
  	// Construct sets time of event.
  	GEvent(double t, double fX, double fY, double fZ, double fE):
  		time(t), x(fX), y(fY), z(fZ), E(fE){}
  	
  	// Execute event by invoking this method.
  	virtual void processEvent(GSpectra* pSpectrum) = 0;
  	const double time, E;
  	const double x,y,z;
};

//Public inheritance is used to allow for casting (from derived class to base class)
class GEmission:public GEvent{
	public:
  	GEmission (double t, double fX, double fY, double fZ, double fE)
    	: GEvent(t, fX, fY, fZ, fE){}
  	virtual void processEvent(GSpectra* pSpectrum){
  		//std::cout<<"Emission"<<std::endl;
  	}
	private:
};

class GCompton:public GEvent{
	public:
  	GCompton (double t, double fX, double fY, double fZ, double fE)
    	: GEvent(t, fX, fY, fZ, fE){}
  	virtual void processEvent(GSpectra* pSpectrum){
  		double fX1, fY1, fZ1, fEs, fTheta, fPhi;
  		GRand::RandComptonAngle(E, fX1, fY1, fZ1, fEs, fTheta, fPhi, 0);
  		pSpectrum->AddOneEvent(1000*(E-fEs));
  	}
	private:
};

class GPhotoElec:public GEvent{
	public:
  	GPhotoElec (double t, double fX, double fY, double fZ, double fE)
    	: GEvent(t, fX, fY, fZ, fE){}
  	virtual void processEvent(GSpectra* pSpectrum){
  		pSpectrum->AddOneEvent(1000*E);
  	}
	private:
};

class GPairProd:public GEvent{
	public:
  	GPairProd (double t, double fX, double fY, double fZ, double fE)
    	:GEvent(t, fX, fY, fZ, fE){}
  	virtual void processEvent(GSpectra* pSpectrum){
  		//To be added
  	}
	private:
};

#endif
