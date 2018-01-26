#include "GSimProcess.h"
#include <iostream>
#include <sstream>

void GSimProcess::Run(){
	
	///////////
	//Progress bar
	int nMaxSize = eventQueue.size();
	int nProcessed = 0;
	int nBarWidth = 70;
  	int nProgPos = 0.0;
  	double fProgress = 0.0;
  	int nCt = 0.0;
	////////////////
	
	while (!eventQueue.empty()){
  		GEvent * nextEvent = eventQueue.top();
   		eventQueue.pop();
   		time = nextEvent->time;
   		nextEvent->ProcessEvent(this);
   		delete nextEvent;
   		
		
   		///////////
		//Progress bar
		if(eventQueue.size()==0) break;
		nProcessed ++;
		nCt ++;
		if(eventQueue.size()>nMaxSize) nMaxSize = eventQueue.size();
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
  		}
  		//////////
   		
	}
	///////////
	//Progress bar
	std::cout << std::endl;
	/////////////
}
void GSimProcess::ScheduleEvent (GEvent * newEvent) {
   	eventQueue.push (newEvent);
}
void GSimProcess::OutputSpectrum(){
	for(unsigned int i=0; i<vecGSpec.size(); i++){
		std::ostringstream oss;
		oss << "Spectrum_Detector" << i <<".txt";
		vecGSpec[i]->Output(oss.str());
	}
}
//Sort the objects based on whichever is first entered by the vector.
void GSimProcess::ReOrderObjects(GVector* pVector){
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
	vecGSpec.push_back(pSpec);
}
void GSimProcess::PumpDecays(double fTime){
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
  			ScheduleEvent(new GEmission(t,0.0,0.0,0.0, vecGPtSource[i]->fEnergy, pVector));

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

void GSimProcess::Add2Spec(const double fE, const bool bNoise){
	//fE unit: keV
	if(!bNoise) vecGSpec[0]->AddOneEvent(fE);
	else vecGSpec[0]->AddOneEvent(fE + pStatNoise->fGaussianSampler( 2.35*sqrt(fE * 0.005) ) + pElecNoise->fGaussianSampler( 1.4 ));
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
