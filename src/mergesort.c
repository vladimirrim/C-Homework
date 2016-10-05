#include "../include/merge.h"
void super_copy(char *p1,char *p2,size_t elem_size){
    for(int i=0;i<elem_size;i++){
        *(p1+i)=*(p2+i);
    }
}

void unite_arrays(void* array,void *a1,size_t n1,void *a2,size_t n2,size_t elem_size,int (*cmp)(const void*,const void*)){
    char *p1=(char*)a1;
    char *p2=(char*)a2;
    int j=0,i=0,k=0;
    while(j<n1&&i<n2){
        if(cmp(a1+j*elem_size,a2+i*elem_size)<0){
            super_copy(array+k*elem_size,p1+j*elem_size,elem_size);
            j++;
        }else{
            super_copy(array+k*elem_size,p2+i*elem_size,elem_size);
            i++;
        }
        k++;
    }
    while(i<n2){
        super_copy(array+k*elem_size,p2+i*elem_size,elem_size);
        i++;
    }
    while(j<n1){
        super_copy(array+k*elem_size,p1+j*elem_size,elem_size);
        j++;
    }
}
void merge_sort(void* array,size_t n,size_t elem_size,int (*cmp)(const void*,const void*)){
    if (n==1){
    }else{
        int m=n/2;
        void *arr1=malloc(sizeof(char)*elem_size*m);
        for(int i=0;i<m;i++){
            super_copy((char*)arr1+i*elem_size,(char*)array+(i)*elem_size,elem_size);
        }
        merge_sort(arr1,m,elem_size,cmp);
        void *arr2=malloc(sizeof(char)*elem_size*(n-m));
        for(int i=0;i<n-m;i++){
            super_copy((char*)arr2+i*elem_size,(char*)array+(m+i)*elem_size,elem_size);
        }
        merge_sort(arr2,n-m,elem_size,cmp);
        unite_arrays(array,arr1,m,arr2,n-m,elem_size,cmp);
        free(arr1);
        free(arr2);
    }
}
