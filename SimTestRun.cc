#include "GSimProcess/GSimProcess.h"
#include "GRand/GRand.h"
#include "GEvent/GEvent.h"
#include "GGeometry/GPoint.h"
#include "GGeometry/GVector.h"
#include "GGeometry/GCuboid.h"
#include "GSource/GSource.h"
#include "GSpectra/GSpectra.h"

#include <iostream>
#include <fstream>

//For now I just used the linear attenuation coefficient of CZT at 662 keV. (1/cm)
#define DENSITY 5.8
#define E_THR 10

const int nENum = 7;
const double fEnergy[7] = {0.01, 0.05, 0.1, 0.2, 0.4, 0.5, 0.662};
const double fCS_Compton[7] = {0.06, 0.11, 0.1103, 0.09715, 0.07803, 0.07164, 0.0638};
const double fCS_PP[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
const double fCS_PE[7] = {135.4, 10.24, 1.463, 0.1994, 0.02917, 0.01641, 0.008302};

void GetAtten_All(double fE, double& fCS_C, double& fCS_P, double& fCS_E){
	if(fE<=fEnergy[0]){
		fCS_C = fCS_Compton[0];
		fCS_P = fCS_PP[0];
		fCS_E = fCS_PE[0];
		return;
	}
	if(fE>=fEnergy[nENum-1]){
		fCS_C = fCS_Compton[nENum-1];
		fCS_P = fCS_PP[nENum-1];
		fCS_E = fCS_PE[nENum-1];
		return;
	}
	int i=0;
	while(fE>fEnergy[i]) i++;
	//atteuation by interpolation
	double fInterpRatio = (fE-fEnergy[i])/(fEnergy[i+1]-fEnergy[i]);
	fCS_C = fCS_Compton[i] + fInterpRatio*(fCS_Compton[i+1]-fCS_Compton[i]);
	fCS_P = fCS_PP[i] + fInterpRatio*(fCS_PP[i+1]-fCS_PP[i]);
	fCS_E = fCS_PE[i] + fInterpRatio*(fCS_PE[i+1]-fCS_PE[i]);
	return;
}


int main(){
	
	//Note the spectrum class ONLY supports keV unit, with integer as bin size!
	GSpectra* pSpectrum = new GSpectra(1000, 1);
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
  	double f_SourceE = 0.662;//Cs-137 source
  	GPointSource* pPointSource = new GPointSource(0.0,0.0,0.0);
  	GCuboid* pTempObj1 = new GCuboid(-1,-1,1, 1,1,2.5);
  	
  	
  	//Attenuation coefficients
  	double fCS_C, fCS_P, fCS_E;
  	std::cout << "Starting to pump queue with events"<< std::endl;
  	while (t<1E7){//0.001 second of simulation
    	if(!GRand::RandTime2Decay(fActivity, tTemp)) break;
    	nTotalDecay ++;
    	t+=tTemp;
    	GVector* pVector = pPointSource->GenerateOneRay();
    	GetAtten_All(f_SourceE, fCS_C, fCS_P, fCS_E);
    	
		double fT1, fT2, fX, fY, fZ, fEs, fTheta, fPhi;
  		if(pTempObj1->IfCollide(pVector, fT1, fT2)){
  			nTrespass++;
  			
  			double fZTemp;
  			if(GRand::RandInteractionDepth(fCS_C+fCS_P+fCS_E,fZTemp,1*(fT2-fT1))){
  				nInteractions++;
  				GammaSim->ScheduleEvent(new GEmission(t,0.0,0.0,0.0, f_SourceE));
  				double fTemp = GRand::RandDouble(0.0, fCS_C+fCS_P+fCS_E);
  				if(fTemp <= fCS_C){//For now only one scatter at most.
  					GRand::RandComptonAngle(f_SourceE, fX, fY, fZ, fEs, fTheta, fPhi, 0);
  					pSpectrum->AddOneEvent(1000*(f_SourceE-fEs));
  				}
  				else if(fTemp <= fCS_C+fCS_P){}
  				else{
  					pSpectrum->AddOneEvent(1000*f_SourceE);
  				}
  			}
  		}
  		
    	delete pVector;
  	}
  	pSpectrum->Output("Spectrum_temp.txt");
  	// Run the simulation.
  	GammaSim->run();
  	GammaSim->OutputSpectrum();
  	
  	std::cout << "Total decays: " << nTotalDecay << std::endl;
  	std::cout << "Total trespass: " << nTrespass << std::endl;
  	std::cout << "Total interactions: " << nInteractions << std::endl;
  	
  	
  	delete pPointSource;
  	delete pSpectrum;
  	delete GammaSim;
  	
	return 0;
}
