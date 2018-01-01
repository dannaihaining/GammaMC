#ifndef CUBOID_H
#define CUBOID_H
#include "GGeometryStruct.h"
#include <algorithm>

class GCuboid{
	private:
	//Diagonal points defining the cuboid
	GPoint bl;
	GPoint tr;
	public:
	GCuboid(){
		bl.SetPos(0,0,0);
		tr.SetPos(0,0,0);
	}
	GCuboid(double x1, double y1, double z1, double x2, double y2, double z2){
		bl.SetPos(x1, y1, z1);
		tr.SetPos(x2, y2, z2);
	}
	GCuboid(GPoint gs_InBl, GPoint gs_InTr){
		bl.SetPos(gs_InBl.x, gs_InBl.y, gs_InBl.z);
		tr.SetPos(gs_InTr.x, gs_InTr.y, gs_InTr.z);
	}
	//If a vector "collides" with cuboid. Return the timing of enter and exit.
	bool IfCollid(GVector* g_sVec, double& t1, double &t2);
};

#endif
