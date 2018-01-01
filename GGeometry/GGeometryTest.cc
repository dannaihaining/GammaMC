#include "GGeometryStruct.h"
#include <iostream>     // std::cout

int main(){
    std::cout<<"Initalizing point"<<std::endl;
    GPoint gs_PointTemp;
    std::cout<<gs_PointTemp.x<<" "<<gs_PointTemp.y<<" "<<gs_PointTemp.z<<std::endl;
    std::cout<<"Modifying point"<<std::endl;
    gs_PointTemp.SetPos(1,2,3);
    std::cout<<gs_PointTemp.x<<" "<<gs_PointTemp.y<<" "<<gs_PointTemp.z<<std::endl;
    
    std::cout<<"Initalizing vector"<<std::endl;
    GVector gs_VectorTemp;
    std::cout<<"Origin: "<<gs_VectorTemp.gs_Orig.x<<" "<<gs_VectorTemp.gs_Orig.y<<" "<<gs_VectorTemp.gs_Orig.z<<std::endl;
    std::cout<<"Direction: "<<gs_VectorTemp.fDirX<<" "<<gs_VectorTemp.fDirY<<" "<<gs_VectorTemp.fDirZ<<std::endl;
    
    std::cout<<"Changing direction"<<std::endl;
    gs_VectorTemp.SetDir(1,2,3);
    std::cout<<"Origin: "<<gs_VectorTemp.gs_Orig.x<<" "<<gs_VectorTemp.gs_Orig.y<<" "<<gs_VectorTemp.gs_Orig.z<<std::endl;
    std::cout<<"Direction: "<<gs_VectorTemp.fDirX<<" "<<gs_VectorTemp.fDirY<<" "<<gs_VectorTemp.fDirZ<<std::endl;
    
    std::cout<<"Changing to direction [0 0 0]"<<std::endl;
    gs_VectorTemp.SetDir(0,0,0);
    std::cout<<"Origin: "<<gs_VectorTemp.gs_Orig.x<<" "<<gs_VectorTemp.gs_Orig.y<<" "<<gs_VectorTemp.gs_Orig.z<<std::endl;
    std::cout<<"Direction: "<<gs_VectorTemp.fDirX<<" "<<gs_VectorTemp.fDirY<<" "<<gs_VectorTemp.fDirZ<<std::endl;
    
    std::cout<<"Changing origin"<<std::endl;
    gs_VectorTemp.SetOrig(1,2,3);
    std::cout<<"Origin: "<<gs_VectorTemp.gs_Orig.x<<" "<<gs_VectorTemp.gs_Orig.y<<" "<<gs_VectorTemp.gs_Orig.z<<std::endl;
    std::cout<<"Direction: "<<gs_VectorTemp.fDirX<<" "<<gs_VectorTemp.fDirY<<" "<<gs_VectorTemp.fDirZ<<std::endl;
    
    std::cout<<"Initalizing new vector"<<std::endl;
    GVector gs_VectorTemp1(1,2,3,true);
    std::cout<<"Origin: "<<gs_VectorTemp1.gs_Orig.x<<" "<<gs_VectorTemp1.gs_Orig.y<<" "<<gs_VectorTemp1.gs_Orig.z<<std::endl;
    std::cout<<"Direction: "<<gs_VectorTemp1.fDirX<<" "<<gs_VectorTemp1.fDirY<<" "<<gs_VectorTemp1.fDirZ<<std::endl;
    
    std::cout<<"Initalizing new vector"<<std::endl;
    GVector gs_VectorTemp2(1,2,3,false);
    std::cout<<"Origin: "<<gs_VectorTemp2.gs_Orig.x<<" "<<gs_VectorTemp2.gs_Orig.y<<" "<<gs_VectorTemp2.gs_Orig.z<<std::endl;
    std::cout<<"Direction: "<<gs_VectorTemp2.fDirX<<" "<<gs_VectorTemp2.fDirY<<" "<<gs_VectorTemp2.fDirZ<<std::endl;
    
    std::cout<<"Initalizing new vector"<<std::endl;
    GVector gs_VectorTemp3(1,2,3,1,2,3);
    std::cout<<"Origin: "<<gs_VectorTemp3.gs_Orig.x<<" "<<gs_VectorTemp3.gs_Orig.y<<" "<<gs_VectorTemp3.gs_Orig.z<<std::endl;
    std::cout<<"Direction: "<<gs_VectorTemp3.fDirX<<" "<<gs_VectorTemp3.fDirY<<" "<<gs_VectorTemp3.fDirZ<<std::endl;
    
    return 0;
}
