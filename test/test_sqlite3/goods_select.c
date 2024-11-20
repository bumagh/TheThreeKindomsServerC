#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
 int callback(void *data, int argc, char **argv, char **azColName){
   
   int i;
   int *a = (int *)data;
   *a = 6;
 printf("value_a=%d,p_a=%p\n", *a, a);
   for(i = 0; i<argc; i++){
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
   const char* data = "Callback function called";

   /* Open database */
     char buf[64];
   sprintf(buf,"../../data/%s",dbname);
   rc = sqlite3_open(buf, &db);
   
   if(rc) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "select * from goods";
//sql = "select qino from chibi where qino=%d;";
 //char buf2[128];
   //  sprintf(buf2, sql,1);
   int a = 5;
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void *)&a, &zErrMsg);
   printf("value_a = %d,p_a=%p\n", a,&a);
   printf("rc=%d\n", rc);
   if(rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return 1;
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
   return 0;
}