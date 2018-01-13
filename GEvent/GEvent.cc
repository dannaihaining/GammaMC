#include "GEvent.h"
#include "../GSimProcess/GSimProcess.h"


//For now I just used the linear attenuation coefficient of CZT at 662 keV. (1/cm)
#define DENSITY 5.8
//Energy threshold for the simulation: 10 keV
#define E_THR 0.1

int nENum = 7;
double fEnergy[7] = {0.01, 0.05, 0.1, 0.2, 0.4, 0.5, 0.662};
double fCS_Compton[7] = {0.06, 0.11, 0.1103, 0.09715, 0.07803, 0.07164, 0.0638};
double fCS_PP[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double fCS_PE[7] = {135.4, 10.24, 1.463, 0.1994, 0.02917, 0.01641, 0.008302};

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
//Attenuation coefficients
double fCS_C, fCS_P, fCS_E;

void GEmission::ProcessEvent(GSimProcess* pGProc){
	GVector* pVector = pGProc->pPointSource->GenerateOneRay();
	GetAtten_All(E, fCS_C, fCS_P, fCS_E);
	pGProc->ReOrderObjects(pVector);
	double fT1, fT2, fX, fY, fZ;
	for(int i=0; i<pGProc->vecGCuboid.size(); i++){
		if(pGProc->vecGCuboid[i]->IfCollide(pVector, fT1, fT2)){
			double fZTemp;
  			if(GRand::RandInteractionDepth(fCS_C + fCS_P + fCS_E, fZTemp, 1*(fT2 - fT1))){
  				double fTemp = GRand::RandDouble(0.0, fCS_C+fCS_P+fCS_E);
  				pVector->PointOnThis(fZTemp, fX, fY, fZ);
  				if(fTemp <= fCS_C){
  					pGProc->ScheduleEvent(new GCompton(time, fX, fY, fZ, E, pGProc->vecGCuboid[i]->IsDetector()));
  				}
  				else if(fTemp <= fCS_C + fCS_P){}
  				else{
  					pGProc->ScheduleEvent(new GPhotoElec(time, fX, fY, fZ, E, pGProc->vecGCuboid[i]->IsDetector()));
  				}
  			}
  			break;
		}
	}
	delete pVector;
}

void GCompton::ProcessEvent(GSimProcess* pGProc){
	double fX1, fY1, fZ1, fEs, fTheta, fPhi;
	GRand::RandComptonAngle(E, fX1, fY1, fZ1, fEs, fTheta, fPhi, 0);
  	if(E-fEs > E_THR){
  		pGProc->ScheduleEvent(new GEmission(time, fX1, fY1, fZ1, E-fEs, bInDetector));
  		//For now I assuemd all objects are detectors. I need to use a flag to mark some materials as non-detectors.
  		if(bInDetector) pGProc->pSpectrum->AddOneEvent(1000*(E-fEs));
  	}
  	else if(bInDetector) pGProc->pSpectrum->AddOneEvent(1000*E);
}

void GPhotoElec::ProcessEvent(GSimProcess* pGProc){
	if(bInDetector) pGProc->pSpectrum->AddOneEvent(1000*E);
}

void GPairProd::ProcessEvent(GSimProcess* pGProc){
	
}

