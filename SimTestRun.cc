#include "GSimProcess/GSimProcess.h"
#include "GRand/GRand.h"
#include "GEvent/GEvent.h"

int main(){
	GSimProcess* GammaSim = new GSimProcess();
	srand(time(0));  // Initialize random number generator.
	std::cout << "Gamma sim start" << std::endl;
  	// Load queue with some number of initial events.
  	double fActivity = 1;//1 uCi activity
  	double t=0.0;
  	double tTemp;
  	int nTotalDecay = 0;
  	while (t<1E6){//One second of simulation
    	//std::cout << "pumping queue with event at time: " << t << "us" << std::endl;
    	GammaSim->scheduleEvent(new GEmission(t));
    	if(!GRand::RandTime2Decay(fActivity, tTemp)) break;
    	nTotalDecay ++;
    	t+=tTemp;
  	}
  	// Run the simulation.
  	GammaSim->run();
  	std::cout << "Total decays: " << nTotalDecay << std::endl;
	return 0;
}
