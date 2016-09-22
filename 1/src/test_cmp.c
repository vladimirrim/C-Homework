#include "../include/str_test.h"
#include <stdio.h>
int strcmp(const char * str1, const char * str2){
    int k=0;
    while(*str2!=0&&*str1!=0&&*str1==*str2){
        *str1++;*str2++;
    }
    if(!*str1&&!*str2)
        return 0;
    if(!str1||*str2>*str1)
        return -1;
    if(!str2||*str1>*str2)
        return 1;
}
void test_cmp(){
char a[]="Hello";
char b[]="World";
printf("a = %s\nb = %s\n",a,b);
printf("a>b(strcmp=%d\n)",strcmp(b,a));
}
