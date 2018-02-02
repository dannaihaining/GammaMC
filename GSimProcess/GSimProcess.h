#ifndef SIM_PROCESS_H
#define SIM_PROCESS_H

#include <queue>
#include <limits>
#include <utility>      // std::pair, std::make_pair
#include <chrono>
#include <thread>
#include <math.h>
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <mutex>
#include <condition_variable>
#include "../GEvent/GEvent.h"
#include "../GSpectra/GSpectra.h"
#include "../GGeometry/GCuboid.h"
#include "../GGeometry/GVector.h"
#include "../GSource/GSource.h"
#include "../GRand/GRand.h"
#include "../GRand/GNoise.h"
#include "../GEventsFile/GEventsFile.h"

struct GEventComparator{
	bool operator() (const GEvent * left, const GEvent * right) const{
    	return left->time > right->time;
  	}
};

class GSimProcess{
  	private:
  	double time;
  	GNoise* pStatNoise = nullptr;
  	GNoise* pElecNoise = nullptr;
	std::vector<GSpectra*> vecGSpec;
	std::vector<GEventsFile*> vecGEvtFile;
	
  	std::vector<std::thread> vecThrSim_;
  	std::mutex mx_;
	std::condition_variable cond_;
	
	protected:
  	/*
  	std::priority_queue<GEvent*,
  		std::vector<GEvent *, std::allocator<GEvent*> >,
        GEventComparator> eventQueue;
        */
      
	
	public:
	std::vector<std::priority_queue<GEvent*,
  		std::vector<GEvent *, std::allocator<GEvent*> >,
        GEventComparator>> vec_EventQueue;  
	
		
  	std::vector<GPointSource*> vecGPtSource;
  	//I use a separate vector of Objects because different threads sorting seem to cause significant overhead.
  	std::vector<std::vector<GCuboid*>> vecGCuboid;
  	//std::vector<GCuboid*> vecGCuboid;
  	//GSimProcess():time(0.0),eventQueue(){
  	GSimProcess():time(0.0),vec_EventQueue(){
  		//pSpectrum = new GSpectra(1000, 1);
  		pStatNoise = new GNoise(0.1, 0.0);
  		pElecNoise = new GNoise(1.0, 0.0);
  	}
  	~GSimProcess(){
  		for(unsigned int j=0; j<vecGCuboid.size(); ++j){
  			for(unsigned int i=0; i<vecGCuboid[j].size(); i++) delete vecGCuboid[j][i];
  			if(vecGCuboid[j].size()>0) vecGCuboid[j].erase(vecGCuboid[j].begin(), vecGCuboid[j].end());
  		}
  		if(vecGCuboid.size()>0) vecGCuboid.erase(vecGCuboid.begin(), vecGCuboid.end());
  		
  		//for(unsigned int i=0; i<vecGCuboid.size(); i++) delete vecGCuboid[i];
  		//if(vecGCuboid.size()>0) vecGCuboid.erase(vecGCuboid.begin(), vecGCuboid.end());
  		for(unsigned int i=0; i<vecGPtSource.size(); i++) delete vecGPtSource[i];
  		if(vecGPtSource.size()>0) vecGPtSource.erase(vecGPtSource.begin(), vecGPtSource.end());
		
  		for(unsigned int i=0; i<vecGSpec.size(); i++){
  			delete vecGSpec[i];	
  		}
  		if(vecGSpec.size()>0) vecGSpec.erase(vecGSpec.begin(), vecGSpec.end());
  		for(unsigned int i=0; i<vecGEvtFile.size(); i++){
  			delete vecGEvtFile[i];	
  		}
  		if(vecGEvtFile.size()>0) vecGEvtFile.erase(vecGEvtFile.begin(), vecGEvtFile.end());
  		//delete pSpectrum;
  		if(!pStatNoise) delete pStatNoise;
  		if(!pElecNoise) delete pElecNoise;
  	}
  	//void ReOrderObjects(GVector* pVector);
  	void ReOrderObjects(GVector* pVector, int nThread);
  	void Run(int nThread);
  	void ThreadStartRun(int nThread);
  	void ThreadWaitTillFinish();
  	void ScheduleEvent (GEvent * newEvent, int nThread);
  	void OutputSpectrum(int nThread);
  	void RecordEvent(const double E, const double x, const double y, const double z, const double time, int nThread=0, const bool bNoise = false);
  	void AddNewSource(GPointSource* pPSource);
  	void AddNewObject(GCuboid* pGC);
  	void AddNewSpectrum(GSpectra* pSpec);
  	void AddNewEventsFile(GEventsFile* pEventsFile);
  	void PumpDecays(double fTime, int nThread);
  	void ResetNoiseE(const double fNoiseE);
  	bool ObjectConstraintTest();
  	int nRecordOption = 0;
};

#endif
