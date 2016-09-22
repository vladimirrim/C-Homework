#include "../include/str_test.h"
#include <stdio.h>
int strlen(const char * str){
    int cnt=0;
    while(*str){
        cnt++;
        *str++;
    }
    return cnt;
}
void test_len(){
char a[]="Hello";
char b[]="World";
printf("len(a) = %d\nlen(b) = %d\n",strlen(a),strlen(b));
}
