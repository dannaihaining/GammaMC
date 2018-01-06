#ifndef MATERIAL_H
#define MATERIAL_H

#include "../GGeometry/GCuboid.h"
#include <sqlite3.h> 
#include <stdexcept>

class GMaterial{
	public:
	//
	GMaterial(){
		pAttenData = nullptr;
		if(!SQLDataFetch()){
			throw std::runtime_error("failed to query database\n");
		}
	}
	~GMaterial(){
		delete pAttenData;
	}
	bool SQLDataFetch();
	private:
	double fDensity;
	double* pAttenData;
	int nEnergyBins, nInteractionTypes;
};

#endif
