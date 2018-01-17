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
  	for(unsigned int i=0; i<vecGPtSource.size(); i++){
  		while (t < fTime){//fTime: length(time) of simulation
    		if(!GRand::RandTime2Decay(vecGPtSource[i]->fActivity, tTemp)) break;
    		t+=tTemp;
    		GVector* pVector = vecGPtSource[i]->GenerateOneRay();
  			ScheduleEvent(new GEmission(t,0.0,0.0,0.0, vecGPtSource[i]->fEnergy, pVector));
  		}
  	}
	
}
