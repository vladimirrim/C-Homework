#include "../include/str_test.h"
#include <stdio.h>
char * strcat(char * destination, const char * source){
    while(*destination!=0)
        *destination++;
    while(*source!=0)
        *destination++=*source++;
    *destination=0;
    return destination;
}
void test_cat(){
char a[]="Hello";
char b[]=" World";
printf("a = %s\nb = %s\n",a,b);
strcat(a,b);
printf("a = %s\n",a);
}
