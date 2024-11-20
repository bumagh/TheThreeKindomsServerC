#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "yyjson.h"

int callback(void *data, int argc, char **argv, char **azColName)
{

   int i;
  char *jsonbuf = (char*)data;
   
     
   //read json
   if(strlen(jsonbuf) == 0){
      //new json
   yyjson_mut_doc  *doc = yyjson_mut_doc_new(NULL);
   yyjson_mut_val *newarr = yyjson_mut_arr(doc);
   yyjson_mut_val *ele = yyjson_mut_obj_with_str(doc, (const char **)azColName,(const char **)argv, argc);
    yyjson_mut_arr_append(newarr,ele);
   yyjson_mut_doc_set_root(doc,newarr);
  const char *json= yyjson_mut_write(doc, 0, NULL);

  printf("%s\n", json);
  strcpy(jsonbuf,json);
  printf("jsonbuf:%s\n",jsonbuf);
  free(json);
    yyjson_mut_doc_free(doc);
   }else{
      
  yyjson_doc  *doc  = yyjson_read(jsonbuf,strlen(jsonbuf),0);
      if(doc){
         yyjson_mut_doc *mutdoc = yyjson_doc_mut_copy(doc, NULL);
         yyjson_mut_val *mutroot = yyjson_mut_doc_get_root(mutdoc);
         if(yyjson_is_arr(mutroot)){
           
      yyjson_mut_val *ele = yyjson_mut_obj_with_str(mutdoc, (const char **)azColName,(const char **)argv, argc);
       yyjson_mut_arr_append(mutroot,ele);     
        const char *json= yyjson_mut_write(mutdoc, 0, NULL);
        printf("newjson:%s\n",json);
         strcpy(jsonbuf,json);
         free(json);
         }else{
            printf("no it not arr\n");
         }
         yyjson_doc_free(doc);
         yyjson_mut_doc_free(mutdoc);
     }else printf("read error:\n");
    
   }
   
  
// // Free the memory of doc and all values which is created from this doc.
 //  yyjson_mut_doc_free(doc);

   for (i = 0; i < argc; i++)
   {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      printf("参数有误\n");
      return -1;
   }
   char *dbname = argv[1];

   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char *data = "Callback function called";


   /* Open database */
   char buf[64];
   sprintf(buf, "../../data/%s", dbname);
   rc = sqlite3_open(buf, &db);

   if (rc)
   {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return (0);
   }
   else
   {
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "select goods_id,counts from user_goods where user_id=9";
   // sql = "select qino from chibi where qino=%d;";
   // char buf2[128];
   //   sprintf(buf2, sql,1);


  
 
   //char jsonbuf[1024]={0};
   //char *jsonbuf = (char *)malloc(1024*sizeof(char));
   static char jsonbuf[1024];
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void *)&jsonbuf, &zErrMsg);
  // printf("p_doc=%p\n",pdoc);
   printf("rc=%d\n", rc);
   if (rc != SQLITE_OK)
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return 1;
   }
   else
   {
      fprintf(stdout, "Operation done successfully\n");
   }
 printf("ends:%s\n",jsonbuf);
   sqlite3_close(db);
   return 0;
}