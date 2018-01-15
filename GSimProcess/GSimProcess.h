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
  	private:
  	double time;
	protected:
  	std::priority_queue<GEvent*,
  		std::vector<GEvent *, std::allocator<GEvent*> >,
        GEventComparator> eventQueue;
	public:
	GSpectra* pSpectrum;
  	GPointSource* pPointSource;
  	std::vector<GCuboid*> vecGCuboid;
  	GSimProcess():time(0.0),eventQueue(){
  		pSpectrum = new GSpectra(1000, 1);
  		/*
  		//First: a detector
  		vecGCuboid.push_back(new GCuboid(-1,-1,1, 1,1,2.5, true));
  		//Second: a large block of CZT between the detector and the source.
  		vecGCuboid.push_back(new GCuboid(-1,-1,0, 1,1,1, false));
  		*/
  		pPointSource = new GPointSource(0.0,0.0,0.0);
  	}
  	~GSimProcess(){
  		for(unsigned int i=0; i<vecGCuboid.size(); i++) delete vecGCuboid[i];
  		if(vecGCuboid.size()>0) vecGCuboid.erase(vecGCuboid.begin(), vecGCuboid.end());
  		delete pSpectrum;
  		delete pPointSource;
  	}
  	void ReOrderObjects(GVector* pVector);
  	void Run();
  	void ScheduleEvent (GEvent * newEvent);
  	void OutputSpectrum();
  	void AddNewObject(GCuboid* pGC);
};

#endif
