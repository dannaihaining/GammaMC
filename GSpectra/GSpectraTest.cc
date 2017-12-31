//#include <Python.h>

#include "GSpectra.h"

int main(){
    GSpectra* pSpecTemp = new GSpectra(20, 1);
    for(int i=0; i<20; i++){
    	for(int j=0; j<=i; j++){
    		pSpecTemp->AddOneEvent(i);
    	}
    }
    
  	pSpecTemp->Output("Spectrum_temp.txt");
  	pSpecTemp->Clear();
  	pSpecTemp->Output("Spectrum_temp_clear.txt");
    delete pSpecTemp;
    
    /*
    Py_Initialize();
    PyObject *obj = Py_BuildValue("s", "simple_plot.py");
 	FILE *file = _Py_fopen_obj(obj, "r+");
  	if(file != NULL) {
     	PyRun_SimpleFile(file, "simple_plot.py");
 	}
  	Py_Finalize();
    */
    return 0;
}
