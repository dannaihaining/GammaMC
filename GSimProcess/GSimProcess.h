#ifndef SIM_PROCESS_H
#define SIM_PROCESS_H

#include <queue>
#include "../GEvent/GEvent.h"

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
  	GSimProcess():time(0.0),eventQueue(){}
  	void run(){
  		while (!eventQueue.empty()){
    		GEvent * nextEvent = eventQueue.top();
    		eventQueue.pop();
    		time = nextEvent->time;
    		nextEvent->processEvent();
    		delete nextEvent;
  		}
	}
  	void scheduleEvent (GEvent * newEvent) {
    	eventQueue.push (newEvent);
  	}
  	double time;
};

#endif
