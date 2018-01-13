#ifndef SIM_PROCESS_H
#define SIM_PROCESS_H

#include <queue>
#include <limits>
#include <utility>      // std::pair, std::make_pair
#include "../GEvent/GEvent.h"
#include "../GSpectra/GSpectra.h"
#include "../GGeometry/GCuboid.h"
#include "../GGeometry/GVector.h"
#include "../GSource/GSource.h"
#include "../GRand/GRand.h"

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
  	std::vector<GCuboid*> vecGCuboid;
  	GSimProcess():time(0.0),eventQueue(){
  		pSpectrum = new GSpectra(1000, 1);
  		pTempObj1 = new GCuboid(-1,-1,1, 1,1,2.5);
  		vecGCuboid.push_back(pTempObj1);
  		pPointSource = new GPointSource(0.0,0.0,0.0);
  	}
  	~GSimProcess(){
  		for(int i=0; i<vecGCuboid.size(); i++) delete vecGCuboid[i];
  		if(vecGCuboid.size()>0) vecGCuboid.erase(vecGCuboid.begin(), vecGCuboid.end());
  		delete pSpectrum;
  		delete pPointSource;
  	}
  	void ReOrderObjects(GVector* pVector);
  	void run();
  	void ScheduleEvent (GEvent * newEvent);
  	void OutputSpectrum();
  	private:
  	double time;
};

#endif
