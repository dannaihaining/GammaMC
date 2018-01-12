#ifndef EVENT_H
#define EVENT_H

#include <iostream>

class GSimProcess; //Forward declaration. Some people do not like it!

class GEvent{
	public:
  	// Construct sets time of event.
  	GEvent(double t, double fX, double fY, double fZ, double fE):
  		time(t), x(fX), y(fY), z(fZ), E(fE){}
  	
  	// Execute event by invoking this method.
  	virtual void ProcessEvent(GSimProcess* pGProc) = 0;
  	const double time, E;
  	const double x,y,z;
};

//Public inheritance is used to allow for casting (from derived class to base class)
class GEmission:public GEvent{
	public:
  	GEmission (double t, double fX, double fY, double fZ, double fE)
    	: GEvent(t, fX, fY, fZ, fE){}
  	virtual void ProcessEvent(GSimProcess* pGProc);
	private:
};

class GCompton:public GEvent{
	public:
  	GCompton (double t, double fX, double fY, double fZ, double fE)
    	: GEvent(t, fX, fY, fZ, fE){}
  	virtual void ProcessEvent(GSimProcess* pGProc);
	private:
};

class GPhotoElec:public GEvent{
	public:
  	GPhotoElec (double t, double fX, double fY, double fZ, double fE)
    	: GEvent(t, fX, fY, fZ, fE){}
  	virtual void ProcessEvent(GSimProcess* pGProc);
	private:
};

class GPairProd:public GEvent{
	public:
  	GPairProd (double t, double fX, double fY, double fZ, double fE)
    	:GEvent(t, fX, fY, fZ, fE){}
  	virtual void ProcessEvent(GSimProcess* pGProc);
	private:
};

#endif
