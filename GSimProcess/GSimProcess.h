#ifndef SIM_PROCESS_H
#define SIM_PROCESS_H

#include <queue>
#include "../GEvent/GEvent.h"
#include "../GSpectra/GSpectra.h"
#include "../GGeometry/GCuboid.h"
#include "../GGeometry/GVector.h"
#include "../GSource/GSource.h"

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
	GCuboid* pTempObj1;
  	GPointSource* pPointSource;
  	GSimProcess():time(0.0),eventQueue(){
  		pSpectrum = new GSpectra(1000, 1);
  		pTempObj1 = new GCuboid(-1,-1,1, 1,1,2.5);
  		pPointSource = new GPointSource(0.0,0.0,0.0);
  	}
  	~GSimProcess(){
  		delete pSpectrum;
  		delete pTempObj1;
  		delete pPointSource;
  	}
  	void run();
  	void ScheduleEvent (GEvent * newEvent);
  	void OutputSpectrum();
  	private:
  	double time;
};

#endif
