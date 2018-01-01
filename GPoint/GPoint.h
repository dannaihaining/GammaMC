#ifndef POINT_H
#define POINT_H


/*
 * Energy spectra class.
 */
class GPoint{
	private:
	double* fPos = new double[3];
	
	public:
	GPoint(double fInX=0, double fInY=0, double fInZ=0){
		fPos[0]=fInX; fPos[1]=fInY; fPos[2]=fInZ;
	}
	~GPoint(){
		delete [] fPos;
		fPos = nullptr;
	}
	//Default values are only needed in declaration, not in implementation
	void UpdatePoint(double fInX=0, double fInY=0, double fInZ=0);
	double* GetPos();
};


#endif
