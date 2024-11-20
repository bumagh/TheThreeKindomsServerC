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
   sql = "create table if not exists user("  \
      "id integer primary key autoincrement," \
      "online           int    DEFAULT 0," \
      "status           int    DEFAULT 0," \
      "server           int    DEFAULT 0," \
      "name           nchar  DEFAULT 'unnamed'," \
       "account           nchar  NOT NULL," \
        "pwd           nchar  NOT NULL," \
      "job           int    DEFAULT 0," \
      "level           int    DEFAULT 1," \
      "contry         int    DEFAULT 0," \
      "gender           int    DEFAULT 0," \
      "birthplace           int    DEFAULT 0," \
      "phystr           int    DEFAULT 100," \
      "hp           int    DEFAULT 100," \
      "hpmax           int    DEFAULT 100," \
      "mp           int    DEFAULT 100," \
      "mpmax           int    DEFAULT 100," \
      "attack           int    DEFAULT 10," \
      "defence           int    DEFAULT 5," \
      "speed           int    DEFAULT 50," \
      "coin           int    DEFAULT 0," \
      "tael            int     DEFAULT 0);";

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