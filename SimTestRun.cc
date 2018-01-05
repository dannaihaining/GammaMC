#include "GSimProcess/GSimProcess.h"
#include "GRand/GRand.h"
#include "GEvent/GEvent.h"
#include "GGeometry/GPoint.h"
#include "GGeometry/GVector.h"
#include "GGeometry/GCuboid.h"
#include "GSource/GSource.h"

#include <iostream>
#include <fstream>

//For now I just used the linear attenuation coefficient of CZT at 662 keV. (1/cm)
#define LIN_ATTEN_COEFF 0.41818

int main(){
	GSimProcess* GammaSim = new GSimProcess();
	srand(time(0));  // Initialize random number generator.
	std::cout << "Gamma sim start" << std::endl;
  	// Load queue with some number of initial events.
  	double fActivity = 1;//1 uCi activity
  	double t=0.0;
  	double tTemp;
  	int nTotalDecay = 0;
  	int nInteractions = 0;
  	int nTrespass = 0;
  	GPointSource* pPointSource = new GPointSource(0.0,0.0,0.0);
  	GCuboid* pTempObj = new GCuboid(-1,-1,20, 1,1,21.5);
  	
  	
  	std::ofstream myfile;
  	myfile.open ("example1.txt");
  
  	while (t<1E7){//0.001 second of simulation
    	//std::cout << "pumping queue with event at time: " << t << "us" << std::endl;
    	//GammaSim->scheduleEvent(new GEmission(t,0.0,0.0,0.0));
    	if(!GRand::RandTime2Decay(fActivity, tTemp)) break;
    	nTotalDecay ++;
    	t+=tTemp;
    	GVector* pVector = pPointSource->GenerateOneRay();
//    	myfile<<pVector->gs_Orig.x<<" "<<pVector->gs_Orig.y<<" "<<pVector->gs_Orig.z
// 				<<" "<<pVector->fDirX<<" "<<pVector->fDirY<<" "<<pVector->fDirZ<<"\n";
		double fT1, fT2, fX, fY, fZ;
  		if(pTempObj->IfCollide(pVector, fT1, fT2)){
  			/*
  			pVector->PointOnThis(fT1, fX, fY, fZ);
  			myfile<<fX<<" "<<fY<<" "<<fZ<<" "<<fT1<<" ";
  			pVector->PointOnThis(fT2, fX, fY, fZ);
  			myfile<<fX<<" "<<fY<<" "<<fZ<<" "<<fT2<<"\n";
  			*/
  			nTrespass++;
  			
  			double fZTemp;
  			if(GRand::RandInteractionDepth(LIN_ATTEN_COEFF,fZTemp,1*(fT2-fT1))){
  				myfile<<fZTemp<<"\n";
  				nInteractions++;
  			}
  			
  		}
  			
    	delete pVector;
  	}
  	myfile.close();
  	std::cout << "Total decays: " << nTotalDecay << std::endl;
  	std::cout << "Total trespass: " << nTrespass << std::endl;
  	std::cout << "Total interactions: " << nInteractions << std::endl;
  	
  	
  	
  	
  	// Run the simulation.
  	// GammaSim->run();
  	delete pPointSource;
  	
  	//Cube source
  	/*
  	GCuboidSource* pCubSource = new GCuboidSource(0.0,0.0,0.0,1.0,1.0,1.0);
  	t = 0.0;
  	//myfile.open ("example2.txt");
  	while (t<1E5){//0.001 second of simulation
    	if(!GRand::RandTime2Decay(fActivity, tTemp)) break;
    	nTotalDecay ++;
    	t+=tTemp;
    	GVector* pVector = pCubSource->GenerateOneRay();
  		//myfile<<pVector->gs_Orig.x<<" "<<pVector->gs_Orig.y<<" "<<pVector->gs_Orig.z
  		//	<<" "<<pVector->fDirX<<" "<<pVector->fDirY<<" "<<pVector->fDirZ<<"\n";
    	delete pVector;
  	}
  	//myfile.close();
  	std::cout << "Total decays: " << nTotalDecay << std::endl;
  	delete pCubSource;
  	*/
  	
	return 0;
}
