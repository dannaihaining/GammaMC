#include "GSimProcess.h"
#include <iostream>


void GSimProcess::Run(){
	while (!eventQueue.empty()){
  		GEvent * nextEvent = eventQueue.top();
   		eventQueue.pop();
   		time = nextEvent->time;
   		nextEvent->ProcessEvent(this);
   		delete nextEvent;
	}
}
void GSimProcess::ScheduleEvent (GEvent * newEvent) {
   	eventQueue.push (newEvent);
}
void GSimProcess::OutputSpectrum(){
	pSpectrum->Output("SimEnergySpec.txt");
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
bool GSimProcess::ObjectConstraintTest(){
	if(vecGCuboid.size() <= 1) return true;
	else{
		for(int i=0; i<vecGCuboid.size(); i++){
			for(int j=0; j<vecGCuboid.size(); j++){
				if(i==j) continue;
				double P1[2] = {vecGCuboid[i]->bl.x, vecGCuboid[i]->tr.x};
				double P2[2] = {vecGCuboid[i]->bl.y, vecGCuboid[i]->tr.y}; 
				double P3[2] = {vecGCuboid[i]->bl.z, vecGCuboid[i]->tr.z};
				for(int l=0; l<2; l++){
					for(int m=0; m<2; m++){
						for(int n=0; n<2; n++){
							if((P1[l]-vecGCuboid[j]->bl.x)*(P1[l]-vecGCuboid[j]->tr.x)<0 &&
							(P2[m]-vecGCuboid[j]->bl.x)*(P2[m]-vecGCuboid[j]->tr.x)<0 &&
							(P3[n]-vecGCuboid[j]->bl.x)*(P3[n]-vecGCuboid[j]->tr.x)<0) return false;
						}
					}
				}
			}
		}
	}
	return true;
}
