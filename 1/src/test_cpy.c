#include "../include/str_test.h"
#include <stdio.h>
char * strcpy(char * destination, const char * source){
    while(*source!=0){
        *destination++=*source++;
    }
    *destination=0;
    return destination;
}
void test_cpy(){
char a[]="Hello";
char b[20];
strcpy(b,a);
printf("a = %s\nb = %s\n",a,b);
printf("b = %s\n",b);
}

