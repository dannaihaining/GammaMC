#include "GSource.h"

GVector* GPointSource::GenerateOneRay(){
	double x, y, z;
	GRand::RandSphereDir(x,y,z);
	return new GVector(gs_SourcePos->x, gs_SourcePos->y,
		gs_SourcePos->z, x, y, z);
}

GVector* GCuboidSource::GenerateOneRay(){
	double fPosX, fPosY, fPosZ, fDirX, fDirY, fDirZ;
	GRand::RandCuboidUniform(&gs_SourceCuboid->bl, &gs_SourceCuboid->tr,
		fPosX, fPosY, fPosZ);
	GRand::RandSphereDir(fDirX, fDirY, fDirZ);
	return new GVector(fPosX, fPosY, fPosZ, fDirX, fDirY, fDirZ);
}
