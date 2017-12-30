#include <iostream>
#include <stdio.h>

#include "GSpectra.h"

int main(){
    GSpectra* pSpecTemp = new GSpectra(20, 1);
    for(int i=0; i<20; i++){
    	for(int j=0; j<=i; j++){
    		pSpecTemp->AddOneEvent(i);
    	}
    }
    for(int i=0; i<20; i++){
    	std::cout<<pSpecTemp->CountsInBin(i)<<std::endl;
    }
    delete pSpecTemp;
    return 0;
}
