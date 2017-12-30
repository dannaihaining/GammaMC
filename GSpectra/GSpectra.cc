#include "GSpectra.h"
#include <cstring>

void GSpectra::AddOneEvent(int num){
	double fNum = (double)num;
	fNum = 0>fNum? 0:fNum;
	fNum = fHigh<fNum? fHigh:fNum;
	int nIndex = (int)(fNum/fBin);
	pSpec[nIndex] ++;
}
void GSpectra::AddOneEvent(float num){
	double fNum = (double)num;
	fNum = 0>fNum? 0:fNum;
	fNum = fHigh<fNum? fHigh:fNum;
	int nIndex = (int)(fNum/fBin);
	pSpec[nIndex] ++;
}
void GSpectra::AddOneEvent(double num){
	double fNum = num;
	fNum = 0>fNum? 0:fNum;
	fNum = fHigh<fNum? fHigh:fNum;
	int nIndex = (int)(fNum/fBin);
	pSpec[nIndex] ++;
}
void GSpectra::Clear(){
	memset(pSpec, 0, sizeof(pSpec));
}
int GSpectra::CountsInBin(int nBin){
	if(nBin>=nSpecSize) return -1;
	return pSpec[nBin];
}
