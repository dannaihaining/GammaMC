#ifndef EVENTS_FILE_H
#define EVENTS_FILE_H

#include <iostream>
#include <fstream>     // std::cout, std::fixed
#include <iomanip>

class GEventsFile{
public:
  	//Noise in the unit of keV
	GEventsFile(std::string strFileName){
		eventsFile.open (strFileName);
	}
	~GEventsFile(){
		if (eventsFile.is_open()) eventsFile.close();
	}
  	void OutputToFile(const double E, const double x, const double y, const double z, const double time){
  		if (eventsFile.is_open()){
  			eventsFile << std::fixed << std::setprecision(3) << E << " " << x << " " << y << " " << z << " " << time << "\n";
  		}
  	}
private:
  	std::ofstream eventsFile;
	
};


#endif
