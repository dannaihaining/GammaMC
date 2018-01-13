#ifndef EVENT_H
#define EVENT_H

#include <iostream>

//Coefficient to convert distance (cm) in CZT to time of flight (us)
#define Z2T_COEFF 9.133E-5 

class GSimProcess; //Forward declaration. Some people do not like it!

class GEvent{
	public:
  	// Construct sets time of event.
  	GEvent(double t, double fX, double fY, double fZ, double fE, bool IsInDetector=false):
  		time(t), x(fX), y(fY), z(fZ), E(fE), bInDetector(IsInDetector){}
  	
  	// Execute event by invoking this method.
  	virtual void ProcessEvent(GSimProcess* pGProc) = 0;
  	const double time, E;
  	const double x,y,z;
  	const bool bInDetector;
};

//Public inheritance is used to allow for casting (from derived class to base class)
class GEmission:public GEvent{
	public:
  	GEmission (double t, double fX, double fY, double fZ, double fE, bool IsInDetector=false)
    	: GEvent(t, fX, fY, fZ, fE, IsInDetector){}
  	virtual void ProcessEvent(GSimProcess* pGProc);
	private:
};

class GCompton:public GEvent{
	public:
  	GCompton (double t, double fX, double fY, double fZ, double fE, bool IsInDetector=false)
    	: GEvent(t, fX, fY, fZ, fE, IsInDetector){}
  	virtual void ProcessEvent(GSimProcess* pGProc);
	private:
};

class GPhotoElec:public GEvent{
	public:
  	GPhotoElec (double t, double fX, double fY, double fZ, double fE, bool IsInDetector=false)
    	: GEvent(t, fX, fY, fZ, fE, IsInDetector){}
  	virtual void ProcessEvent(GSimProcess* pGProc);
	private:
};

class GPairProd:public GEvent{
	public:
  	GPairProd (double t, double fX, double fY, double fZ, double fE, bool IsInDetector=false)
    	:GEvent(t, fX, fY, fZ, fE, IsInDetector){}
  	virtual void ProcessEvent(GSimProcess* pGProc);
	private:
};

#endif
