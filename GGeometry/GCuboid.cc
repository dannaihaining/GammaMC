#include "GCuboid.h"
#include <iostream>     // std::cout

//Note I used X86 system so double should be even faster than float

//Kudos to "dcousens"
//https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
//In this implementation if cuboidis tangent with the vector then I assume there will not be any interactions
bool GCuboid::IfCollide(GVector* g_sVec, double& tEnter, double &tExit){
	double t1 = (bl.x - g_sVec->gs_Orig.x)*g_sVec->fDirFracX;
	double t2 = (tr.x - g_sVec->gs_Orig.x)*g_sVec->fDirFracX;
	double t3 = (bl.y - g_sVec->gs_Orig.y)*g_sVec->fDirFracY;
	double t4 = (tr.y - g_sVec->gs_Orig.y)*g_sVec->fDirFracY;
	double t5 = (bl.z - g_sVec->gs_Orig.z)*g_sVec->fDirFracZ;
	double t6 = (tr.z - g_sVec->gs_Orig.z)*g_sVec->fDirFracZ;
	tEnter = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	tExit = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));
	
	// if tEnter > tExit, ray doesn't intersect AABB
	if (tEnter >= tExit){
		return false;
	}
	
	// Vector is in the opposite direction
	if (tExit <= 0.0){
		return false;
	}
	
	// if tEnter < 0, ray (line) is intersecting AABB, but the vector starts from within the cuboid.
	if (tEnter < 0){
		tEnter = 0.0;
    	return true;
    }
    
	return true;
}
