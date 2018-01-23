#ifndef SIM_PROCESS_H
#define SIM_PROCESS_H

#include <queue>
#include <limits>
#include <utility>      // std::pair, std::make_pair
#include <chrono>
#include <thread>
#include <math.h>
#include "../GEvent/GEvent.h"
#include "../GSpectra/GSpectra.h"
#include "../GGeometry/GCuboid.h"
#include "../GGeometry/GVector.h"
#include "../GSource/GSource.h"
#include "../GRand/GRand.h"
#include "../GRand/GNoise.h"

struct GEventComparator{
	bool operator() (const GEvent * left, const GEvent * right) const{
    	return left->time > right->time;
  	}
};

class GSimProcess{
  	private:
  	double time;
  	GNoise* pStatNoise;
  	GNoise* pElecNoise;
	GSpectra* pSpectrum;
  	std::vector<GPointSource*> vecGPtSource;
  	std::vector<GCuboid*> vecGCuboid;
  	
	protected:
  	std::priority_queue<GEvent*,
  		std::vector<GEvent *, std::allocator<GEvent*> >,
        GEventComparator> eventQueue;
	
	public:
  	GSimProcess():time(0.0),eventQueue(){
  		pSpectrum = new GSpectra(1000, 1);
  		pStatNoise = new GNoise(0.1, 0.0);
  		pElecNoise = new GNoise(1.0, 0.0);
  		/*
  		//First: a detector
  		vecGCuboid.push_back(new GCuboid(-1,-1,1, 1,1,2.5, true));
  		//Second: a large block of CZT between the detector and the source.
  		vecGCuboid.push_back(new GCuboid(-1,-1,0, 1,1,1, false));
  		*/
  	}
  	~GSimProcess(){
  		for(unsigned int i=0; i<vecGCuboid.size(); i++) delete vecGCuboid[i];
  		if(vecGCuboid.size()>0) vecGCuboid.erase(vecGCuboid.begin(), vecGCuboid.end());
  		for(unsigned int i=0; i<vecGPtSource.size(); i++) delete vecGPtSource[i];
  		if(vecGPtSource.size()>0) vecGPtSource.erase(vecGPtSource.begin(), vecGPtSource.end());
  		delete pSpectrum;
  		delete pStatNoise;
  		delete pElecNoise;
  	}
  	void ReOrderObjects(GVector* pVector);
  	void Run();
  	void ScheduleEvent (GEvent * newEvent);
  	void OutputSpectrum();
  	void Add2Spec(const double fE, const bool bNoise = false);
  	void AddNewSource(GPointSource* pPSource);
  	void AddNewObject(GCuboid* pGC);
  	void PumpDecays(double fTime);
  	bool ObjectConstraintTest();
};

#endif
