#ifndef EVENT_H
#define EVENT_H

#include <iostream>

class GEvent{
	public:
  	// Construct sets time of event.
  	GEvent(double t) : time(t){}
  	// Execute event by invoking this method.
  	virtual void processEvent() = 0;
  	const double time;
};

//Public inheritance is used to allow for casting (from derived class to base class)
class GEmission:public GEvent{
	public:
  	GEmission (double t)
    	: GEvent(t){}
  	virtual void processEvent(){
  		//std::cout<<"Emission"<<std::endl;
  	}
	private:
};

class GCompton:public GEvent{
	public:
  	GCompton (double t)
    	: GEvent(t){}
  	virtual void processEvent(){
  		std::cout<<"Compton"<<std::endl;
  	}
	private:
};

class GPhotoElec:public GEvent{
	public:
  	GPhotoElec (double t)
    	: GEvent(t){}
  	virtual void processEvent(){
  		std::cout<<"PhotoElec"<<std::endl;
  	}
	private:
};

class GPairProd:public GEvent{
	public:
  	GPairProd (double t)
    	:GEvent(t){}
  	virtual void processEvent(){
  		std::cout<<"PairProd"<<std::endl;
  	}
	private:
};

#endif
