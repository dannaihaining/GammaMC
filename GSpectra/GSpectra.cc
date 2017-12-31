#include "GSpectra.h"

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
	memset(pSpec, 0, sizeof(pSpec[0])*nSpecSize);
}
void GSpectra::Output(std::string strFileName){
	std::ofstream myfile;
  	myfile.open(strFileName);	//Overwrite
  	myfile <<nSpecSize<< "\n";	//Spectrum bin number
  	myfile <<fBin<< "\n";		//Spectrum bin size
    for(int i=0; i<20; i++){
    	myfile <<pSpec[i]<< "\n";
    }
  	myfile.close();
}
int GSpectra::CountsInBin(int nBin){
	if(nBin>=nSpecSize) return -1;
	return pSpec[nBin];
}
