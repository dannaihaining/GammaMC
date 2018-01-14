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
	
	//Note the spectrum class ONLY supports keV unit, with integer as bin size!
	//GSpectra* pSpectrum = new GSpectra(1000, 1);
	GSimProcess* GammaSim = new GSimProcess();
	srand(time(0));  // Initialize random number generator.
	std::cout << "Gamma sim start" << std::endl;
  	// Load queue with some number of initial events.
  	double fActivity = 1;//1 uCi activity
  	double t=0.0;
  	double tTemp;
  	int nTotalDecay = 0;
  	//double f_SourceE = 0.662;//Cs-137 source
  	double f_SourceE = 0.183;//Uranium line
  	GPointSource* pPointSource = new GPointSource(0.0,0.0,0.0);
  	//GCuboid* pTempObj1 = new GCuboid(-1,-1,1, 1,1,2.5);
  	
  	
  	//Attenuation coefficients
  	//double fCS_C, fCS_P, fCS_E;
  	std::cout << "Starting to pump queue with events"<< std::endl;
  	while (t<1E7){//1000 second of simulation
    	if(!GRand::RandTime2Decay(fActivity, tTemp)) break;
    	nTotalDecay ++;
    	t+=tTemp;
  		GammaSim->ScheduleEvent(new GEmission(t,0.0,0.0,0.0, f_SourceE));
  		
  		/*
    	GetAtten_All_1(f_SourceE, fCS_C, fCS_P, fCS_E);
    	GVector* pVector = pPointSource->GenerateOneRay();
		double fT1, fT2, fX, fY, fZ, fEs, fTheta, fPhi;
  		if(pTempObj1->IfCollide(pVector, fT1, fT2)){
  			nTrespass++;
  			
  			double fZTemp;
  			if(GRand::RandInteractionDepth(fCS_C+fCS_P+fCS_E,fZTemp,1*(fT2-fT1))){
  				nInteractions++;
  				double fTemp = GRand::RandDouble(0.0, fCS_C+fCS_P+fCS_E);
  				if(fTemp <= fCS_C){//For now only one scatter at most.
  					GRand::RandComptonAngle(f_SourceE, fX, fY, fZ, fEs, fTheta, fPhi, 0);
  					//pSpectrum->AddOneEvent(1000*(f_SourceE-fEs));
  				}
  				else if(fTemp <= fCS_C+fCS_P){}
  				else{
  					//pSpectrum->AddOneEvent(1000*f_SourceE);
  				}
  			}
  		}
  		
    	delete pVector;
    	*/
  	}
  	//pSpectrum->Output("Spectrum_temp.txt");
  	// Run the simulation.
  	if(GammaSim->vecGCuboid.size()>0){
	  	GammaSim->run();
  		GammaSim->OutputSpectrum();
  	}
  	
  	std::cout << "Total decays: " << nTotalDecay << std::endl;
  	
  	delete pPointSource;
  	//delete pSpectrum;
  	delete GammaSim;
  	
	return 0;
}
