#include "GSimProcess.h"



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
