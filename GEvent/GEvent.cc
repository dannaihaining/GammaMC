#include "GEvent.h"
#include "../GSimProcess/GSimProcess.h"


//For now I just used the linear attenuation coefficient of CZT at 662 keV. (1/cm)
#define DENSITY 5.8
#define E_THR 10

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
	double fT1, fT2, fX, fY, fZ, fEs, fTheta, fPhi;
	if(pGProc->vecGCuboid[0]->IfCollide(pVector, fT1, fT2)){
		double fZTemp;
  		if(GRand::RandInteractionDepth(fCS_C+fCS_P+fCS_E,fZTemp,1*(fT2-fT1))){
  			double fTemp = GRand::RandDouble(0.0, fCS_C+fCS_P+fCS_E);
  			if(fTemp <= fCS_C){//For now only one scatter at most.
  				GRand::RandComptonAngle(E, fX, fY, fZ, fEs, fTheta, fPhi, 0);
  				pGProc->pSpectrum->AddOneEvent(1000*(E-fEs));
  			}
  			else if(fTemp <= fCS_C+fCS_P){}
  			else{
  				pGProc->pSpectrum->AddOneEvent(1000*E);
  				//pGProc->ScheduleEvent(new GPhotoElec(t,0.0,0.0,0.0, E));
  			}
  		}
	}
	delete pVector;
}

void GCompton::ProcessEvent(GSimProcess* pGProc){
	double fX1, fY1, fZ1, fEs, fTheta, fPhi;
	GRand::RandComptonAngle(E, fX1, fY1, fZ1, fEs, fTheta, fPhi, 0);
	pGProc->pSpectrum->AddOneEvent(1000*(E-fEs));
}

void GPhotoElec::ProcessEvent(GSimProcess* pGProc){
	pGProc->pSpectrum->AddOneEvent(1000*E);
}

void GPairProd::ProcessEvent(GSimProcess* pGProc){
	
}

