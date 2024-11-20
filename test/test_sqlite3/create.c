#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i < argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[]) {
    if(argc != 2){
      printf("参数有误\n");
      return -1;
   }
   char *dbname = argv[1];
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   /* Open database */
   char buf[64];
   sprintf(buf,"../../data/%s",dbname);
   rc = sqlite3_open(buf, &db);
   
   if(rc) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "CREATE TABLE Chibi("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "QINO           INT    NOT NULL," \
      "WEIJ            INT     NOT NULL," \
      "WEIY        BIGINT    NOT NULL," \
      "SHUJ            INT     NOT NULL," \
      "SHUY        BIGINT    NOT NULL," \
      "WUJ            INT     NOT NULL," \
      "WUY        BIGINT    NOT NULL," \
      "YAWEIJ        INT  DEFAULT 0 ," \
      "YAWEIY      BIGINT    NOT NULL," \
      "YAWEIJ        INT    NOT NULL," \
      "YAWEIY      BIGINT    NOT NULL," \
      "YAWEIJ        INT    NOT NULL," \
      "YAWEIY      BIGINT    NOT NULL," \
      "SHUJ         REAL );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if(rc != SQLITE_OK){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   sqlite3_close(db);
   return 0;
}