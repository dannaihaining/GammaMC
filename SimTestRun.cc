#include "GSimProcess/GSimProcess.h"

/*
#include "GRand/GRand.h"
#include "GEvent/GEvent.h"
#include "GGeometry/GPoint.h"
#include "GGeometry/GVector.h"
#include "GGeometry/GCuboid.h"
#include "GSource/GSource.h"
#include "GSpectra/GSpectra.h"
*/
#include <iostream>
#include <fstream>


//For now I just used the linear attenuation coefficient of CZT at 662 keV. (1/cm)
/*
#define DENSITY 5.8
#define E_THR 10
int nENum_1 = 7;
double fEnergy_1[7] = {0.01, 0.05, 0.1, 0.2, 0.4, 0.5, 0.662};
double fCS_Compton_1[7] = {0.06, 0.11, 0.1103, 0.09715, 0.07803, 0.07164, 0.0638};
double fCS_PP_1[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double fCS_PE_1[7] = {135.4, 10.24, 1.463, 0.1994, 0.02917, 0.01641, 0.008302};

void GetAtten_All_1(double fE, double& fCS_C, double& fCS_P, double& fCS_E){
	if(fE<=fEnergy_1[0]){
		fCS_C = fCS_Compton_1[0];
		fCS_P = fCS_PP_1[0];
		fCS_E = fCS_PE_1[0];
		return;
	}
	if(fE>=fEnergy_1[nENum_1-1]){
		fCS_C = fCS_Compton_1[nENum_1-1];
		fCS_P = fCS_PP_1[nENum_1-1];
		fCS_E = fCS_PE_1[nENum_1-1];
		return;
	}
	int i=0;
	while(fE>fEnergy_1[i]) i++;
	//atteuation by interpolation
	double fInterpRatio = (fE-fEnergy_1[i])/(fEnergy_1[i+1]-fEnergy_1[i]);
	fCS_C = fCS_Compton_1[i] + fInterpRatio*(fCS_Compton_1[i+1]-fCS_Compton_1[i]);
	fCS_P = fCS_PP_1[i] + fInterpRatio*(fCS_PP_1[i+1]-fCS_PP_1[i]);
	fCS_E = fCS_PE_1[i] + fInterpRatio*(fCS_PE_1[i+1]-fCS_PE_1[i]);
	return;
}
*/

int main(){
	
	GSimProcess* pGammaSim = new GSimProcess();
	srand(time(0));  // Initialize random number generator.
	std::cout << "Gamma sim start" << std::endl;
	
  	// Load queue with some number of initial emissions.
  	double f_SourceE = 0.662;//Cs-137 source
  	//double f_SourceE = 0.183;//Uranium line
  	
  	//Add a new point source
  	pGammaSim->AddNewSource(new GPointSource(0.0,0.0,0.0, f_SourceE));
  	//First: a detector
  	pGammaSim->AddNewObject(new GCuboid(-1,-1,1, 1,1,2.5, true));
  	//Second: a large block of CZT between the detector and the source.
  	pGammaSim->AddNewObject(new GCuboid(-1,-1,0, 1,1,1, false));
  	
  	std::cout << "Starting to pump queue with events"<< std::endl;
  	
  	pGammaSim->PumpDecays(3E7);
  	
  	std::cout << "Start simulation" << std::endl;
  	// Run the simulation.
  	if(pGammaSim->vecGCuboid.size()>0){
	  	pGammaSim->Run();
  		pGammaSim->OutputSpectrum();
  	}
  	
  	std::cout << "Simulation finished" << std::endl;
  	
  	//Some pointers will be released by the destructor of pGammaSim.
  	//delete pSpectrum;
  	delete pGammaSim;
  	
	return 0;
}
