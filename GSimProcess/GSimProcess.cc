#include "GSimProcess.h"
#include <iostream>


void GSimProcess::run(){
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
	for(int i=0; i<vecGCuboid.size(); i++){
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