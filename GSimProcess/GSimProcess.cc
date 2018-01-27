#include "GSimProcess.h"
#include <iostream>
#include <sstream>

void GSimProcess::ThreadStartRun(int nThread){
	vecThrSim_.push_back(std::thread(&GSimProcess::Run, this, nThread));
}

void GSimProcess::ThreadWaitTillFinish(){
	for(unsigned int i=0; i<vecThrSim_.size(); ++i) if(vecThrSim_[i].joinable()) vecThrSim_[i].join();
}

void GSimProcess::Run(int nThread){
	
	///////////
	//Progress bar
	//int nMaxSize = eventQueue.size();
	int nMaxSize = vec_EventQueue[nThread].size();
	int nProcessed = 0;
	int nBarWidth = 70;
  	int nProgPos = 0.0;
  	double fProgress = 0.0;
  	int nCt = 0.0;
	////////////////
	
	/*
	while (!eventQueue.empty()){
  		GEvent * nextEvent = eventQueue.top();
   		eventQueue.pop();*/
   	while (!vec_EventQueue[nThread].empty()){
  		GEvent * nextEvent = vec_EventQueue[nThread].top();
   		vec_EventQueue[nThread].pop();
   		time = nextEvent->time;
   		nextEvent->ProcessEvent(this, nThread);
   		delete nextEvent;
   		
   		///////////
		//Progress bar
		if(nThread>0) continue;
		//if(eventQueue.size()==0) break;
		if(vec_EventQueue[nThread].size()==0) break;
		nProcessed ++;
		nCt ++;
		//if(eventQueue.size()>nMaxSize) nMaxSize = eventQueue.size();
		if(vec_EventQueue[nThread].size()>nMaxSize) nMaxSize = vec_EventQueue[nThread].size();
  		fProgress = (double)nProcessed/nMaxSize;
  		if(fProgress>1.0) fProgress = 1.0;
  		if((double)nCt/nMaxSize>0.05){
  			nProgPos = fProgress*nBarWidth;
  			std::cout << "[";
  			for (int i = 0; i < nBarWidth; ++i) {
        		if (i < nProgPos) std::cout << "=";
        		else if (i == nProgPos) std::cout << ">";
        		else std::cout << " ";
    		}
    		std::cout << "] " << int(fProgress * 100.0) << " %\r";
    		std::cout.flush();
  			nCt=0;
  			
  			//Update the spectrum every 5 percent
  			//this->OutputSpectrum(nThread);
  		}
  		//////////
   		
	}
	///////////
	//Progress bar
	std::cout << std::endl;
	/////////////
}
void GSimProcess::ScheduleEvent (GEvent * newEvent, int nThread) {
   	//eventQueue.push (newEvent);
   	if(nThread>=vec_EventQueue.size()) nThread = 0;
   	vec_EventQueue[nThread].push (newEvent);
}
void GSimProcess::OutputSpectrum(int nThread){
	
	//Declare a unique_lock object and lock the mutex object.
	//Block the thread if the lock is owned by other threads.
    std::unique_lock<std::mutex> lock(mx_);
    
	std::ostringstream oss;
	oss << "Spectrum_Thread"<< nThread <<".txt";
	vecGSpec[nThread]->Output(oss.str());
}
//Sort the objects based on whichever is first entered by the vector.
void GSimProcess::ReOrderObjects(GVector* pVector){
	//Declare a unique_lock object and lock the mutex object.
	//Block the thread if the lock is owned by other threads.
    std::unique_lock<std::mutex> lock(mx_);
    
	std::vector<std::pair<double, GCuboid*>> pPairVec;
	double fT1, fT2;
	for(unsigned int i=0; i<vecGCuboid.size(); i++){
		if(vecGCuboid[i]->IfCollide(pVector, fT1, fT2)){
			pPairVec.push_back(std::make_pair(fT1, vecGCuboid[i]));
		}
		else{
			pPairVec.push_back(std::make_pair(std::numeric_limits<double>::max(), vecGCuboid[i]));
		}	
	}
	sort(pPairVec.begin(), pPairVec.end());
	for(int i=0; i<vecGCuboid.size(); i++)
		vecGCuboid[i] = pPairVec[i].second;
}
void GSimProcess::AddNewSource(GPointSource* pPSource){
	vecGPtSource.push_back(pPSource);
}
void GSimProcess::AddNewObject(GCuboid* pGC){
	vecGCuboid.push_back(pGC);
}
void GSimProcess::AddNewSpectrum(GSpectra* pSpec){
	pSpec->Clear();
	vecGSpec.push_back(pSpec);
}
void GSimProcess::PumpDecays(double fTime, int nThread){
	//double fActivity = 1;//1 uCi activity
  	double t=0.0;
  	double tTemp;
  	
  	//////////////
  	//Progress bar
  	int nBarWidth = 70;
  	int nProgPos = 0.0;
  	double fProgress = 0.0;
  	double fCt = 0.0;
  	///////////////////
  	
  	for(unsigned int i=0; i<vecGPtSource.size(); i++){
  		
  		std::cout << "Source " << (i+1) << " emitting ..." << std::endl;
  		
  		while (t < fTime){//fTime: length(time) of simulation
    		if(!GRand::RandTime2Decay(vecGPtSource[i]->fActivity, tTemp)) break;
    		t+=tTemp;
    		GVector* pVector = vecGPtSource[i]->GenerateOneRay();
  			ScheduleEvent(new GEmission(t,0.0,0.0,0.0, vecGPtSource[i]->fEnergy, pVector), nThread);

			///////////
			//Progress bar
  			fProgress = t/fTime;
  			nProgPos = fProgress*nBarWidth;
  			fCt += tTemp/fTime;
  			if(fCt>0.05){
  				std::cout << "[";
  				for (int i = 0; i < nBarWidth; ++i) {
        			if (i < nProgPos) std::cout << "=";
        			else if (i == nProgPos) std::cout << ">";
        			else std::cout << " ";
    			}
    			std::cout << "] " << int(fProgress * 100.0) << " %\r";
    			std::cout.flush();
  				fCt=0.0;
  			}
  			//////////
  		}
  		std::cout << std::endl;
	}
}

void GSimProcess::Add2Spec(const double fE, int nThread, const bool bNoise){
	//fE unit: keV
	//Declare a unique_lock object and lock the mutex object.
	//Block the thread if the lock is owned by other threads.
    std::unique_lock<std::mutex> lock(mx_);
    
	if(nThread>=vecGSpec.size()) nThread = 0;
	if(!bNoise) vecGSpec[nThread]->AddOneEvent(fE);
	else vecGSpec[nThread]->AddOneEvent(fE + pStatNoise->fGaussianSampler( 2.35*sqrt(fE * 0.005) ) + pElecNoise->fGaussianSampler( 1.4 ));
}

void GSimProcess::ResetNoiseE(const double fNoiseE){
	delete pElecNoise;
	pElecNoise = new GNoise(fNoiseE, 0.0);
}

bool GSimProcess::ObjectConstraintTest(){
	std::cout<< "Testing" <<std::endl;
	if(vecGCuboid.size() <= 1) return true;
	else{
		for(int i=0; i<vecGCuboid.size(); i++){
			for(int j=0; j<vecGCuboid.size(); j++){
				if(i==j) continue;
				double P1[2] = {vecGCuboid[i]->bl.x, vecGCuboid[i]->tr.x};
				double P2[2] = {vecGCuboid[i]->bl.y, vecGCuboid[i]->tr.y}; 
				double P3[2] = {vecGCuboid[i]->bl.z, vecGCuboid[i]->tr.z};
				if((P1[0]/2+P1[1]/2-vecGCuboid[j]->bl.x)*(P1[0]/2+P1[1]/2-vecGCuboid[j]->tr.x)<0 &&
					(P2[0]/2+P2[1]/2-vecGCuboid[j]->bl.y)*(P2[0]/2+P2[1]/2-vecGCuboid[j]->tr.y)<0 &&
					(P3[0]/2+P3[1]/2-vecGCuboid[j]->bl.z)*(P3[0]/2+P3[1]/2-vecGCuboid[j]->tr.z)<0) return false;
				for(int l=0; l<2; l++){
					for(int m=0; m<2; m++){
						for(int n=0; n<2; n++){
							if((P1[l]-vecGCuboid[j]->bl.x)*(P1[l]-vecGCuboid[j]->tr.x)<0 &&
							(P2[m]-vecGCuboid[j]->bl.y)*(P2[m]-vecGCuboid[j]->tr.y)<0 &&
							(P3[n]-vecGCuboid[j]->bl.z)*(P3[n]-vecGCuboid[j]->tr.z)<0) return false;
						}
					}
				}
				for(int l=0; l<2; l++){
					if((P1[l]-vecGCuboid[j]->bl.x)*(P1[l]-vecGCuboid[j]->tr.x)<0 &&
					(P2[0]/2+P2[1]/2-vecGCuboid[j]->bl.y)*(P2[0]/2+P2[1]/2-vecGCuboid[j]->tr.y)<0 &&
					(P3[0]/2+P3[1]/2-vecGCuboid[j]->bl.z)*(P3[0]/2+P3[1]/2-vecGCuboid[j]->tr.z)<0) return false;
					if((P2[l]-vecGCuboid[j]->bl.x)*(P2[l]-vecGCuboid[j]->tr.x)<0 &&
					(P1[0]/2+P1[1]/2-vecGCuboid[j]->bl.y)*(P1[0]/2+P1[1]/2-vecGCuboid[j]->tr.y)<0 &&
					(P3[0]/2+P3[1]/2-vecGCuboid[j]->bl.z)*(P3[0]/2+P3[1]/2-vecGCuboid[j]->tr.z)<0) return false;
					if((P3[l]-vecGCuboid[j]->bl.x)*(P3[l]-vecGCuboid[j]->tr.x)<0 &&
					(P2[0]/2+P2[1]/2-vecGCuboid[j]->bl.y)*(P2[0]/2+P2[1]/2-vecGCuboid[j]->tr.y)<0 &&
					(P1[0]/2+P1[1]/2-vecGCuboid[j]->bl.z)*(P1[0]/2+P1[1]/2-vecGCuboid[j]->tr.z)<0) return false;
				}
			}
		}
	}
	return true;
}
