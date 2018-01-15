#ifndef SOURCE_H
#define SOURCE_H

#include "../GRand/GRand.h"
#include "../GGeometry/GPoint.h"
#include "../GGeometry/GVector.h"
#include "../GGeometry/GCuboid.h"

class GSource{
	public:
  	// Construct source object.
  	GSource(double fInE):fEnergy(fInE){}
	const double fEnergy;//MeV
  	//Must remember to release the memory of the passed GVector object
  	//Jiawei-Jan03: Somwhow if I do not declare this virtual function to return 0 I get fuzzy problems (Undefined reference to vtable ...)
  	virtual GVector* GenerateOneRay() = 0;
	//Force the derived class destructor to be defined
  	//Note I MUST define it (in parentheses) so the copiler knows it is doing nothing.
  	virtual ~GSource(){}
};

class GPointSource : public GSource{
	public:
  	GPointSource(double fX, double fY, double fZ, double fInE):GSource(fInE){
  		gs_SourcePos = new GPoint(fX, fY, fZ);
  	}
  	~GPointSource(){
  		delete gs_SourcePos;
  	}
  	virtual GVector* GenerateOneRay();
	private:
	GPoint* gs_SourcePos;
};

class GCuboidSource : public GSource{
	public:
  	GCuboidSource(double x1, double y1, double z1, double x2, double y2, double z2, double fInE):GSource(fInE){
  		gs_SourceCuboid = new GCuboid(x1, y1, z1, x2, y2, z2);
  	}
  	~GCuboidSource(){
  		delete gs_SourceCuboid;
  	}
  	virtual GVector* GenerateOneRay();
	private:
	GCuboid* gs_SourceCuboid;
};

#endif
