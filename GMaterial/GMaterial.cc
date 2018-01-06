#include "GMaterial.h"
#include <stdio.h>

bool GMaterial::SQLDataFetch(){
	//return false;
	sqlite3 *db;
   	char *zErrMsg = 0;
   	int rc;

   	rc = sqlite3_open("NISTElementsGammaAttenuation.db", &db);

   	if( rc ) {
      	fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      	return false;
  	} else {
      	fprintf(stderr, "Opened database successfully\n");
   	}
   	sqlite3_close(db);
   	return true;
}

int main(){
	GMaterial* foo = new GMaterial();
	return 0;
}
