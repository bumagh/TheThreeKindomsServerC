#include<stdio.h>
#include<string.h>

char *getStr(){

    char *str = (char*)malloc(100*sizeof(char));
    strcpy(str, "1000");
    return str;
}
char *getStr2(){
    char *s = getStr();
    return s;
}
int getStr3(char *str){
    strcpy(str, "str3");
}
int main(){
    char buf[64];
    getStr3(buf);
    printf("%s\n",buf);
    return 0;
}