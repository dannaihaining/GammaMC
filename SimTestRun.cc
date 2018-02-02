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

int nNumOfThreads = 1;

bool ProcessConfig(GSimProcess* pGammaSim){
	std::ifstream infile("Settings.ini");//No need to release the memory manually this way
	std::string line;
	
    std::regex rComment ("^#");
    std::regex rBlank ("^\s*$");
    std::regex rTime ("^SIM_TIME");
    std::regex rPointSouce ("^SOURCE_POINT");
    std::regex rCuboidObject ("^OBJ_CUBOID");
    std::regex rNoiseE ("^NOISE_E");
    std::regex rThread ("^THREAD_NUM");
    std::regex rRecordOption ("^EVENT_RECORD_OPTION");
    std::smatch m;
    std::string strKeyWord;
    
    bool bIfInputValid = true;
	
	double fTime = 0.0;
	
	//Use the first iteraction to parse the thread number only, so no specific orders are needed in the Settings.ini file!
	while (std::getline(infile, line)){
		if(std::regex_search (line,m,rThread)){
    		std::istringstream iss(line);
    		if(!(iss >> strKeyWord)) bIfInputValid = false;
    		if(!(iss >> nNumOfThreads)) bIfInputValid = false;
    		if(nNumOfThreads == 0) bIfInputValid = false;
    		if(nNumOfThreads > 0){
    			std::cout<<"Number of threads: "<< nNumOfThreads <<std::endl;
    			for(int i=0; i<nNumOfThreads; ++i){
    				std::vector<GCuboid*> tempVec;
    				pGammaSim->vecGCuboid.push_back(tempVec);
    			}
    		}
    		break;
    	}
    	if(!bIfInputValid){
    		std::cout<<"Input file exception"<<std::endl;
    		return false;
    	}
	}
	
	infile.close();
	infile.open("../Settings.ini");
	
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
    	}
    	if(std::regex_search (line,m,rNoiseE)){
    		std::istringstream iss(line);
    		if(!(iss >> strKeyWord)) bIfInputValid = false;
    		double fNoiseE;
    		if(!(iss >> fNoiseE)) bIfInputValid = false;
    		if(fNoiseE >= 0.0){
    			std::cout<<"Setting electronic noise: "<< fNoiseE << "keV" <<std::endl;
    			pGammaSim->ResetNoiseE(fNoiseE);
    		}
    	}
    	if(std::regex_search (line,m,rRecordOption)){
    		std::istringstream iss(line);
    		if(!(iss >> strKeyWord)) bIfInputValid = false;
    		int nRecordOpt;
    		if(!(iss >> nRecordOpt)) bIfInputValid = false;
    		if(nRecordOpt >= 0 && nRecordOpt<=2){
    			std::cout<<"Events recording option: "<< nRecordOpt <<std::endl;
    			pGammaSim->nRecordOption = nRecordOpt;
    		}
    	}
    	/*
    	if(std::regex_search (line,m,rThread)){
    		std::istringstream iss(line);
    		if(!(iss >> strKeyWord)) bIfInputValid = false;
    		if(!(iss >> nNumOfThreads)) bIfInputValid = false;
    		if(nNumOfThreads >= 0){
    			std::cout<<"Number of threads: "<< nNumOfThreads <<std::endl;
    			for(int i=0; i<nNumOfThreads; ++i){
    				std::vector<GCuboid*> tempVec;
    				pGammaSim->vecGCuboid.push_back(tempVec);
    			}
    		}
    	}
    	*/
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
	
	//Multi thread
	for(int nThread=0; nThread<nNumOfThreads; nThread++){
		std::priority_queue<GEvent*,
  		std::vector<GEvent *, std::allocator<GEvent*> >,
        GEventComparator> eventQueue;
        pGammaSim->vec_EventQueue.push_back(eventQueue);
        pGammaSim->PumpDecays(fTime, nThread);
	}
	//pGammaSim->PumpDecays(fTime, 0);
	//pGammaSim->PumpDecays(fTime, 1);
	
	return true;
}

int main(){
	
	GSimProcess* pGammaSim = new GSimProcess();
	srand(time(0));  // Initialize random number generator.
	std::cout << "Configuring simulation settings ..." << std::endl;
	
	if(!ProcessConfig(pGammaSim)) return 0;
  	
  	std::cout << "Start simulation" << std::endl;
  	// Run the simulation.
  	
  	auto start = std::chrono::high_resolution_clock::now();
  	
  	//Multi thread
  	if(pGammaSim->vecGCuboid.size()>0){
  		for(int i=0; i<nNumOfThreads; i++) pGammaSim->ThreadStartRun(i);
	  	std::string strTempFile = "EventsFile_";
	  	for(int i=0; i<nNumOfThreads; i++){
	  		pGammaSim->AddNewSpectrum(new GSpectra(1000, 1));
	  		pGammaSim->AddNewEventsFile(new GEventsFile(strTempFile + std::to_string(i) + ".txt"));
	  	}
	  	pGammaSim->ThreadWaitTillFinish();
		//Wait for all the processes to finish, then output spectra
		for(int i=0; i<nNumOfThreads; i++) pGammaSim->OutputSpectrum(i);
  	}
  	
  	//Some pointers will be released by the destructor of pGammaSim.
  	delete pGammaSim;
  	
  	std::cout << "Simulation finished" << std::endl;
  	
  	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout<<"Elapsed time "<< elapsed.count() << "S" <<std::endl;
  	
	return 0;
}
