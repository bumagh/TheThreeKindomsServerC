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
   sql = "INSERT INTO goods (name,info,type,level,price)" \
         "VALUES ('招兵令','打开后95%概率获得一个常人,5%概率获得一个英才','baowu',1,100),"\
         "('招贤令','打开后25%概率获得一个英才75%概率获得一个常人','baowu',2,300),"\
         "('将军令','打开后25%概率获得一个将才,75%概率获得一个英才','baowu',3,1000),"\
         "('大将军令','打开后95%概率获得一个将才,5%概率获得一个猛将','baowu',4,2500),"\
         // sql = "INSERT INTO goods (name,info,type,level,price)" \
         // "VALUES ('银两','可购买物品','baowu',1,1),"\
         // "('金币','可购买物品','baowu',1,500);";
         "('体力丹','使用后提升体力值100点','baowu',1,300),"\
         "('原矿','打开后随机获得1，2，3，4等级的宝石一块','baowu',1,100),"\
         "('精矿','打开后随机获得5，6，7，8等级的宝石一块','baowu',1,1600),"\
         "('珍矿','打开后随机获得9，10等级的宝石一块','baowu',1,15600),"\
         "('1级技能书','使用后提升1级技能熟练度1','baowu',1,2),"\
         "('2级技能书','使用后提升2级技能熟练度1','baowu',1,4),"\
         "('3级技能书','使用后提升3级技能熟练度1','baowu',1,6),"\
         "('4级技能书','使用后提升4级技能熟练度1','baowu',1,8),"\
         "('5级技能书','使用后提升5级技能熟练度1','baowu',1,10),"\
         "('银两','可购买物品','baowu',1,1),"\
          "('金币','可购买物品','baowu',1,500);";
         
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