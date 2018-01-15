#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include "../GSource/GSource.h"

//Coefficient to convert distance (cm) in CZT to time of flight (us)
#define Z2T_COEFF 9.133E-5 

class GSimProcess; //Forward declaration. Some people do not like it!

class GEvent{
	public:
  	// Construct sets time of event.
  	GEvent(double t, double fX, double fY, double fZ, double fE):
  		time(t), x(fX), y(fY), z(fZ), E(fE){}
  	
  	// Execute event by invoking this method.
  	virtual void ProcessEvent(GSimProcess* pGProc) = 0;
  	const double time,x,y,z,E;
};

//Public inheritance is used to allow for casting (from derived class to base class)
class GEmission:public GEvent{
	public:
  	//GEmission (double t, double fX, double fY, double fZ, double fE, bool IsInDetector=false, bool bIfScattered = false, GVector* pInVector = nullptr)
  	GEmission (double t, double fX, double fY, double fZ, double fE, GVector* pInVector = nullptr)
    	: GEvent(t, fX, fY, fZ, fE){
    		pPointSource = new GPointSource(fX, fY, fZ, fE);
    		//bScattered = bIfScattered;
    		//if(bScattered) pVector = pInVector;
    		pVector = pInVector;
    	}
    ~GEmission(){
    	delete pPointSource;
		delete pVector;
    }
  	virtual void ProcessEvent(GSimProcess* pGProc);
	private:
	GPointSource* pPointSource = nullptr;
	//bool bScattered;
	GVector* pVector = nullptr;
};

class GCompton:public GEvent{
	public:
  	GCompton (double t, double fX, double fY, double fZ, double fE, bool IsInDetector=false)
    	: GEvent(t, fX, fY, fZ, fE), bInDetector(IsInDetector){}
  	virtual void ProcessEvent(GSimProcess* pGProc);
	private:
  	const bool bInDetector;
};

class GPhotoElec:public GEvent{
	public:
  	GPhotoElec (double t, double fX, double fY, double fZ, double fE, bool IsInDetector=false)
    	: GEvent(t, fX, fY, fZ, fE), bInDetector(IsInDetector){}
  	virtual void ProcessEvent(GSimProcess* pGProc);
	private:
  	const bool bInDetector;
};

class GPairProd:public GEvent{
	public:
  	GPairProd (double t, double fX, double fY, double fZ, double fE, bool IsInDetector=false)
    	:GEvent(t, fX, fY, fZ, fE), bInDetector(IsInDetector){}
  	virtual void ProcessEvent(GSimProcess* pGProc);
	private:
  	const bool bInDetector;
};

#endif
