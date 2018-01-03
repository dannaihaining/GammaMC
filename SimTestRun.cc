#include "GSimProcess/GSimProcess.h"
#include "GRand/GRand.h"
#include "GEvent/GEvent.h"

int main(){
	GSimProcess* GammaSim = new GSimProcess();
	srand(time(0));  // Initialize random number generator.
	std::cout << "Gamma sim start\n";
  	// Load queue with some number of initial events.
  	for (int t=0; t<10; t+=GRand::randInt(5)){
    	std::cout << "pumping queue with event at time: " << t << "us \n";
    	GammaSim->scheduleEvent(new GCompton((double)t));
  	}
  	// Run the simulation.
  	GammaSim->run();
	return 0;
}
