#include "GPoint.h"
#include <iostream>     // std::cout

int main(){
    GPoint* pPointTemp = new GPoint();
    double* pTemp = pPointTemp->GetPos();
    std::cout<<pTemp[0]<<pTemp[1]<<pTemp[2]<<std::endl;
    pPointTemp->UpdatePoint(1,2,3);
    std::cout<<pTemp[0]<<pTemp[1]<<pTemp[2]<<std::endl;
    
    std::cout<<"Checking pointer before deletion"<<std::endl;
    
    if(pTemp==nullptr) std::cout<<"NULL"<<std::endl;
    
    delete pPointTemp;
    
    std::cout<<"Checking pointer after deletion"<<std::endl;
    
    if(pTemp==nullptr) std::cout<<"NULL"<<std::endl;
    else{
    	//Note the values should become 0,2,3.
    	//This means that operator delete[] does not reset the memory, but only tells the system that these memories are ready for re-use! 
    	std::cout<<pTemp[0]<<pTemp[1]<<pTemp[2]<<std::endl;
    }
    
    std::cout<<"Delete pTemp"<<std::endl;
    pTemp = nullptr;
    if(pTemp==nullptr) std::cout<<"NULL"<<std::endl;
    else{
    	std::cout<<pTemp[0]<<pTemp[1]<<pTemp[2]<<std::endl;
    }
    
    return 0;
}
