#include "GMaterial.h"

bool GMaterial::SQLDataFetch(){
	//return false;
	sqlite3 *db;
   	char *zErrMsg = 0;
   	int rc;
	const char* data = "Callback function called";
	
   	rc = sqlite3_open("../NISTElementsGammaAttenuation.db", &db);

	//Note the database directory MUST be specified based on where the executable is.
   	if( rc ) {
      	fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      	return false;
  	} else {
      	fprintf(stderr, "Opened database successfully\n");
   	}
   	
   	/* Create merged SQL statement */
   	std::string strSQL = "SELECT energy, attencoeff FROM " + strMatName;
   	
   	/* Execute SQL statement */
  	rc = sqlite3_exec(db, strSQL.c_str(), SQLCallBack, (void*)data, &zErrMsg);
   	if( rc != SQLITE_OK ){
      	fprintf(stderr, "SQL error: %s\n", zErrMsg);
      	sqlite3_free(zErrMsg);
   	}else {
      	fprintf(stdout, "Operation done successfully\n");
   	}
   	
   	
   	sqlite3_close(db);
   	return true;
}


int GMaterial::SQLCallBack(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   
   //fprintf(stderr, "argc = %d", argc);
   
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      //printf("%s\n", azColName[i]);
   }
   printf("\n");
   return 0;
}

int main(){
	//GMaterial* foo = new GMaterial("CadmiumTelluride");
	GMaterial* foo = new GMaterial("Boron");
	return 0;
}
