#ifndef MATERIAL_H
#define MATERIAL_H

#include "../GGeometry/GCuboid.h"
#include <sqlite3.h> 
#include <stdexcept>
#include <string>
#include <stdio.h>
#include <stdlib.h>

class GMaterial{
	public:
	//
	GMaterial(const std::string strInName):strMatName(strInName){
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
	const std::string strMatName;
	//Density of material, unit g/cm^3
	double fDensity;
	//Attenuation coefficient of material, unit cm^2/g
	double* pAttenData;
	//Number of columns and rows for this material in the database.
	int nEnergyBins, nInteractionTypes;
	
	static int SQLCallBack(void *data, int argc, char **argv, char **azColName);
};

#endif
