#include "GSimProcess/GSimProcess.h"

/*
#include "GRand/GRand.h"
#include "GEvent/GEvent.h"
#include "GGeometry/GPoint.h"
#include "GGeometry/GVector.h"
#include "GGeometry/GCuboid.h"
#include "GSource/GSource.h"
#include "GSpectra/GSpectra.h"
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>



bool ProcessConfig(GSimProcess* pGammaSim){
	std::ifstream infile("../Settings.ini");//No need to release the memory manually this way
	std::string line;
	
    std::regex rComment ("^#");
    std::regex rBlank ("^\s*$");
    std::regex rTime ("^SIM_TIME");
    std::regex rPointSouce ("^SOURCE_POINT");
    std::regex rCuboidObject ("^OBJ_CUBOID");
    std::smatch m;
    std::string strKeyWord;
    
    bool bIfInputValid = true;
	
	double fTime = 0.0;
	
	
	while (std::getline(infile, line))
	{
    	if(std::regex_search (line,m,rComment)) continue;
    	if(std::regex_search (line,m,rBlank)) continue;
    	//Input time length
    	if(std::regex_search (line,m,rTime)){
    		std::istringstream iss(line);
    		if(!(iss >> strKeyWord)) bIfInputValid = false;
    		if(!(iss >> fTime)) bIfInputValid = false;
    		std::cout<<"Simulation time length: "<<fTime<<" seconds"<<std::endl;
    	}
    	//Input source type
    	if(std::regex_search (line,m,rPointSouce)){
    		std::istringstream iss(line);
    		if(!(iss >> strKeyWord)) bIfInputValid = false;
    		double x,y,z,E,fA;
    		if(!(iss >> x >> y >> z >> E >> fA)) bIfInputValid = false;
    		std::cout<<"Add point source, x="<<x<<", y="<<y<<", z="<<z;
    		std::cout<<", Energy: " << E << " MeV" <<", Activity: "<<fA<<" uCi."<<std::endl;
    		pGammaSim->AddNewSource(new GPointSource(x, y, z, E, fA));
    	}
    	//Input object type
    	if(std::regex_search (line,m,rCuboidObject)){
    		std::istringstream iss(line);
    		if(!(iss >> strKeyWord)) bIfInputValid = false;
    		double x1,y1,z1,x2,y2,z2;
    		std::string strMaterialName;
    		int nIsDetector;
    		if(!(iss >> x1 >> y1 >> z1 >> x2 >> y2 >> z2)) bIfInputValid = false;
    		if(!(iss >> strMaterialName)) bIfInputValid = false;
    		if(!(iss >> nIsDetector)) bIfInputValid = false;
    		std::cout<<"Add new object: cuboid of "<<strMaterialName;
    		if(nIsDetector>0) std::cout<<" as active detctor volume.";
    		std::cout<<std::endl;
    		std::cout<<"Position: "<<x1<<" "<<y1<<" "<<z1<<" "<<x2<<" "<<y2<<" "<<z2<<" "<<std::endl;
    		pGammaSim->AddNewObject(new GCuboid(x1, y1, z1, x2, y2, z2, (nIsDetector>0)));
    		if(nIsDetector) pGammaSim->AddNewSpectrum(new GSpectra(1000, 1));
    	}
    	if(!bIfInputValid){
    		std::cout<<"Input file exception"<<std::endl;
    		return false;
    	}
	}
	if(fTime<=0.0){
		std::cout<< "Input time length invalid!" << std::endl;
		return false;
	}
	if(!pGammaSim->ObjectConstraintTest()){
    	std::cout<<"Input objects have overlapped parts, quit"<<std::endl;
    	return false;
   	}
	std::cout<< "Simulation time length " << fTime << "seconds." << std::endl;
	pGammaSim->PumpDecays(fTime);
	return true;
}

int main(){
	
	GSimProcess* pGammaSim = new GSimProcess();
	srand(time(0));  // Initialize random number generator.
	std::cout << "Configuring simulation settings ..." << std::endl;
	
	if(!ProcessConfig(pGammaSim)) return 0;
	/*
  	// Load queue with some number of initial emissions.
  	double f_SourceE = 0.662;//Cs-137 source
  	//double f_SourceE = 0.183;//Uranium line
  	
  	//Add a new point source
  	pGammaSim->AddNewSource(new GPointSource(0.0,0.0,0.0, f_SourceE));
  	//First: a detector
  	pGammaSim->AddNewObject(new GCuboid(-1,-1,1, 1,1,2.5, true));
  	//Second: a large block of CZT between the detector and the source.
  	pGammaSim->AddNewObject(new GCuboid(-1,-1,0, 1,1,1, false));
  	
  	std::cout << "Starting to pump queue with events"<< std::endl;
  	
  	pGammaSim->PumpDecays(3E7);
  	
  	*/
  	
  	std::cout << "Start simulation" << std::endl;
  	// Run the simulation.
  	if(pGammaSim->vecGCuboid.size()>0){
	  	pGammaSim->Run();
  		pGammaSim->OutputSpectrum();
  	}
  	
  	std::cout << "Simulation finished" << std::endl;
  	
  	//Some pointers will be released by the destructor of pGammaSim.
  	delete pGammaSim;
  	
	return 0;
}
