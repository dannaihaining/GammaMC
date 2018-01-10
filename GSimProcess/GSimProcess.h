#ifndef SIM_PROCESS_H
#define SIM_PROCESS_H

#include <queue>
#include "../GEvent/GEvent.h"
#include "../GSpectra/GSpectra.h"

struct GEventComparator{
	bool operator() (const GEvent * left, const GEvent * right) const{
    	return left->time > right->time;
  	}
};

class GSimProcess{
	protected:
  	std::priority_queue<GEvent*,
  		std::vector<GEvent *, std::allocator<GEvent*> >,
        GEventComparator> eventQueue;
	public:
	GSpectra* pSpectrum;
  	GSimProcess():time(0.0),eventQueue(){
  		pSpectrum = new GSpectra(1000, 1);
  	}
  	~GSimProcess(){
  		delete pSpectrum;
  	}
  	void run(){
  		while (!eventQueue.empty()){
    		GEvent * nextEvent = eventQueue.top();
    		eventQueue.pop();
    		time = nextEvent->time;
    		nextEvent->processEvent(pSpectrum);
    		delete nextEvent;
  		}
	}
  	void ScheduleEvent (GEvent * newEvent) {
    	eventQueue.push (newEvent);
  	}
  	void OutputSpectrum(){
  		pSpectrum->Output("SimEnergySpec.txt");
  	}
  	double time;
};

#endif
