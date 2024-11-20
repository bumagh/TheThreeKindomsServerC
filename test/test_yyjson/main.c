#include <stdio.h>
#include <stdlib.h>

#include "yyjson.h"
void test1(){
yyjson_doc *doc = yyjson_read("[1,2,3]", 7, 0);
char *json = yyjson_write(doc, YYJSON_WRITE_PRETTY, NULL);
printf("%s\n", json);
free(json);
}

void test2(){
    yyjson_mut_doc *doc = yyjson_mut_doc_new(NULL);
yyjson_mut_val *arr = yyjson_mut_arr(doc);
yyjson_mut_doc_set_root(doc, arr);
yyjson_mut_arr_add_int(doc, arr, 1);

yyjson_mut_arr_add_int(doc, arr, 2);
yyjson_mut_arr_add_int(doc, arr, 3);
    
char *json = yyjson_mut_write(doc, YYJSON_WRITE_PRETTY, NULL);
printf("%s\n", json);
free(json);
}
void test3(){
    // Build this JSON:
//     {
//        "page": 123,
//        "names": [ "Harry", "Ron", "Hermione" ]
//     }
 
// Create a mutable document.
yyjson_mut_doc *doc = yyjson_mut_doc_new(NULL);
 
// Create an object, the value's memory is held by doc.
yyjson_mut_val *root = yyjson_mut_obj(doc);
 
// Create key and value, add to the root object.
yyjson_mut_val *key = yyjson_mut_str(doc, "page");
yyjson_mut_val *num = yyjson_mut_int(doc, 123);
yyjson_mut_obj_add(root, key, num);
 
// Create 3 string value, add to the array object.
yyjson_mut_val *names = yyjson_mut_arr(doc);
yyjson_mut_val *name1 = yyjson_mut_str(doc, "Harry");
yyjson_mut_val *name2 = yyjson_mut_str(doc, "Ron");
yyjson_mut_val *name3 = yyjson_mut_str(doc, "Hermione");
yyjson_mut_arr_append(names, name1);
yyjson_mut_arr_append(names, name2);
yyjson_mut_arr_append(names, name3);
 
// ❌ Wrong! the value is already added to another container.
yyjson_mut_obj_add(root, key, name1);
 
// Set the document's root value.
yyjson_mut_doc_set_root(doc, root);
 
// Write to JSON string
const char *json = yyjson_mut_write(doc, 0, NULL);
 printf("%s\n", json);
 free(json);
// Free the memory of doc and all values which is created from this doc.
yyjson_mut_doc_free(doc);
}

void test4(){
    const char *keys[] = {"name", "type", "id"};
const char *vals[] = {"Harry", "student", "123456"};
yyjson_mut_doc *doc = yyjson_mut_doc_new(NULL);
 
// Create an object, the value's memory is held by doc.

yyjson_mut_val *root = yyjson_mut_obj_with_str(doc, keys, vals, 3);
yyjson_mut_doc_set_root(doc, root);
const char *json = yyjson_mut_write(doc, 0, NULL);
 printf("%s\n", json);
 free(json);
// Free the memory of doc and all values which is created from this doc.
yyjson_mut_doc_free(doc);
}
int main(int argc, char *argv[])
{
   test4();
    return 0;
}