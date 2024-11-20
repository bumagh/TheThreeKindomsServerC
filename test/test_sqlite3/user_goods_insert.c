#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
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
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   // sql = "INSERT INTO goods (name,info,type,level,price)" \
   //       "VALUES ('招兵令','打开后95%概率获得一个常人,5%概率获得一个英才','baowu',1,100),"\
   //       "('招贤令','打开后25%概率获得一个英才75%概率获得一个常人','baowu',2,300),"\
   //       "('将军令','打开后25%概率获得一个将才,75%概率获得一个英才','baowu',3,1000),"\
   //       "('大将军令','打开后95%概率获得一个将才,5%概率获得一个猛将','baowu',4,2500);";
         sql = "INSERT INTO user_goods (user_id,goods_id,counts)" \
         "VALUES (1,1,1);";
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if(rc != SQLITE_OK){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }
   sqlite3_close(db);
   return 0;
}