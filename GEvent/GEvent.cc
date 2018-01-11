#include "GEvent.h"
#include "../GSimProcess/GSimProcess.h"



void GEmission::ProcessEvent(GSimProcess* pGProc){
	pGProc->pSpectrum->AddOneEvent(1000*E);
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
	pGProc->pSpectrum->AddOneEvent(1000*E);
}

