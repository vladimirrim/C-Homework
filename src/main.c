#include <stdio.h>
#include "../include/merge.h"
#include <string.h>
int cmpa(const void *p1,const void *p2){
    int *pa=(int*)p1;
    int *pb=(int*)p2;
    return (*pa-*pb);
}


int cmpb(const void *p1,const void *p2){
    return strcmp((char*)p1,(char*)p2);
}


int cmpc(const void *p1,const void *p2){
    char *pa=(char*)p1;
    char *pb=(char*)p2;
    return (*pa-*pb);
}


int main(){
    int *a=(int*)malloc(sizeof(int)*3);
    a[0]=3;
    a[1]=-1;
    a[2]=0;
    char b[3][8];
    b[0][0]='f';b[0][1]='o';b[0][2]='o';b[0][3]=0;
    b[1][0]='b';b[1][1]='a';b[1][2]='r';b[1][3]=0;
    b[2][0]='b';b[2][1]='a';b[2][2]='z';b[2][3]='o';b[2][4]='o';b[2][5]='k';b[2][6]='a';b[2][7]=0;
    char *c=(char*)malloc(sizeof(char)*3);
    c[0]='z';
    c[1]='y';
    c[2]='x';
    merge_sort(a,3,sizeof(int),cmpa);
    merge_sort(b,3,sizeof(char)*8,cmpb);
    merge_sort(c,3,sizeof(char),cmpc);
    printf("%d %d %d\n",a[0],a[1],a[2]);
    printf("%s %s %s\n",b[0],b[1],b[2]);
    printf("%c %c %c\n",c[0],c[1],c[2]);
    free(a);
    free(b);
    free(c);
    return 0;
}
