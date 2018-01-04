#ifndef EVENT_H
#define EVENT_H

#include <iostream>

class GEvent{
	public:
  	// Construct sets time of event.
  	GEvent(double t, double fX, double fY, double fZ):
  		time(t), x(fX), y(fY), z(fZ){}
  	
  	// Execute event by invoking this method.
  	virtual void processEvent() = 0;
  	const double time;
  	const double x,y,z;
};

//Public inheritance is used to allow for casting (from derived class to base class)
class GEmission:public GEvent{
	public:
  	GEmission (double t, double fX, double fY, double fZ)
    	: GEvent(t, fX, fY, fZ){}
  	virtual void processEvent(){
  		//std::cout<<"Emission"<<std::endl;
  	}
	private:
};

class GCompton:public GEvent{
	public:
  	GCompton (double t, double fX, double fY, double fZ)
    	: GEvent(t, fX, fY, fZ){}
  	virtual void processEvent(){
  		std::cout<<"Compton"<<std::endl;
  	}
	private:
};

class GPhotoElec:public GEvent{
	public:
  	GPhotoElec (double t, double fX, double fY, double fZ)
    	: GEvent(t, fX, fY, fZ){}
  	virtual void processEvent(){
  		std::cout<<"PhotoElec"<<std::endl;
  	}
	private:
};

class GPairProd:public GEvent{
	public:
  	GPairProd (double t, double fX, double fY, double fZ)
    	:GEvent(t, fX, fY, fZ){}
  	virtual void processEvent(){
  		std::cout<<"PairProd"<<std::endl;
  	}
	private:
};

#endif
