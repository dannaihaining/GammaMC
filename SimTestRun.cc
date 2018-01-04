#include "GSimProcess/GSimProcess.h"
#include "GRand/GRand.h"
#include "GEvent/GEvent.h"
#include "GGeometry/GPoint.h"
#include "GGeometry/GVector.h"
#include "GGeometry/GCuboid.h"
#include "GSource/GSource.h"

#include <iostream>
#include <fstream>

int main(){
	GSimProcess* GammaSim = new GSimProcess();
	srand(time(0));  // Initialize random number generator.
	std::cout << "Gamma sim start" << std::endl;
  	// Load queue with some number of initial events.
  	double fActivity = 1;//1 uCi activity
  	double t=0.0;
  	double tTemp;
  	int nTotalDecay = 0;
  	GPointSource* pPointSource = new GPointSource(0.0,0.0,0.0);
  	GCuboidSource* pCubSource = new GCuboidSource(0.0,0.0,0.0,1.0,1.0,1.0);
  	
  	std::ofstream myfile;
  	myfile.open ("example1.txt");
  
  	while (t<1E5){//0.001 second of simulation
    	//std::cout << "pumping queue with event at time: " << t << "us" << std::endl;
    	//GammaSim->scheduleEvent(new GEmission(t,0.0,0.0,0.0));
    	if(!GRand::RandTime2Decay(fActivity, tTemp)) break;
    	nTotalDecay ++;
    	t+=tTemp;
    	GVector* pVector = pPointSource->GenerateOneRay();
  		myfile<<pVector->gs_Orig.x<<" "<<pVector->gs_Orig.y<<" "<<pVector->gs_Orig.z
  			<<" "<<pVector->fDirX<<" "<<pVector->fDirY<<" "<<pVector->fDirZ<<"\n";
    	delete pVector;
  	}
  	myfile.close();
  	std::cout << "Total decays: " << nTotalDecay << std::endl;
  	
  	t = 0.0;
  	myfile.open ("example2.txt");
  	while (t<1E5){//0.001 second of simulation
    	if(!GRand::RandTime2Decay(fActivity, tTemp)) break;
    	nTotalDecay ++;
    	t+=tTemp;
    	GVector* pVector = pCubSource->GenerateOneRay();
  		myfile<<pVector->gs_Orig.x<<" "<<pVector->gs_Orig.y<<" "<<pVector->gs_Orig.z
  			<<" "<<pVector->fDirX<<" "<<pVector->fDirY<<" "<<pVector->fDirZ<<"\n";
    	delete pVector;
  	}
  	myfile.close();
  	std::cout << "Total decays: " << nTotalDecay << std::endl;
  	
  	
  	// Run the simulation.
  	// GammaSim->run();
  	delete pPointSource;
  	delete pCubSource;
	return 0;
}
