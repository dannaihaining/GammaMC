#ifndef SPECTRA_H
#define SPECTRA_H

/*
 * Energy spectra class.
 */
class GSpectra{
	private:
	//Size of a spectrum
	const int nSpecSize; 	
	//Energy bin width
	const double fBin; 		
	//Largest value to insert into the spectrum. Any larger values are truncated.
	const double fHigh; 	
	//By default the smallest value allowed is zero.
	int* pSpec;
	
	public:
	GSpectra(double fInHigh, double fInBin):fHigh(fInHigh-0.001),fBin(fInBin),nSpecSize((int)(fInHigh/fInBin)){
		//This constructor is dangerous since I do not check parameters.
		//No zero/negative values should be passed.
		pSpec = new int[nSpecSize];
	}
	~GSpectra(){
		//Free the space
		delete pSpec;
	}
	void AddOneEvent(int num);
	void AddOneEvent(float num);
	void AddOneEvent(double num);
	void Clear();
	int CountsInBin(int nBin);
};


#endif
